#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include "order.h"
#include "slab.h"
#include <vector>

class GlobalVar
{
public:
	int SlabNum;//板坯数
	int OrderNum;//合同数
	float *OrdSlabQL;//lyn20140803 用来记录算法实时匹配过程中的欠量,只有主制程有效,副制程的加入主制程中
	Order* m_pOrdNode1;//合同数据数组,此数组的序号即板坯链表中的m_nIDOrd,起始 0
	float **OrdSlabWei;
	vector<string> Steel_Ord_NotYC;//lyn 20131017 不可优充的合同的出钢记号
	vector<string> Steel_Slab_NotYC;//lyn 20140721 不可优充的板坯的出钢记号
	int m_nTtoJU;//
	string m_strSiSG[8];//属于硅钢的出钢记号
	// vector<D_Ceya_Si> m_pSiCeyaList;//硅钢侧压标准链表
	int m_nSiCeya[2];//其他硅钢测压标准
	// vector<D_Ceya> m_pCeyaList;//侧压标准链表
	// vector<D_SteelClass> m_pQMMatchSCList;//QM匹配钢级分级链表
	vector<string>*** UnCut;	//不可切割的合同条件vector<OrdCnd3,OrdCnd3>
	// SDJNode *m_DJ;
	// SCompNode *m_Comp;
	// SGANode *m_GA;
	string *m_strPono;
	int Line_Num;//产线个数 dream
	int ALg_Num;//算法个数
	int mode_num;	//模式个数
	int Owei_Num[3]; //0-重点合同，1-全委托合同，参数设置中完整性设置的条件个数
	int ZK_Num[3]; //0-重点合同，1-全委托合同，参数设置中转库设置的条件个数

	vector<Order> m_pOutOrdList;//合同结果链表lc
	vector<Slab> m_pOutSlList;//板坯结果链表lc
	vector<Order>* m_pIniOrdList;//参与匹配的初始合同链表lc
	vector<Slab>* m_pIniSlList;//参与匹配的初始板坯链表lc
	vector<string> Steel_NotCut;//不可切割的出钢记号
	string Directory;//当前程序所在目录
	vector<Slab> m_pSlabList;//板坯链表
	string** Steel_YouChong;//优充表
	string Para_OPrio_Y;//日2+按周2，前月的Y相当于本月...
	vector<string> SCCnd_Ord_All;//全委托合同条件

	GlobalVar(void);
	~GlobalVar(void);
protected:
private:
};

// GlobalVar::GlobalVar(void)
// {
// }

// GlobalVar::~GlobalVar(void)
// {
// }


#endif