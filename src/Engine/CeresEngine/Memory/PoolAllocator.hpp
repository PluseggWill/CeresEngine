using namespace std;
#include <iostream>

template<typename T, int NumofObjects = 20>
class PoolAllocator
{
private:
	struct Node
	{
		Node* pNext;
		T object;
	};

	struct Block
	{
		Block* pNext;
		Node data[NumofObjects];
	};

	Node* freeNodeHeader;
	Block* memBlockHeader;

public:
	PoolAllocator()
	{
		freeNodeHeader = NULL;
		memBlockHeader = NULL;
	}

	~PoolAllocator()
	{
		Block* ptr;
		while (memBlockHeader)
		{
			ptr = memBlockHeader->pNext;
			delete memBlockHeader;
			memBlockHeader = ptr;
		}
	}
	void* malloc();
	void free(void*);
};

template<typename T, int NumofObjects>
void* PoolAllocator<T, NumofObjects>::malloc()
{
	if (freeNodeHeader == NULL)
	{
		Block* newBlock = new Block;
		newBlock->pNext = NULL;

		freeNodeHeader = &newBlock->data[0];
		for (int i = 1; i < NumofObjects; ++i)
		{
			newBlock->data[i - 1].pNext = &newBlock->data[i];
		}
		newBlock->data[NumofObjects - 1].pNext = NULL;

		if (memBlockHeader == NULL)
		{
			memBlockHeader = newBlock;
		}
		else
		{
			newBlock->pNext = memBlockHeader;
			memBlockHeader = newBlock;
		}
	}
	void* freeNode = freeNodeHeader;
	freeNodeHeader = freeNodeHeader->pNext;
	return freeNode;
}

template<typename T, int NumofObjects>
void PoolAllocator<T, NumofObjects>::free(void* p)
{
	Node* pNode = (Node*)p;
	pNode->pNext = freeNodeHeader;
	freeNodeHeader = pNode;
}