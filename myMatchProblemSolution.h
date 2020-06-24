#ifndef MYMATCHPROBLEMSOLUTION_H
#define MYMATCHPROBLEMSOLUTION_H

#include "order.h"
#include "slab.h"
#include "globalVar.h"
#include <vector>

vector<Slab> m_pPreSlabList;            //预定板坯链表
vector<Order> m_pSCList;                //本次收池链表
vector<Order> m_pOrderList;             //合同链表
vector<Order> m_prolist;                //合同链表
GlobalVar globalVar;
vector<string> STYC_Array;              ///优充表的Array
int YouChongNum;                        //记录优充表的出钢记号的组数


#endif