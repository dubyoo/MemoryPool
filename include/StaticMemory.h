#pragma once

#include "MemoryChunk.h"  

/** @ StaticMemory.h
* ����ʵ���ڴ��
* ���ù̶���С���Խ����ڴ���������
* ���������С�ڴ���䵼�µ��ڴ���Ƭ����
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
