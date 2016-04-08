#pragma once

#include "StaticMemory.h"

/** @class ObjectManager
* 实现利用内存池创建对象
* 要求对象具有缺省构造函数
*/

template<typename T>
class ObjectManager
{
public:
	typedef T ObjectType;

	static ObjectType* Create(StaticMemory* pool)
	{
		void* pobject = pool->Malloc(sizeof(T));
		new(pobject) ObjectType();
		return static_cast<ObjectType*>(pobject);
	}
	static void Delete(StaticMemory* pool, ObjectType* pobject)
	{
		pobject->~ObjectType();
		pool->Free(pobject);
	}
};
