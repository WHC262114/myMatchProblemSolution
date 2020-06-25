#ifndef A_MATCHALL_H
#define A_MATCHALL_H

#include "slab.h"
#include "order.h"
#include "globalVar.h"
#include <vector>

using namespace std;

class A_matchAll
{
private:
    /* data */
public:
    vector<Slab> *SlabList;//原始板坯链表指针
	vector<Order> *OrderList;//原始合同链表指针
	vector<Slab> re_slist;
	vector<Order> re_olist;
	void main(GlobalVar &globalVar);//主函数

    A_matchAll(/* args */);
    ~A_matchAll();
};




#endif