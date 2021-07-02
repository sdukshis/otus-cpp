// Example from C++ Concurrency in Action

#include <atomic>
#include <iostream>
#include <memory>

template <class T> class lockfree_stack {
  private:
    struct node {
        T data;
        std::shared_ptr<node> next;
        node(const T &data_) : data(data_) {}
    };

    std::shared_ptr<node> head = nullptr;

  public:
    void push(const T &data) {
        std::shared_ptr<node> new_node = std::make_shared<node>(data);
        new_node->next = std::atomic_load(&head);
        while (!std::atomic_compare_exchange_weak(&head, &new_node->next,
                                                  new_node))
            ;
    }

    bool empty() const { return head.load() == nullptr; }

    bool pop(T &result) {
        std::shared_ptr<node> old_head = std::atomic_load(&head);
        while (old_head && !std::atomic_compare_exchange_weak(&head, &old_head,
                                                              old_head->next))
            ;
        if (old_head == nullptr) {
            return false;
        }
        std::atomic_store(&old_head->next, std::shared_ptr<node>());
        result = old_head->data;
        return true;
    }

    ~lockfree_stack() {
        std::shared_ptr<node> next = head;
        while (next) {
            std::shared_ptr<node> prev = next;
            next = next->next;
            prev->next = nullptr;
        }
    }
};

int main() {
#if __cpp_lib_atomic_shared_ptr
    std::atomic<std::shared_ptr<void>> atomic_shared_ptr;
    std::cout << "atomic_shared_ptr.is_lock_free(): "
              << atomic_shared_ptr.is_lock_free() << '\n';
#else
    std::shared_ptr<void> shared_ptr;
    std::cout << "atomic_is_lock_free(shared_ptr<void)): "
              << std::atomic_is_lock_free(&shared_ptr) << '\n';
#endif
    lockfree_stack<int> stack;
    stack.push(42);
    stack.push(17);
    int val;
    stack.pop(val);
}