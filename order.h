#ifndef ORDER_H
#define ORDER_H

#include <string>

using namespace std;

class Order
{
private:
    /* data */
public:
    string m_strOrderNum;	        //合同号 
    string m_strBacklog;	        //BackLog号 
    string m_strOrdState;	        //合同状态
    string m_strOrdProp;	        //合同性质 
    string m_strSteelGrade;         //出钢记号
    string m_strST[10];//副出钢记号 yy
    float m_nOrdWeight;		//合同订货量
    int m_nPWidth;			//成品板/卷宽度
    string m_strDlvDate;	//合同交货期 
    string m_strPlantDate;	//厂内交货期
    string m_strOrdType;	//合同类别
    string m_strMtrlGroup;	//材料组别
    int m_nWidths;			//板宽下
	int m_nWidthl;			//板宽上
    float m_nLengths;		//板长下
	float m_nLengthl;		//板长上
	float m_nWeights;		//板重下
	float m_nWeightl;		//板重上
    float m_nRollThick;			//额定轧制厚度
    int m_nRollWidth;		//轧宽
    float m_nApplyLackWe;	//申请欠量
	float m_nRollLackWe;	//轧制欠量
    float m_nPWeightl;		//成品重上限
	float m_nPWeights;		//成品重下限
    float m_nLGWeight;		//炼钢工序在库量
	float m_nRZWeight;		//热轧工序在库量
    float m_nJZWeight;		//钢坯精整工序在库量

    // Order();
	// virtual ~Order();

	// Order(const Order* pOrd);
	// Order & operator = (const Order &ord);

};



#endif