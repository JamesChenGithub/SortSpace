//
//  main4.cpp
//  CPP
//
//  Created by AlexiChen on 2017/12/8.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <stack>
#include <math.h>
#include <iostream>
#include <map>
#include <list>


using namespace std;

class Sample21
{
    typedef struct TreeNode {
        int      value;
        TreeNode *left;
        TreeNode *right;
    } *TreeRoot;
    
};

class Sample22
{
private:
    void swap(char *a, char *b)
    {
        char temp = *a;
        *a = *b;
        *b = temp;
    }
    void allrange(char *&str, int start, int length, vector<string> &mutaResult)
    {
        if (start == length - 1)
        {
            mutaResult.push_back(str);
        }
        else
        {
            for(int i = start; i < length; i++)
            {
                swap(&str[start], &str[i]);
                allrange(str, start + 1, length, mutaResult);
                swap(&str[start], &str[i]);
            }
        }
    }
public:
    void permutation(string str, vector<string> &mutaResult)
    {
        if (str.length() == 0)
        {
            return;
        }
        
        char *strc = (char *)str.c_str();
        
        allrange(strc, 0, str.length(), mutaResult);
    }
};

class Sample23
{
private:
    long value[100];
    int lastn;
public:
    Sample23()
    {
        value[0] = 0;
        value[1] = 1;
        lastn = 2;
    }
    long func(int n)
    {
        
        if (n == 0)
        {
            return value[0];
        }
        else if (n == 1)
        {
            return value[1];
        }
        else
        {
            if (value[n] == 0)
            {
                for (int i = lastn; i <= n; i++)
                {
                    value[i] = value[i-1] + value[i - 2];
                    cout << value[i] << "  ";
                }
                cout << endl;
                lastn = n;
            }
            
            return value[n];
        }
    }
};


int main()
{
    Sample23 s23;
    
    long resulta = s23.func(90);
    cout << resulta << endl;
    cout << "==========" << endl;
    Sample22 s22;
    
    vector<string> result;
    s22.permutation("abcde", result);
    
    std::for_each(result.begin(), result.end(), [](string str){
        cout << str << endl;
    });
    return 0;
}
