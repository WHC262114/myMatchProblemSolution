#ifndef SLAB_H
#define SLAB_H
#include <string>

using namespace std;

class Slab{
    public:
        string m_strSlabNum;		//板坯号
        string m_strPreOrdNum;		//原合同号
        string m_strPreBK;		    //原BACKLOG
        string m_strCutTime;		//切断时间
        int m_nThick;				//厚度
        float m_nLength;			//长度
        int m_nWidth;				//宽度
        int m_nWidthhead;			//头宽
        int m_nWidthtail;			//尾宽
        float m_nWeight;			//重量
        string m_strDirect;		    //去向
        string m_strSlabState;		//板坯状态
        string m_strStorArea;		//库区
        string m_strSteelGrade;	    //出钢记号
        string m_strQualityGrade;	//质量等级 9是报废坯
        int m_nTSign;				//调宽标志 0矩形坯,1小头在前(尾<头,异常),2大头在前(尾>头).尾先进轧机,大头在前是正常的.
        /*------------*/
        string m_strNowOrdNum;		//现合同号
        string m_strOrdSt;			//合同状态
        string m_strOrdProp;		//合同性质
        string m_strDlvDate;		//用户合同期
        string m_strOrdType;       //合同类别
        string m_strNowBK;

        /*-----------*/


};
#endif