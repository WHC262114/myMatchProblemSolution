#include "myMatchProblemSolution.h"
#include "order.h"
#include "slab.h"
#include "A_matchAll.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string Trim(string &str)
{
    //str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置
    str.erase(0, str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
    return str;
}

void readSlabData()
{
    //读板坯数据
    globalVar.m_pSlabList.clear();
    m_pPreSlabList.clear();
    globalVar.SlabNum = 0;
    string slabnum = "";

    ifstream fin("./data/slabData.csv");
    string line;
    if (fin.fail())
        cout << "failed" << endl;
    getline(fin, line); //跳过第一行
    while (getline(fin, line))
    {
        // cout << line << endl;
        stringstream ss(line);
        string strValue;
        Slab slab;

        getline(ss, strValue, ','); //板坯号
        slab.m_strSlabNum = Trim(strValue);

        getline(ss, strValue, ',');
        slab.m_strPreOrdNum = Trim(strValue); //原合同号
        slab.m_strNowOrdNum = "";             //现合同号

        getline(ss, strValue, ',');
        slab.m_strPreBK = Trim(strValue); //原backlog号
        slab.m_strNowBK = "";

        getline(ss, strValue, ',');
        slab.m_strCutTime = Trim(strValue); //板坯切断时间

        getline(ss, strValue, ',');
        slab.m_nThick = Trim(strValue).empty() ? 0 : stoi(strValue); //厚度

        getline(ss, strValue, ',');
        slab.m_nLength = Trim(strValue).empty() ? 0 : stoi(strValue); //长度

        getline(ss, strValue, ',');
        slab.m_nWidth = Trim(strValue).empty() ? 0 : stoi(strValue); //标准宽

        getline(ss, strValue, ',');
        slab.m_nWidthhead = Trim(strValue).empty() ? 0 : stoi(strValue); //头宽

        getline(ss, strValue, ',');
        slab.m_nWidthtail = Trim(strValue).empty() ? 0 : stoi(strValue); //尾宽

        int wid = (slab.m_nWidthhead < slab.m_nWidthtail ? slab.m_nWidthhead : slab.m_nWidthtail);
        if (slab.m_nWidth < wid && slab.m_nWidth < slab.m_nWidthtail)
            slab.m_nWidthtail = slab.m_nWidth;
        if (slab.m_nWidth < wid && slab.m_nWidth < slab.m_nWidthhead)
            slab.m_nWidthhead = slab.m_nWidth;
        if (slab.m_nWidthtail == slab.m_nWidthhead && slab.m_nWidthtail == 0)
        {
            slab.m_nWidthtail = slab.m_nWidth;
            slab.m_nWidthhead = slab.m_nWidth;
        }
        if (abs(slab.m_nWidthtail - slab.m_nWidthhead) <= globalVar.m_nTtoJU) //矩形坯头宽尾宽宽度差
        {
            slab.m_nTSign = 0;
        }
        else if (slab.m_nWidthtail > slab.m_nWidthhead) //尾先进轧机,大头在前是正常的.
            slab.m_nTSign = 2;                          //大头在前
        else if (slab.m_nWidthtail < slab.m_nWidthhead)
            slab.m_nTSign = 1; //小头在前

        getline(ss, strValue, ',');
        slab.m_nWeight = Trim(strValue).empty() ? 0 : stof(strValue); //重量

        getline(ss, strValue, ',');
        slab.m_strDirect = Trim(strValue); //去向

        getline(ss, strValue, ',');
        slab.m_strSlabState = Trim(strValue); //状态

        getline(ss, strValue, ',');
        slab.m_strStorArea = Trim(strValue); //库区

        getline(ss, strValue, ',');
        slab.m_strSteelGrade = Trim(strValue); //出钢记号

        getline(ss, strValue, ',');
        slab.m_strQualityGrade = Trim(strValue); //质量等级

        getline(ss, strValue, ',');
        slab.m_strOrdSt = Trim(strValue); //合同状态

        getline(ss, strValue, ',');
        slab.m_strOrdProp = Trim(strValue); //合同性质

        getline(ss, strValue, ',');
        slab.m_strDlvDate = Trim(strValue); //用户合同期

        getline(ss, strValue, ',');
        slab.m_strOrdType = Trim(strValue); //合同类别

        if (slab.m_strSlabNum != slabnum || slabnum == "") //相同板坯号的不加入链表
        {
            if (slab.m_strSlabNum.size() == 11 || slab.m_strSlabNum.size() == 13) //  yy11to13
            {
                globalVar.m_pSlabList.push_back(slab);
                globalVar.SlabNum++;
            }
            else if (slab.m_strSlabNum.size() == 9) //  yy9to11  11位的表示预定板坯
            {
                m_pPreSlabList.push_back(slab);
            }
            slabnum = slab.m_strSlabNum;
        }
    }
}

void readOrderData()
{
    m_pOrderList.clear();
    globalVar.OrderNum = 0;
    string ordnum = "", backlog = "";

    ifstream fin("./data/orderData.csv");
    string line;
    if (fin.fail())
        cout << "failed" << endl;
    getline(fin, line); //跳过第一行
    while (getline(fin, line))
    {
        stringstream ss(line);
        string strValue;
        Order ord;

        getline(ss, strValue, ',');
        ord.m_strOrderNum = Trim(strValue); //合同号

        getline(ss, strValue, ',');
        ord.m_strBacklog = Trim(strValue); //backlog号

        getline(ss, strValue, ',');
        ord.m_strOrdState = Trim(strValue); //合同状态

        getline(ss, strValue, ',');
        ord.m_strOrdProp = Trim(strValue); //合同性质

        getline(ss, strValue, ',');
        ord.m_strSteelGrade = Trim(strValue); //出钢记号

        getline(ss, strValue, ',');
        ord.m_nPWidth = Trim(strValue).empty() ? 0 : stoi(strValue); //成品板/卷宽度

        getline(ss, strValue, ',');
        ord.m_nOrdWeight = Trim(strValue).empty() ? 0 : stoi(strValue); //合同订货量

        getline(ss, strValue, ',');
        ord.m_strDlvDate = Trim(strValue); //用户合同期

        //ord.m_strPlantDate = Trim(strValue);                //厂内交货期

        getline(ss, strValue, ',');
        ord.m_strOrdType = Trim(strValue); //合同类别

        getline(ss, strValue, ',');
        ord.m_strMtrlGroup = Trim(strValue); //材料组别

        getline(ss, strValue, ',');
        ord.m_nWidthl = Trim(strValue).empty() ? 0 : stoi(strValue); //合同宽上限

        getline(ss, strValue, ',');
        ord.m_nWidths = Trim(strValue).empty() ? 0 : stoi(strValue); //合同宽下限

        getline(ss, strValue, ',');
        ord.m_nLengthl = Trim(strValue).empty() ? 0 : stof(strValue); //合同长上限

        getline(ss, strValue, ',');
        ord.m_nLengths = Trim(strValue).empty() ? 0 : stof(strValue); //合同长下限

        getline(ss, strValue, ',');
        ord.m_nWeightl = Trim(strValue).empty() ? 0 : stof(strValue); //板坯重上限

        getline(ss, strValue, ',');
        ord.m_nWeights = Trim(strValue).empty() ? 0 : stof(strValue); //板坯重下限

        getline(ss, strValue, ',');
        ord.m_nRollThick = Trim(strValue).empty() ? 0 : stof(strValue); //额定轧制厚度

        getline(ss, strValue, ',');
        ord.m_nRollWidth = Trim(strValue).empty() ? 0 : stoi(strValue); //额定轧制宽度

        getline(ss, strValue, ',');
        ord.m_nApplyLackWe = Trim(strValue).empty() ? 0 : stof(strValue); //申请欠量

        getline(ss, strValue, ',');
        ord.m_nRollLackWe = Trim(strValue).empty() ? 0 : stof(strValue); //轧制欠量

        getline(ss, strValue, ',');
        ord.m_nPWeightl = Trim(strValue).empty() ? 0 : stof(strValue); //成品重量上限

        getline(ss, strValue, ',');
        ord.m_nPWeights = Trim(strValue).empty() ? 0 : stof(strValue); //成品重量下限

        getline(ss, strValue, ',');
        ord.m_nLGWeight = Trim(strValue).empty() ? 0 : stof(strValue); //炼钢工序在库量

        getline(ss, strValue, ',');
        ord.m_nJZWeight = Trim(strValue).empty() ? 0 : stof(strValue); //精整工序在库量

        getline(ss, strValue, ',');
        ord.m_nRZWeight = Trim(strValue).empty() ? 0 : stof(strValue); //热轧工序在库量

        getline(ss, strValue, ',');
        ord.m_strST[0] = Trim(strValue);

        getline(ss, strValue, ',');
        ord.m_strST[1] = Trim(strValue);

        getline(ss, strValue, ',');
        ord.m_strST[2] = Trim(strValue);

        getline(ss, strValue, ',');
        ord.m_strST[3] = Trim(strValue);

        getline(ss, strValue, ',');
        ord.m_strST[4] = Trim(strValue);

        getline(ss, strValue, ',');
        ord.m_strST[5] = Trim(strValue);

        getline(ss, strValue, ',');
        ord.m_strST[6] = Trim(strValue);

        getline(ss, strValue, ',');
        ord.m_strST[7] = Trim(strValue);

        getline(ss, strValue, ',');
        ord.m_strST[8] = Trim(strValue);

        getline(ss, strValue, ',');
        ord.m_strST[9] = Trim(strValue);

        if (ord.m_nRollWidth <= 0)
            ord.m_nRollWidth = ord.m_nWidths;
        if (ord.m_strOrderNum != ordnum || ord.m_strBacklog != backlog || ordnum == "") //相同的不加入链表
        {
            m_pOrderList.push_back(ord);
            globalVar.OrderNum++;
            ordnum = ord.m_strOrderNum;
            backlog = ord.m_strBacklog;
        }
    }
}

void readYouchong()
{
    YouChongNum = 0;
    STYC_Array.clear();

    ifstream fin("./data/Youchong.csv");
    string line;
    if (fin.fail())
        cout << "failed" << endl;
    getline(fin, line); //跳过第一行
    while (getline(fin, line))
    {
        string str = "";
        stringstream ss(line);
        string strValue;

        getline(ss, strValue, ',');
        // if (Trim(strValue).size() != 8 && Trim(strValue).size() != 0)
        //     cout << "getit" << strValue << endl;
        str += Trim(strValue); //NOM_ST_NO

        getline(ss, strValue, ',');
        // if (Trim(strValue).size() != 8 && Trim(strValue).size() != 0)
        //     cout << "getit" << strValue << endl;
        str += Trim(strValue); //ST_NO_1

        getline(ss, strValue, ',');
        // if (Trim(strValue).size() != 8 && Trim(strValue).size() != 0)
        //     cout << "getit" << strValue << endl;
        str += Trim(strValue); //ST_NO_2

        getline(ss, strValue, ',');
        // if (Trim(strValue).size() != 8 && Trim(strValue).size() != 0)
        //     cout << "getit" << strValue << endl;
        str += Trim(strValue); //ST_NO_3

        getline(ss, strValue, ',');
        // if (Trim(strValue).size() != 8 && Trim(strValue).size() != 0)
        //     cout << "getit" << strValue << endl;
        str += Trim(strValue); //ST_NO_4

        getline(ss, strValue, ',');
        // if (Trim(strValue).size() != 8 && Trim(strValue).size() != 0)
        //     cout << "getit" << strValue << endl;
        str += Trim(strValue); //ST_NO_5

        getline(ss, strValue, ',');
        // if (Trim(strValue).size() != 8 && Trim(strValue).size() != 0)
        //     cout << "getit" << strValue << endl;
        str += Trim(strValue); //ST_NO_6

        getline(ss, strValue, ',');
        // if (Trim(strValue).size() != 8 && Trim(strValue).size() != 0)
        //     cout << "getit" << strValue << endl;
        str += Trim(strValue); //ST_NO_7

        getline(ss, strValue, ',');
        // if (Trim(strValue).size() != 8 && Trim(strValue).size() != 0)
        //     cout << "getit" << strValue << endl;
        str += Trim(strValue); //ST_NO_8

        getline(ss, strValue, ',');
        // if (Trim(strValue).size() != 8 && Trim(strValue).size() != 0)
        //     cout << "getit" << strValue << endl;
        str += Trim(strValue); //ST_NO_9

        getline(ss, strValue, ',');
        // if (Trim(strValue).size() != 8 && Trim(strValue).size() != 0)
        //     cout << "getit" << strValue << endl;
        str += Trim(strValue); //ST_NO_10

        if (str.size() > 8)             //只有一个出钢记号的不需要加入该序列
        { 
            STYC_Array.push_back(str);
            //cout << str << "；长度是：" << str.size() << endl;
        }
    }
}

void AlgAll(){
    A_matchAll sm;
    sm.SlabList = &globalVar.m_pSlabList;
    sm.OrderList = &m_pOrderList;
    sm.main(globalVar);
}

int main()
{
    cout << "进入main" << endl;
    readSlabData();
    readOrderData();
    readYouchong();
    cout << "板坯数据量：" << globalVar.m_pSlabList.size() << endl;
    cout << "预定板坯量" << m_pPreSlabList.size() << endl;
    cout << "合同数据量：" << m_pOrderList.size() << endl;
    cout << "优充表数据量：" << STYC_Array.size() << endl;
}