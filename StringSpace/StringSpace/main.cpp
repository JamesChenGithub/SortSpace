//
//  main.m
//  StringSpace
//
//  Created by AlexiChen on 2017/12/19.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class StringSample
{
public:

    // 暴力搜索
    int violenceSearchIndexOf(const string matchStr, const string patternStr)
    {
        int matchLen =  (int)matchStr.length();
        int patternLen = (int)patternStr.length();
        if (patternLen > matchLen)
        {
            return (int)(std::string::npos);
        }
        
        if (patternLen == 0) {
            return (int)(std::string::npos);
        }
        
        const char *matchCPtr = matchStr.c_str();
        const char *patternCPtr = patternStr.c_str();
        int count = 0;
        
        for (int i = 0; i < matchLen; i++)
        {
            int j = 0;
            int k = i;
            while (j < patternLen && k < matchLen)
            {
                char p = patternCPtr[j];
                char m = matchCPtr[k];
                cout << "第"<< ++count << "次比较： patternCPtr[" << j << "] (" << p <<") != matchCPtr[" << k << "] ("<< m <<")" << endl;
                if (p != m)
                {
                    break;
                }
                else
                {
                    j++;
                    k++;
                }
            }
            
            if (j == patternLen)
            {
                return i;
            }
        }
        
        
        return (int)(std::string::npos);
    }
    
    // 逆向暴力搜索
    int violenceReverseSearchIndexOf(const string matchStr, const string patternStr)
    {
        int matchLen =  (int)matchStr.length();
        int patternLen = (int)patternStr.length();
        if (patternLen > matchLen)
        {
            return (int)(std::string::npos);
        }
        
        if (patternLen == 0)
        {
            return (int)(std::string::npos);
        }
        
        const char *matchCPtr = matchStr.c_str();
        const char *patternCPtr = patternStr.c_str();
        int count = 0;
        
        int s_index = patternLen;
        int p_index = 0;
        
        while (s_index < matchLen)
        {
            p_index = patternLen;
            cout << "第"<< ++count << "次比较： patternCPtr[" << p_index-1 << "] (" << patternCPtr[p_index-1] <<") != matchCPtr[" << s_index-1 << "] ("<< matchStr[s_index-1] <<")" << endl;
            while (matchStr[--s_index] == patternCPtr[--p_index])
            {
                cout << "第"<< ++count << "次比较： patternCPtr[" << p_index << "] (" << patternCPtr[p_index] <<") != matchCPtr[" << s_index << "] ("<< matchStr[s_index] <<")" << endl;
                if (p_index == 0)
                {
                    return s_index;
                }
            }
            
            s_index += (patternLen - p_index) + 1;
//            cout << "第"<< count << "次比较 后 s_index = " << s_index << "    matchCPtr[" << s_index << "] ("<< matchStr[s_index] <<")"  << endl;
        }
        
        
        return (int)(std::string::npos);
    }
    
    
    
    // KMP搜索
    
    int get_next(const string pstr)
    {
        int plen = (int)pstr.length();
        int *next = new int[plen];
        
        int i = 0;
        int k = -1;
        
        int mlen = plen - 1;
        
        next[i] = k;
        while(i < mlen)
        {
            if((-1 == k) || (pstr[i] == pstr[k]))
            {
                next[++ i] = ++ k;
            }
            else
            {
                k = next[k];
            }
        }
        
        cout << pstr <<"  Next数组为:";
        for (int i = 0; i < plen; i++)
        {
            cout << "  " << next[i];
        }
        
        cout << endl;
        
        delete [] next;
        return plen;
    }
    
    void getNext(string ps, int  *nextPtr = nullptr, int n = 0)
    {
        
        if (nextPtr)
        {
            const char *psCPtr = ps.c_str();
            nextPtr[0] = -1;
            
            int i = 0;
            int k = -1;
            
            if (n == 0)
            {
                n = (int)ps.length();
            }
            
            while (i < (n - 1))
            {
                if (k == -1 || psCPtr[i] == psCPtr[k])
                {
                    nextPtr[++i] = ++k;
                }
                else
                {
                    k = nextPtr[k];
                }
            }
            
            cout << ps <<"  Next数组为:";
            for (int i = 0; i < n; i++)
            {
                cout << "  " << nextPtr[i];
            }
            
            cout << endl;
        }
        else
        {
            int len = (int)ps.length();
            int *next = new int[len];
            
            getNext(ps, next);
            
            delete [] next;
        }
    }
    
    
    int kmpSearchIndexOf(const string matchStr, const string patternStr)
    {
        int matchLen =  (int)matchStr.length();
        int patternLen = (int)patternStr.length();
        if (patternLen > matchLen)
        {
            return (int)(std::string::npos);
        }
        if (patternLen == 0)
        {
            return (int)(std::string::npos);
        }
        const char *matchCPtr = matchStr.c_str();
        const char *patternCPtr = patternStr.c_str();
        
        int *next = new int[patternLen];
        getNext(patternStr, next, patternLen);
        
        int j = 0;
        int i = 0;
        int count = 0;
        while (j < patternLen && i < matchLen)
        {
            char m = matchCPtr[i];
            char p = patternCPtr[j];
            
            cout << "第"<< ++count << "次比较： patternCPtr[" << j << "] (" << p <<") != matchCPtr[" << i << "] ("<< m <<")" << endl;
            
            if (j == -1 || p == m)
            {
                i++;
                j++;
            }
            else
            {
                j = next[j];
            }
            
        }
        
        delete [] next;
        
        if (j == patternLen)
        {
            return i - j;
        }
    
        
        
        return (int)(std::string::npos);
    }
    

    
    // BM算法
    
    
};

int main()
{
    StringSample ss;
    int index = 0;
    string matchStr = "BBC ABCDAB ABCDABCDABDE";
    string patternStr = "ABCDABD";
    
    cout << "========暴力搜索=======" <<  matchStr <<"  模式串：" << patternStr << endl;
    index = ss.violenceSearchIndexOf(matchStr, patternStr);
    cout << "搜索到 : " << index << endl;
    
    cout << "========逆向暴力搜索=======" <<  matchStr <<"  模式串：" << patternStr << endl;
    index = ss.violenceReverseSearchIndexOf(matchStr, patternStr);
    cout << "搜索到 : " << index << endl;

    cout << "========KMP搜索=======" <<  matchStr <<"  模式串：" << patternStr << endl;
    index = ss.kmpSearchIndexOf(matchStr, patternStr);
    cout << "搜索到 : " << index << endl;
    
//    cout << "========KMPV2搜索=======: 匹配串" <<  "ABCD" <<"  模式串：" << "BC" << endl;
//    index = ss.kmpSearchIndexOfV2("ABCD", "BC");
//    cout << "搜索到 : " << index << endl;

    
    
    cout << "======Next函数对比======" << "ABABCABAA" << endl;
    ss.getNext("ABABCABAA");
    
    ss.get_next("ABABCABAA");
    
    
    
    cout << "======Next函数对比======" << patternStr << endl;
    ss.getNext(patternStr);
    
    ss.get_next(patternStr);
    
    
    
    return 0;
}
