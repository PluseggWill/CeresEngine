#include <iostream>
using namespace std;

template<int ObjectSize, int NumofObjects = 20>
class MemPool
{
private:
	struct FreeNode
	{
		FreeNode* pNext;
		char data[ObjectSize];
	};

	struct MemBlock
	{
		MemBlock* pNext;
		FreeNode data[NumofObjects];
	};

	FreeNode* freeNodeHeader;
	MemBlock* memBlockHeader;

public:
	MemPool()
	{
		freeNodeHeader = NULL;
		memBlockHeader = NULL;
	}

	~MemPool()
	{
		MemBlock* ptr;
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

template<int ObjectSize, int NumofObjects>
void* MemPool<ObjectSize, NumofObjects>::malloc()
{
	if (freeNodeHeader == NULL)
	{
		MemBlock* newBlock = new MemBlock;
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

template<int ObjectSize, int NumofObjects>
void MemPool<ObjectSize, NumofObjects>::free(void* p)
{
	FreeNode* pNode = (FreeNode*)p;
	pNode->pNext = freeNodeHeader;
	freeNodeHeader = pNode;
}