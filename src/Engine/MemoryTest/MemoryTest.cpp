using namespace std;
#include <iostream>

#include<time.h>

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


int mcount = 0;

class TestClass
{

public:
	float content1;
	float content2;
	float content3;
	float content4;


	void print()
	{
		cout << this << ": ";
		cout << mcount++ << "\n";
	}

	void* operator new(size_t size);
	void operator delete(void* p);
};


PoolAllocator<TestClass, 50> mp;

void* TestClass::operator new(size_t size)
{
	return mp.malloc();
}

void TestClass::operator delete(void* p)
{
	mp.free(p);
}

class TestClass2
{

public:
	float content1;
	float content2;
	float content3;
	float content4;

};

int main()
{
	clock_t startTime, endTime;
	startTime = clock();
	for (int i = 0; i < 100000; i++) {
		TestClass* p[100];
		for (int j = 0; j < 100; j++) {

			p[j] = new TestClass;
		}
		for (int j = 0; j < 100; j++) {

			delete p[j];
		}
	}

	/*TestClass* p2 = new TestClass;
	p2->print();


	TestClass* p3 = new TestClass;
	p3->print();

	delete p2;
	delete p3;

	TestClass* p4 = new TestClass;
	p4->print();


	TestClass* p5 = new TestClass;
	p5->print();

	delete p4;
	delete p5;*/
	endTime = clock();
	cout << "Pool Allocator Total Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;


	startTime = clock();
	for (int i = 0; i < 100000; i++) {
		TestClass2* p[100];
		for (int j = 0; j < 100; j++) {

			p[j] = new TestClass2;
		}
		for (int j = 0; j < 100; j++) {

			delete p[j];
		}
	}
	endTime = clock();
	cout << "Default Total Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	system("pause");

}