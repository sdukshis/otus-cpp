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

  public:
    void push(const T &data) {
        node *new_node = new node(data);
        new_node->next = head.load();
        while (!head.compare_exchange_weak(new_node->next, new_node))
            ;
    }

    bool empty() const { return head.load() == nullptr; }

    bool pop(T &result) {
        node *old_head = head.load();
        while (old_head &&
               !head.compare_exchange_weak(old_head, old_head->next))
            ;
        if (old_head == nullptr) {
            return false;
        }
        result = old_head->data;
        return true;
    }

    ~lockfree_stack() {
        node *next = head.load();
        while (next) {
            node *prev = next;
            next = next->next;
            delete prev;
        }
    }
};

int main() {
    lockfree_stack<int> stack;
    stack.push(42);
    stack.push(17);
    int val;
    stack.pop(val);
}