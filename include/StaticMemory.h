#pragma once

#include "MemoryChunk.h"  

/** @ StaticMemory.h
* 定义实现内存池
* 采用固定大小策略进行内存管理与分配
* 减少因大量小内存分配导致的内存碎片增加
*/

class StaticMemory
{
public:
	enum { MAX_SIZE = 1024, MIN_SIZE = sizeof(MemoryChunk*) };

	StaticMemory();
	~StaticMemory();

	void* Malloc(size_t size);
	void Free(void* pMem);

protected:
	void* malloc(size_t size);
	bool free(void* pMem);

private:
	MemoryChunk** pChunkList_;
	int chunkcount_;
};
