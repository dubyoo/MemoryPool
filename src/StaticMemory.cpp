#include "StaticMemory.h"


struct HeapHeader
{
	size_t size;
};

struct MemoryHeap
{
	HeapHeader header;
	char pBuffer;
};


StaticMemory::StaticMemory()
{
	chunkcount_ = 0;
	for (size_t size = MIN_SIZE; size <= MAX_SIZE; size *= 2)++chunkcount_;
	// pChunkList=(MemoryChunk**)malloc(sizeof(MemoryChunk*)*chunkcount);  
	pChunkList_ = new MemoryChunk*[chunkcount_];
	int index = 0;
	for (size_t size = MIN_SIZE; size <= MAX_SIZE; size *= 2)
	{
		pChunkList_[index++] = new MemoryChunk(size, 1000);
	}
}

StaticMemory::~StaticMemory()
{
	for (int index = 0; index < chunkcount_; ++index)
	{
		delete pChunkList_[index];
	}
	// free(pChunkList);  
	delete[] pChunkList_;
}

void* StaticMemory::Malloc(size_t size)
{
	if (size > MAX_SIZE)
	{
		return malloc(size);		// 超过最大size，直接使用系统malloc申请空间
	}
	int index = 0;
	for (size_t tsize = MIN_SIZE; tsize <= MAX_SIZE; tsize *= 2)
	{
		if (tsize >= size)			// 找到恰好满足空间大小的MemoryChunk
			break;
		++index;
	}
	return pChunkList_[index]->malloc();
}

void StaticMemory::Free(void* pMem)
{
	if (!free(pMem))
		MemoryChunk::free(pMem);
}

void* StaticMemory::malloc(size_t size)
{
	MemoryHeap* pHeap = (MemoryHeap*)::malloc(sizeof(HeapHeader) + size);
	if (pHeap)
	{
		pHeap->header.size = size;
		return &pHeap->pBuffer;
	}
	return nullptr;
}

bool StaticMemory::free(void* pMem)
{
	MemoryHeap* pHeap = (MemoryHeap*)((char*)pMem - sizeof(HeapHeader));
	if (pHeap->header.size > MAX_SIZE)
	{
		::free(pHeap);
		return true;
	}
	return false;
}

