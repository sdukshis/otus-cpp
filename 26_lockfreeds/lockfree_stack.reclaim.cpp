// Example from C++ Concurrency in Action

#include <atomic>

template <class T> class lockfree_stack {
  private:
    struct node {
        T data;
        node *next;
        node(const T &data_) : data(data_) {}
    };

    std::atomic<node *> head = nullptr;
    std::atomic<node *> to_be_deleted = nullptr;
    static void delete_nodes(node *nodes) {
        while (nodes) {
            node *next = nodes->next;
            delete nodes;
            nodes = next;
        }
    }
    std::atomic<unsigned> threads_in_pop = 0;
    void try_reclaim(node *old_head) {
        if (threads_in_pop == 1) {
            node *nodes_to_delete = to_be_deleted.exchange(nullptr);
            if (!--threads_in_pop) {
                delete_nodes(nodes_to_delete);
            } else if (nodes_to_delete) {
                chain_pending_nodes(nodes_to_delete);
            }
            delete old_head;
        } else {
            chain_pending_node(old_head);
            --threads_in_pop;
        }
    }
    void chain_pending_nodes(node *nodes) {
        node *last = nodes;
        while (node *next = last->next) {
            last = next;
        }
        chain_pending_nodes(nodes, last);
    }

    void chain_pending_nodes(node *first, node *last) {
        last->next = to_be_deleted;
        while (!to_be_deleted.compare_exchange_weak(last->next, first))
            ;
    }

    void chain_pending_node(node *n) { chain_pending_nodes(n, n); }

  public:
    void push(const T &data) {
        node *new_node = new node(data);
        new_node->next = head.load();
        while (!head.compare_exchange_weak(new_node->next, new_node))
            ;
    }

    bool empty() const { return head.load() == nullptr; }

    bool pop(T &result) {
        ++threads_in_pop;
        node *old_head = head.load();
        while (old_head &&
               !head.compare_exchange_weak(old_head, old_head->next))
            ;
        if (old_head == nullptr) {
            return false;
        }
        result = old_head->data;
        try_reclaim(old_head);
        return true;
    }

    ~lockfree_stack() {
        delete_nodes(head.load());
        delete_nodes(to_be_deleted.load());
    }
};

int main() {
    lockfree_stack<int> stack;
    stack.push(42);
    stack.push(17);
    int val;
    stack.pop(val);
}