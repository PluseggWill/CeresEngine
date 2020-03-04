#include <iostream>
using namespace std;

template<typename T>
class MemoryPool
{
private:
	struct PoolNode
	{
		PoolNode* pNext;
		T data;
	};

	PoolNode* freeNodeHeader;

public:
	MemoryPool()
	{
		freeNodeHeader = NULL;
	}

	~MemoryPool()
	{
		PoolNode* ptr;
		while (freeNodeHeader)
		{
			ptr = freeNodeHeader->pNext;
			delete freeNodeHeader;
			freeNodeHeader = ptr;
		}
	}
	void* malloc();
	void free(void*);
};

template<typename T>
void* MemoryPool<T>::malloc()
{
	if (freeNodeHeader == NULL)
	{
		freeNodeHeader* newNode = new freeNodeHeader;
		newNode->pNext = NULL;

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

template<typename T>
void MemoryPool<T>::free(void* p)
{
	FreeNode* pNode = (FreeNode*)p;
	pNode->pNext = freeNodeHeader;
	freeNodeHeader = pNode;
}

MemoryPool<ActualClass> mp;

class ActualClass
{

public:
	void print()
	{
		cout << this << "\n";
	}

	void* operator new(size_t size);
	void operator delete(void* p);
};


void* ActualClass::operator new(size_t size)
{
	return mp.malloc();
}

void ActualClass::operator delete(void* p)
{
	mp.free(p);
}


int main()
{
	ActualClass* p1 = new ActualClass;
	p1->print();

	ActualClass* p2 = new ActualClass;
	p2->print();
	delete p1;

	p1 = new ActualClass;
	p1->print();

	ActualClass* p3 = new ActualClass;
	p3->print();

	delete p1;
	delete p2;
	delete p3;
}