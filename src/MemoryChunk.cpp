#include "MemoryChunk.h"


/** @struct MemoryBlock
*
*/
struct BlockHeader
{
	MemoryChunk* pChunk;
	size_t len;
};
struct MemoryBlock;
struct BlockData
{
	union
	{
		MemoryBlock* pNext;
		char pBuffer;
	};
};
struct MemoryBlock
{
	BlockHeader header;
	BlockData data;
};


MemoryChunk::MemoryChunk(size_t size, int count)
	: mutex_()
{
	this->pFreeList_ = nullptr;
	this->size_ = size;
	this->count_ = 0;
	MemoryBlock* pBlock;
	while (count--)
	{
		pBlock = CreateBlock();
		if (!pBlock)break;
		pBlock->data.pNext = pFreeList_;
		pFreeList_ = pBlock;
	}
}

MemoryChunk::~MemoryChunk()
{
	int tempcount = 0;
	MemoryBlock* pBlock;
	while (pFreeList_)
	{
		pBlock = pFreeList_;
		pFreeList_ = pBlock->data.pNext;
		DeleteBlock(pBlock);
		++tempcount;
	}
	assert(tempcount == count_);			// 确保释放完全（可以查看是否有内存泄露）
}

void* MemoryChunk::malloc()
{
	MemoryBlock* pBlock;
	mutex_.lock();

	if (pFreeList_)
	{
		pBlock = pFreeList_;
		pFreeList_ = pBlock->data.pNext;
	}
	else
	{
		if (!(pBlock = CreateBlock()))
		{
			mutex_.unlock();
			return nullptr;
		}
	}
	mutex_.unlock();
	return &pBlock->data.pBuffer;
}

void MemoryChunk::free(void* pMem)
{
	MemoryBlock* pBlock = (MemoryBlock*)((char*)pMem - sizeof(BlockHeader));
	pBlock->header.pChunk->free(pBlock);
}

void MemoryChunk::free(MemoryBlock* pBlock)
{
	mutex_.lock();
	pBlock->data.pNext = pFreeList_;
	pFreeList_ = pBlock;
	mutex_.unlock();
}

MemoryChunk* MemoryChunk::Next() 
{ 
	return pNext_; 
}

MemoryBlock* MemoryChunk::CreateBlock()
{
	MemoryBlock* pBlock = (MemoryBlock*)::malloc(sizeof(BlockHeader) + size_);

	if (pBlock)
	{

		pBlock->header.pChunk = this;
		pBlock->header.len = size_;

		++count_;
	}
	return pBlock;
}

void MemoryChunk::DeleteBlock(MemoryBlock* pBlock)
{
	::free(pBlock);
}
