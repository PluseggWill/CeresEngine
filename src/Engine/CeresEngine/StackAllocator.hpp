using namespace std;

template <typename T>
class StackAllocator
{
private:
	struct StackNode
	{
		StackNode* prev;
		T object;
	};

	StackNode* stackNodeHeader;

public:
	StackAllocator()
	{
		stackNodeHeader = NULL;
	}

	~StackAllocator()
	{
		StackNode* ptr;
		while (stackNodeHeader)
		{
			ptr = stackNodeHeader->prev;
			delete stackNodeHeader;
			stackNodeHeader = ptr;
		}
	}
	void* malloc();
};

template<typename T>
void* StackAllocator<T>::malloc()
{
	if (stackNodeHeader != NULL)
	{
		StackNode* newNode = new StackNode;
		newNode->prev = stackNodeHeader;
		stackNodeHeader = newNode;
	}
	return stackNodeHeader;
}
