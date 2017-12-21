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
#include <map>

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
                if (p_index != (patternLen - 1))
                {
                    cout << "第"<< ++count << "次比较： patternCPtr[" << p_index << "] (" << patternCPtr[p_index] <<") != matchCPtr[" << s_index << "] ("<< matchStr[s_index] <<")" << endl;
                }
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
    // 坏字符匹配
    /* 函数：void buildBadC(char *, int, int*)
     * 目的：根据好后缀规则做预处理，建立一张好后缀表
     * 参数：
     * pattern => 模式串P
     * plen => 模式串P长度
     * shift => 存放坏字符规则表,长度为的int数组
     */
    void buildBadC(const string ps, unsigned char *badShift = nullptr, int shiftlength = 256)
    {
        if (badShift)
        {
            
            int psLen = (int)ps.length();
            
            memset(badShift, psLen, sizeof(unsigned char) * shiftlength);
            
            const char *psPtr = ps.c_str();
            while (psLen > 0)
            {
                *(badShift + (unsigned char)*psPtr) = --psLen;
                cout << (unsigned char)*psPtr << " bad value : "  <<(int )(*(badShift + (unsigned char)*psPtr))  << endl;
                psPtr++;
            }
            
            cout << endl;
            for (int i = 0; i < shiftlength; i++)
            {
                if ((int)badShift[i]  != (int)ps.length())
                {
                    cout << (unsigned char) i << " bad value : "  << (int)badShift[i]  << endl;
                }
            }
            cout << endl;
        }
        else
        {
            int len = 256;
            unsigned char *next = new unsigned char[len];
            
            buildBadC(ps, next, len);
            
            delete [] next;
        }
    }
    
    /*bref 查找出模式串patn在主串src中第一次出现的位置
    return patn在src中出现的位置，当src中并没有patn时，返回-1*/
    
    int bmBadSearchIndexOf(const string macthStr, const string patternStr, unsigned char *shift = nullptr, int shiftLen = 256)
    {
        int plen = (int)patternStr.length();
        if (plen == 0)
        {
            return -1;
        }
        
        if (plen > macthStr.length())
        {
            return -1;
        }
        
        bool newshift = false;
        if (shift == nullptr)
        {
            newshift =true;
            shiftLen = 256;
            shift = new unsigned char[shiftLen];
        }
        
        buildBadC(patternStr, shift, shiftLen);
        
        
        int m_idx = plen, p_idx;
        int skip;
        
        const char *mPtr = macthStr.c_str();
        const char *pPtr = patternStr.c_str();
        
        int count = 0;
        
        int mlen = (int) macthStr.length();
        while (m_idx <= mlen)
        {
            p_idx = plen;
            cout << "第"<< ++count << "次比较： patternCPtr[" << m_idx-1 << "] (" << pPtr[p_idx-1] <<") != matchCPtr[" << m_idx-1 << "] ("<< mPtr[p_idx-1] <<")" << endl;
            while (mPtr[--m_idx] == pPtr[--p_idx])
            {
                if (p_idx != (plen - 1))
                {
                    cout << "第"<< ++count << "次比较： patternCPtr[" << m_idx-1 << "] (" << pPtr[p_idx-1] <<") != matchCPtr[" << m_idx-1 << "] ("<< mPtr[p_idx-1] <<")" << endl;
                }
                if (p_idx == 0)
                {
                    if (newshift)
                    {
                        delete [] shift;
                    }
                    return m_idx;
                }
            }
            
            
            unsigned char m_idx_c = mPtr[m_idx];
            skip = shift[m_idx_c];
            m_idx += (skip > (plen - p_idx)) ? skip : plen - p_idx;
            m_idx += 1;
            
        }
        
        if (newshift)
        {
            delete [] shift;
        }
        
        return -1;
    }
    
    void buildBadCMap(const string ps, map<unsigned char, int> &badMap)
    {
        int psLen = (int)ps.length();
        const char *psPtr = ps.c_str();
        while (psLen > 0)
        {
            unsigned char pc = (unsigned char)(*psPtr);
            cout << pc << " bad value : "  << psLen - 1  << endl;
            badMap.erase(pc);
            badMap.insert(make_pair(pc, --psLen));
            psPtr++;
        }
        
        cout << endl;
        std::for_each(badMap.begin(), badMap.end(), [](std::pair<unsigned char, int> n){
            cout << n.first << " bad value : "  << n.second  << endl;
        });
    }
    
    int bmBadMapSearchIndexOf(const string macthStr, const string patternStr)
    {
        int plen = (int)patternStr.length();
        if (plen == 0)
        {
            return -1;
        }
        
        if (plen > macthStr.length())
        {
            return -1;
        }
        
        map<unsigned char, int> badmap;
        
        
        buildBadCMap(patternStr, badmap);
        
        
        int m_idx = plen, p_idx;
        int skip;
        
        const char *mPtr = macthStr.c_str();
        const char *pPtr = patternStr.c_str();
        
        int count = 0;
        
        int mlen = (int) macthStr.length();
        while (m_idx <= mlen)
        {
            p_idx = plen;
            cout << "第"<< ++count << "次比较： patternCPtr[" << m_idx-1 << "] (" << pPtr[p_idx-1] <<") != matchCPtr[" << m_idx-1 << "] ("<< mPtr[p_idx-1] <<")" << endl;
            while (mPtr[--m_idx] == pPtr[--p_idx])
            {
                if (p_idx != (plen - 1))
                {
                    cout << "第"<< ++count << "次比较： patternCPtr[" << m_idx-1 << "] (" << pPtr[p_idx-1] <<") != matchCPtr[" << m_idx-1 << "] ("<< mPtr[p_idx-1] <<")" << endl;
                }
                if (p_idx == 0)
                {
                    return m_idx;
                }
            }
            
            
            unsigned char m_idx_c = mPtr[m_idx];
            skip = badmap.find(m_idx_c) == badmap.end() ? (int)patternStr.length() : badmap.at(m_idx_c);
            m_idx += (skip > (plen - p_idx)) ? skip : plen - p_idx;
            m_idx += 1;
            
        }
        
        return -1;
    }
    
    
    void buildSundayMap(const string ps, map<unsigned char, int> &badMap)
    {
        int psLen = (int)ps.length();
        const char *psPtr = ps.c_str();
        int i = 0;
        while (i < psLen)
        {
            unsigned char pc = (unsigned char)(*(psPtr + i));
            cout << pc << " bad value : "  << i << endl;
            badMap.erase(pc);
            badMap.insert(make_pair(pc, i));
            i++;
        }
        
        cout << endl;
        std::for_each(badMap.begin(), badMap.end(), [](std::pair<unsigned char, int> n){
            cout << n.first << " bad value : "  << n.second  << endl;
        });
    }
    
    int SundaySearch(const string macthStr, const string patternStr)
    {
        int plen = (int)patternStr.length();
        if (plen == 0)
        {
            return -1;
        }
        
        if (plen > macthStr.length())
        {
            return -1;
        }
        
        map<unsigned char, int> badmap;
        
        
        buildSundayMap(patternStr, badmap);
        
        int matcnLen = (int)macthStr.length();
        int patternLen = (int)patternStr.length();
        
        const char *mPtr = macthStr.c_str();
        const char *pPtr = patternStr.c_str();
        
        int count = 0;
        
        cout << macthStr << endl;
        cout << patternStr << endl;
        for (int nBegin = 0 ; nBegin < matcnLen - patternLen; )
        {
            int i = nBegin, j = 0;
            
            bool flag = false;
            if (mPtr[nBegin + plen - 1] == pPtr[plen - 1])
            {
            
                cout << "第"<< ++count << "次比较： patternCPtr[" << plen - 1 << "] (" << pPtr[plen - 1] <<") != matchCPtr[" << nBegin + plen - 1 << "] ("<< mPtr[nBegin + plen - 1] <<")" << endl;
                for (; j < patternLen - 1 && i < matcnLen && mPtr[i] == pPtr[j]; i++, j++)
                {
                    flag = true;
                    cout << "第"<< ++count << "次比较： patternCPtr[" << j << "] (" << pPtr[j] <<") == matchCPtr[" << i << "] ("<< mPtr[j] <<")" << endl;
                }
                
                if (!flag)
                {
                    cout << "第"<< ++count << "次比较： patternCPtr[" << j << "] (" << pPtr[j] <<") != matchCPtr[" << i << "] ("<< mPtr[j] <<")" << endl;
                }
            }
            else
            {
                cout << "第"<< ++count << "次比较： patternCPtr[" << plen - 1 << "] (" << pPtr[plen - 1] <<") != matchCPtr[" << nBegin + plen - 1 << "] ("<< mPtr[nBegin + plen - 1] <<")" << endl;
            }
            
            
            
            
            
            if (j == patternLen)
            {
                return nBegin;
            }
            
            if (nBegin + patternLen > matcnLen)
            {
                return -1;
            }
            else
            {
                
                unsigned char pc = mPtr[nBegin + patternLen];
                
                int skip = badmap.find(pc) == badmap.end() ? -1 : badmap.at(pc);
                
                nBegin += patternLen - skip;
                
                cout << pc << "后移" << patternLen << " - " <<  skip << " = " << patternLen - skip << endl;
                
                cout << macthStr << endl;
                
                int ai = 0;
                while (ai++ < nBegin)
                {
                    cout << " ";
                }
                cout << patternStr << endl;
            }
        }
        
        return -1;
    }
    
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
    
    
    cout << "========BM Bad搜索=======" <<  matchStr <<"  模式串：" << patternStr << endl;
    index = ss.bmBadSearchIndexOf(matchStr, patternStr);
    cout << "搜索到 : " << index << endl;
    
    cout << "========BM BadMap搜索=======" <<  matchStr <<"  模式串：" << patternStr << endl;
    index = ss.bmBadMapSearchIndexOf(matchStr, patternStr);
    cout << "搜索到 : " << index << endl;
    
    cout << "========Sunday 搜索=======" <<  matchStr <<"  模式串：" << patternStr << endl;
    index = ss.SundaySearch(matchStr, patternStr);
    cout << "搜索到 : " << index << endl;
    
    
    cout << "========BM Bad 表======= :" << patternStr  << endl;
    ss.buildBadC(patternStr);
    
    std::map<unsigned char, int> map;
    ss.buildBadCMap(patternStr, map);
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
