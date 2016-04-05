#pragma once

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <mutex>


struct MemoryBlock;


class MemoryChunk
{
public:
	MemoryChunk(size_t size, int count);
	~MemoryChunk();
	void* malloc();
	void free(MemoryBlock* pBlock);
	MemoryChunk* Next();

	static void free(void* pMem);

protected:
	MemoryBlock* CreateBlock();
	void DeleteBlock(MemoryBlock* pBlock);

private:
	MemoryBlock* pFreeList_;
	size_t size_;			// Block��С
	int count_;				// Block��Ŀ
	MemoryChunk* pNext_;
	std::mutex mutex_;
};
