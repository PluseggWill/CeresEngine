
#include <memory>

template <typename T>
struct StackNode
{
	T data;
	StackNode* prev;
};

template <class T, class Alloc = std::allocator<T> >
class StackAllocator
{
public:
	typedef StackNode<T> Node;
	typedef typename Alloc::template rebind<Node>::other allocator;

	StackAllocator() { head = 0; }
	~StackAllocator() { clear(); }

	bool empty() { return (head == 0); }

	void clear() {
		Node* curr = head;
		while (curr != 0)
		{
			Node* tmp = curr->prev;
			allocator.destroy(curr);
			allocator.deallocate(curr, 1);
			curr = tmp;
		}
		head = 0;
	}

	void push(T element) {
		Node* newNode = allocator.allocate(1);
		allocator.construct(newNode, Node());

		newNode->data = element;
		newNode->prev = head;
		head = newNode;
	}

	T pop() {
		T result = head->data;
		Node* tmp = head->prev;
		allocator.destroy(head);
		allocator.deallocate(head, 1);
		head = tmp;
		return result;
	}

	T top() { return (head->data); }

private:
	allocator allocator;
	Node* head;
};
