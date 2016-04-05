
#include <iostream>
#include <time.h>
#include "ObjectManager.h"

using namespace std;

class MyMessage
{
public:
	MyMessage()
		: id_(13)
		, msg_("Hello")
	{
	}

	friend ostream& operator << (ostream &out, const MyMessage& m)
	{
		return out << m.id_ << " " << m.msg_;
	}

private:
	int id_;
	char msg_[512];
};

int main()
{
	int times = 10000000;
	clock_t start_time = clock();

	StaticMemory* pool = new StaticMemory;
	while (--times)
	{
		MyMessage* pmsg0 = ObjectManager<MyMessage>::Create(pool);
		MyMessage* pmsg1 = ObjectManager<MyMessage>::Create(pool);
		MyMessage* pmsg2 = ObjectManager<MyMessage>::Create(pool);
		MyMessage* pmsg3 = ObjectManager<MyMessage>::Create(pool);
		MyMessage* pmsg4 = ObjectManager<MyMessage>::Create(pool);
// 		cout << *pmsg0 << endl;
// 		cout << *pmsg1 << endl;
// 		cout << *pmsg2 << endl;
// 		cout << *pmsg3 << endl;
// 		cout << *pmsg4 << endl;
		ObjectManager<MyMessage>::Delete(pool, pmsg0);
		ObjectManager<MyMessage>::Delete(pool, pmsg1);
		ObjectManager<MyMessage>::Delete(pool, pmsg2);
		ObjectManager<MyMessage>::Delete(pool, pmsg3);
		ObjectManager<MyMessage>::Delete(pool, pmsg4);
	}																		//	-O0	4.73s		-O2	1.39s
	delete pool;


// 	while (--times)
// 	{
// 		
// 		MyMessage* pmsg0 = new MyMessage;
// 		MyMessage* pmsg1 = new MyMessage;
// 		MyMessage* pmsg2 = new MyMessage;
// 		MyMessage* pmsg3 = new MyMessage;
// 		MyMessage* pmsg4 = new MyMessage;
// 		
// 		delete pmsg0;
// 		delete pmsg1;
// 		delete pmsg2;
// 		delete pmsg3;
// 		delete pmsg4;
// 
// // 		MyMessage* pmsg = (MyMessage*)malloc(sizeof(MyMessage));
// // 		new(pmsg) MyMessage();
// // 		cout << (*pmsg) << endl;
// // 		pmsg->~MyMessage();
// // 		free(pmsg);
// 	}																		//	-O2 3.53s

	clock_t end_time = clock();
	double duration = (double)(end_time - start_time) / (double)CLOCKS_PER_SEC;
	cout << "====== Take time: " << duration << " ======" << endl;

	return 0;
}
