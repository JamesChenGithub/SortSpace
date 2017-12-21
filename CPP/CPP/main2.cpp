//
//  main2.cpp
//  CPP
//
//  Created by AlexiChen on 2017/11/28.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <math.h>
#include <initializer_list>

using namespace std;





//=======================================
//我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？

class Sample11{
public:
    int rectCover(int number)
    {
        if (number <= 0)
        {
            return 0;
        }
        else if (number == 1)
        {
            return 1;
        }
        else if (number == 2)
        {
            return 2;
        }
        else
        {
            return rectCover(number - 1) + 2*rectCover(number - 2);
            
        }
    }
};
//=======================================
//输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。
class Sample12{
public:
    int numbleof1(int number)
    {
        if (number == 0)
        {
            return 0;
        }
        else
        {
            int count = 0;
            int nn = number;
            while (nn != 0)
            {
                nn = nn & (nn - 1);
                count++;
            }
            
            return count;
        }
    }
};

//=======================================
//给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。

class Sample13
{
public:
    double power(double base, int ex)
    {
        double result = 1.0;
        
        
        if (ex == 0)
        {
            return result;
        }
        else if (ex > 0)
        {
            while (ex > 0)
            {
                result *= base;
                ex--;
            }
        }
        else
        {
            if (base == 0)
            {
                cout << "除以0,不能操作";
                return -1;
            }
            
            while (ex < 0)
            {
                result /= base;
                ex++;
            }
        }
        
        return result;
    }
    
    
    double powerv2(double base, int ex)
    {
        double result = 1.0;
        double cur = base;
        int n = ex;
        if (ex == 0) {
            return result;
        }
        else
        {
            if (ex < 0)
            {
                if (base == 0)
                {
                    cout << "除以0,不能操作";
                    return -1;
                }
                
                n = -n;
            }
        }
        
        while (n != 0) {
            if ((n & 1) == 1)
            {
                result *= cur;
            }
            
            cur *= cur;
            
            n >>= 1;
        }
        
        
        return ex > 0 ? result : 1.0/result;
    }
};
//=======================================

//输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。
class Sample14{
public:
    void operArray(int array[], unsigned int size)
    {
        return;
        cout << "========operArray======" << endl;
        int oddIndex = 0;
        int evenIndex = 0;
        int lastOddIndex = 0;
        int lastEvenIndex = 0;
        static int kOperCount = 0;
        
        cout <<  "初始值为 ： ";
        for (int k = 0; k < size; k++)
        {
            cout << array[k] << "   ";
        }
        cout << endl;
        
        for (int i = 0; i < size; i++)
        {
            if (array[i] % 2 == 1)
            {
                lastOddIndex = oddIndex;
                oddIndex = i;
            }
            if (array[i] % 2 == 0)
            {
                lastEvenIndex = evenIndex;
                evenIndex = i;
            }
            
            if (evenIndex < oddIndex)
            {
                int odd = array[oddIndex];
                for (int j = oddIndex; j>lastOddIndex; j--)
                {
                    array[j] = array[j-1];
                }
                array[lastOddIndex] = odd;
                
                cout << ++kOperCount << "次整理 ： ";
                for (int k = 0; k < size; k++)
                {
                    cout << array[k] << "   ";
                }
                cout << endl;
                
                int temp =  oddIndex;
                oddIndex = evenIndex;
                evenIndex = temp;
                
            }
            
        }
        
        kOperCount = 0;
    }
    
    
    void operArrayv2(int array[], unsigned int size)
    {
        cout << "========operArrayv2======" << endl;
        int oddIndex = 0;
        int firstevenIndex = -1;
        
        static int kOperCount = 0;
        
        cout <<  "初始值为 ： ";
        for (int k = 0; k < size; k++)
        {
            cout << array[k] << "   ";
        }
        cout << endl;
        
        for (int i = 0; i < size; i++)
        {
            if (array[i] % 2 == 1)
            {
                oddIndex = i;
            }
            if (array[i] % 2 == 0)
            {
                if (firstevenIndex == -1)
                {
                    firstevenIndex = i;
                }
            }
            
            if (firstevenIndex < oddIndex && firstevenIndex != -1)
            {
                //                cout << kOperCount+1 << "次整理前 ： ";
                //                for (int k = 0; k < size; k++)
                //                {
                //                    cout << array[k] << "   ";
                //                }
                //                cout << endl;
                
                
                //                cout <<  "firstevenIndex = " << firstevenIndex <<"   oddIndex == " << oddIndex <<endl;
                int odd = array[oddIndex];
                for (int j = oddIndex; j > firstevenIndex; j--)
                {
                    array[j] = array[j-1];
                }
                array[firstevenIndex++] = odd;
                oddIndex = 0;
                
                cout << ++kOperCount << "次整理后 ： ";
                for (int k = 0; k < size; k++)
                {
                    cout << array[k] << "   ";
                }
                cout << endl;
                //                cout <<  "firstevenIndex = " << firstevenIndex <<"   oddIndex == " << oddIndex <<endl;
            }
            
        }
        
        kOperCount = 0;
    }
};
//=======================================

//输入一个链表，输出该链表中倒数第k个结点。

class Sample15 {
    
    template<typename T> struct LinkNode{
        
        T _value;
        LinkNode<T> *_next;
    };
    
};


class Sample10
{
public:
    string trim(string s)
    {
        if (s.empty())
        {
            return s;
        }
        
        s.erase(0, s.find_first_not_of(" "));
        return s.erase(s.find_last_not_of(" ") + 1);
        
        
        //        size_t pos = s.find_first_of(" ");
        //        if (pos == string::npos)
        //        {
        //            return s;
        //        }
    }
    
    
    bool isPositive(string a)
    {
        if (a.empty())
        {
            return true;
        }
        
        const char *ac = a.c_str();
        
        if (ac[0] == '-')
        {
            return false;
        }
        else
        {
            return true;
        }
        
    }
    
    string positiveIntStringAdd(string a, string b)
    {
        string aStr = trim(a);
        string bStr = trim(b);
        
        if (aStr.empty())
        {
            return bStr;
        }
        
        if (bStr.empty())
        {
            return aStr;
        }
        
        
        int al = (int)aStr.length();
        int bl = (int)bStr.length();
        
        if (al < bl)
        {
            return positiveIntStringAdd(bStr, aStr);
        }
        
        cout << aStr << " + " << bStr << " = ";
        
        int length = al > bl ? al + 3 : bl + 3;
        
        char *result = new char[length];
        bzero(result, length);
        
        memset(result, '0', length - 1);
        
        
        const char *astrc = aStr.c_str();
        const char *bstrc = bStr.c_str();
        int jw = 0;
        for (int i = bl - 1; i >= 0; i--)
        {
            int addIndex = al - (bl - i);
            int addRes = astrc[addIndex] - '0' + bstrc[i] - '0' + jw;
            
            int resindex = length - (bl - i);
            if (addRes >= 10)
            {
                jw = 1;
                
                result[resindex] = addRes - 10 + '0';
            }
            else
            {
                jw = 0;
                
                result[resindex] = addRes + '0';
            }
        }
        
        
        for (int k = al - bl - 1; k >= 0; k--)
        {
            int addRes = astrc[k] - '0' + jw;
            if (addRes >= 10)
            {
                jw = 1;
                result[length - bl - (al - bl - k)] = addRes - 10 + '0';
            }
            else
            {
                jw = 0;
                result[length - bl - (al - bl - k)] = addRes + '0';
            }
        }
        
        
        result[length - al - 1] = '0' + jw;
        
        int k = 0;
        for (int i = 0; i < length; i++)
        {
            k = i;
            if (result[i] != '0')
            {
                k -= 1;
                break;
            }
        }
        
        if (k == length - 1 )
        {
            return "0";
        }
        string resultStr(result + k);
        memcpy((void *)resultStr.c_str(), result + k, length - k);
//        free(result);
        return resultStr;
        
    }
    
    
    string positiveIntStringDec(string a, string b, bool isReverse = false)
    {
        string aStr = trim(a);
        string bStr = trim(b);
        
        if (aStr.empty())
        {
            return bStr;
        }
        
        if (bStr.empty())
        {
            return aStr;
        }
        
        
        int al = (int)aStr.length();
        int bl = (int)bStr.length();
        
        if (al < bl)
        {
            return "-" + positiveIntStringDec(bStr, aStr, true);
        }
        
        if (isReverse)
        {
            cout << bStr << " - " << aStr << " = ";
        }
        else
        {
            cout << aStr << " - " << bStr << " = ";
        }
        
        
        int length = al > bl ? al + 3 : bl + 3;
        
        char *result = new char[length];
        bzero(result, length);
        
        memset(result, '0', length - 1);
        
        const char *astrc = aStr.c_str();
        const char *bstrc = bStr.c_str();
        int jw = 0;
        for (int i = bl - 1; i >= 0; i--)
        {
            int addIndex = al - (bl - i);
            int addRes = 0;
            if ((astrc[addIndex]  + jw - '0') <  (bstrc[i] - '0'))
            {
                if ((addIndex - 1) >= 0)
                {
                
                    addRes = abs((astrc[addIndex] + 10 + jw - '0') - (bstrc[i] - '0'));
                    jw = -1;
                }
                else
                {
                    addRes = abs((astrc[addIndex] + jw - '0') - (bstrc[i] - '0'));
                    jw = -1;
                }
                
            }
            else
            {
                addRes = (astrc[addIndex] + jw - '0') - (bstrc[i] - '0');
                jw = 0;
            }
            
            int resindex = length - (bl - i);
            
            result[resindex] = addRes + '0';
            
        }
        
        
        for (int k = al - bl - 1; k >= 0; k--)
        {
            int addRes = astrc[k] + jw - '0' ;
            if (addRes < 0)
            {
                jw = -1;
                result[length - bl - (al - bl - k)] = abs(addRes) + 10  + '0';
            }
            else
            {
                jw = 0;
                result[length - bl - (al - bl - k)] = addRes + '0';
            }
        }
        
        if (jw == -1)
        {
            result[length - al - 1] = '-';
        }
        else
        {
            result[length - al - 1] = '0' + jw;
        }
        
       
        
        int k = 0;
        for (int i = 0; i < length; i++)
        {
            k = i;
            if (result[i] != '0')
            {
                break;
            }
        }
        
        if (k == length - 1 && result[k] == '0')
        {
            return "0";
        }
        
        
        string resultStr(result+k);
        memcpy((void *)resultStr.c_str(), result + k, length - k);
//        free(result);
        return resultStr;
        
    }
    
    string IntStringAdd(string a, string b)
    {
        // 判断两个数的正负；
        // 判断要用的方法；
        
        string aStr = trim(a);
        string bStr = trim(b);
        
        if (aStr.empty())
        {
            return bStr;
        }
        
        if (bStr.empty())
        {
            return aStr;
        }
        
        bool isAP = this->isPositive(aStr);
        bool isBP = this->isPositive(bStr);
        
        if (isAP == isBP)
        {
            // 作加法
            if (isAP)
            {
                return positiveIntStringAdd(aStr, bStr);
            }
            else
            {
                string aPStr = aStr.substr(1);
                string bPStr = bStr.substr(1);
                return "-" + positiveIntStringAdd(aPStr, bPStr);
            }
        }
        else
        {
            if (isAP)
            {
                string bPStr = bStr.substr(1);
                return positiveIntStringDec(aStr, bPStr);
            }
            else
            {
                string aPStr = aStr.substr(1);
                return positiveIntStringDec(bStr, aPStr);
            }
        }
    }
    
    //=================================
    // m [0,9]
    string  positiveIntStringMul(string a, int m)
    {
        string aStr = trim(a);
        
        if (aStr.empty())
        {
            return "0";
        }
        
        if (m == 0)
        {
            return "0";
        }
        
        bool isAPos = isPositive(a);
        bool isMPos = m > 0 ;
        if (isAPos != isMPos)
        {
            if (isAPos)
            {
                return "-" + positiveIntStringMul(a, abs(m));
            }
            else
            {
                string aPStr = aStr.substr(1);
                return "-" + positiveIntStringMul(aPStr, abs(m));
            }
            
            
        }
        else
        {
            if (!isAPos)
            {
                string aPStr = aStr.substr(1);
                return positiveIntStringMul(aPStr, abs(m));
            }
            
        }
        
        
        string mIntStr = to_string(m);
        
        size_t alen = aStr.length();
        size_t mlen = mIntStr.length();
        string midResStr = string("0");
        
        int jw = 0;
        int count = 0;
        do
        {
            int mw = m/10;
            
            if (mw == 0)
            {
                mw = m;
            }
            else
            {
                while (mw >= 10)
                {
                    mw = mw/10;
                }
            }
            
            char *temp = new char[aStr.length() + mlen];
            bzero(temp, aStr.length() + mlen);
            
            memset(temp, '0', aStr.length() + mlen - 1);
            size_t addIndex = 0;
            for (int i = alen - 1; i >= 0; i--)
            {
                addIndex = aStr.length() + mlen + i - alen;
                int addRes = 0;
                int ca = aStr[i]  - '0';
                addRes = ca * mw + jw;
                jw = addRes / 10;
                temp[addIndex] = addRes % 10 + '0';
            }
            
            if (jw != 0)
            {
                temp[addIndex  - 1] = '0' + jw;
            }
            
            cout << temp << endl;
            
            midResStr = positiveIntStringAdd(midResStr, string(temp));
            free(temp);
            
            if (m >= 10)
            {
               // 移位
                midResStr += to_string(0);
                m -= pow(10, mlen - count - 1);
                count++;
                
            }
            else
            {
                break;
            }
            
            cout << midResStr << endl;
           
        }while(m > 0);
        
        
        int k = 0;
        const char *result = midResStr.c_str();
        for (int i = 0; i < midResStr.length(); i++)
        {
            k = i;
            if (result[i] != '0')
            {
                break;
            }
        }
        
        if (k == midResStr.length() - 1 && result[k] == '0')
        {
            return "0";
        }
        
        
        string resultStr(result+k);
       
        memcpy((void *)resultStr.c_str(), result + k, midResStr.length() - k);
        
        return resultStr;
        
    }
};

int main2(int argc, const char * argv[]) {
    
//    char *cstr = "Hello world";
//
//
//
//    string str = string(cstr);
//    cout << str << endl;
//
//    return 0;
    cout << "Hello World" << endl;
    
    cout << "=============="<< endl;
    Sample10 s10;
    
    cout << s10.positiveIntStringMul("1221", 9) << endl;
    
//    cout << s10.IntStringAdd("-1", "2") << endl;
//    cout << s10.IntStringAdd("-1", "-2") << endl;
//    cout << s10.IntStringAdd("1", "-2") << endl;
//
//    cout << s10.IntStringAdd("-1", "-2222") << endl;
//
//    cout << s10.IntStringAdd("022220", "-02222") << endl;
//    cout << s10.IntStringAdd("0000222", "01110") << endl;
    
//    cout << s10.IntStringAdd("2222", "-22223332223333333") << endl;
//    cout << s10.IntStringAdd("2222", "-22223332223333334") << endl;
//    cout << s10.IntStringAdd("2222", "-22223332223333335") << endl;
//    cout << s10.IntStringAdd("2222", "-22223332223333336") << endl;
//    cout << s10.IntStringAdd("2222", "-22223332223333337") << endl;
//    cout << s10.IntStringAdd("2222", "-22223332223333331") << endl;
//    cout << s10.IntStringAdd("-2222", "-2333") << endl;
    
    
//    cout << s10.positiveIntStringDec("31", "2") << endl;
//    cout << s10.positiveIntStringDec("1", "2") << endl;
//    cout << s10.positiveIntStringDec("3", "2") << endl;
//    cout << s10.positiveIntStringDec("311111", "29111111111") << endl;
//    cout << s10.positiveIntStringDec("44444444444444444444444444444444444", "1234123412341234") << endl;
//    cout << s10.positiveIntStringAdd("44444444444444444444444444444444444", "4444444444444444444444444444444444444444444444444") << endl;
//    cout << s10.positiveIntStringDec("44", "444") << endl;
//    cout << s10.positiveIntStringDec("44444444444444444444444444444444444", "4444444444444444444444444444444444444444444444444") << endl;
//    cout << s10.positiveIntStringDec("44444444444444444444444444444444444", "555555555775757575757575111111111111111117577575757577575757575775757575757") << endl;
//    return 0;
    
    cout << s10.positiveIntStringAdd("0", "0") << endl;
    cout << s10.positiveIntStringAdd("2", "3") << endl;
    cout << s10.positiveIntStringAdd("12", "3") << endl;
    cout << s10.positiveIntStringAdd("9", "3") << endl;
    cout << s10.positiveIntStringAdd("91", "37") << endl;
    cout << s10.positiveIntStringAdd("91", "9") << endl;
    cout << s10.positiveIntStringAdd("12", "311") << endl;
    cout << s10.positiveIntStringAdd("12121212121212", "82311") << endl;
    cout << s10.positiveIntStringAdd("12121212121212121212121", "3121212121212121212122121212") << endl;
    
    cout << s10.positiveIntStringAdd("222222222222222222222222222222222222222222222222222222222222222222222", "123123123123123123123123123123123123") << endl;
    
    
    
    cout << "=============="<< endl;
    Sample11 s11;
    cout << s11.rectCover(3) << endl;
    cout << s11.rectCover(4) << endl;
    cout << s11.rectCover(5) << endl;
    cout << s11.rectCover(6) << endl;
    cout << s11.rectCover(7) << endl;
    
    
    Sample12 s12;
    cout << s12.numbleof1(15) << endl;
    cout << s12.numbleof1(-1) << endl;
    cout << s12.numbleof1(-15) << endl;
    cout << s12.numbleof1(-0) << endl;
    
    
    Sample13 s13;
    cout << s13.power(1, 0) << endl;
    cout << s13.power(2.2, 3) << endl;
    cout << s13.power(2, -1) << endl;
    cout << s13.power(2, -3) << endl;
    
    cout << "==============" << endl;
    cout << s13.powerv2(1.1, 0) << endl;
    cout << s13.powerv2(-2.2, 3) << endl;
    cout << s13.powerv2(2, -1) << endl;
    cout << s13.powerv2(2, -3) << endl;
    cout << s13.powerv2(-2, -1) << endl;
    cout << s13.powerv2(-2, -2) << endl;
    cout << s13.powerv2(-2, -3) << endl;
    
    
    cout << "==============" << endl;
    Sample14 s14;
    
    
    
    int dd1[4] = {1,2,4,3};
    s14.operArrayv2(dd1, 4);
    
    int qq2[8] = {2,4,1,5, 3, 6, 8, 7};
    s14.operArrayv2(qq2, 8);
    
    
    int a1[8] = {2,4,1,3,5,6,7,8};
    s14.operArrayv2(a1, 8);
    
    int b2[8] = {1,2,4,3,5,6,7,8};
    s14.operArrayv2(b2, 8);
    
    int b3[8] = {1,5,6,5,4,3,4,5};
    s14.operArrayv2(b3, 8);
    
    int b4[8] = {8,7,6,5,4,3,2,1};
    s14.operArrayv2(b4, 8);
    
    return 0;
}
