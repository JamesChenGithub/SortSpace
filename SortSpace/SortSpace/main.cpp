//
//  main.m
//  SortSpace
//
//  Created by AlexiChen on 2017/12/11.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//

#include <iostream>
#include <stdio.h>

using namespace std;
// 从小到大排序
class SortSample
{

public:
    void print(int a[], int n, int num = 0)
    {
        cout << "第" << num << "排序结果：";
        for (int k = 0; k < n; k++) {
            cout << a[k] << "  ";
        }
        cout << endl;
    }
    
public:
    // 冒泡排序
    void bubbleSort(int a[], int n)
    {
        for (int i = 0; i < n; i++)
        {
            int temp = a[i];
            int k = i;
            for (int j = i+1; j < n; j++)
            {
                if (a[j] < temp)
                {
                    temp = a[j];
                    k = j;
                }
            }
            
            if (temp < a[i])
            {
                a[k] = a[i];
                a[i] = temp;
            }
           
            
            
            print(a, n, i);
        }
    }
    
    // 插入排序
    void insertSort(int a[], int n)
    {
        for (int i = 1; i < n; i++)
        {
            int temp = a[i];
            int k = i;
            for (int j = i ; j > 0 && a[j - 1] > temp; j--)
            {
                a[j] = a[j-1];
                k = j-1;
            }
            
            a[k] = temp;
            
            print(a, n, i);
        }
    }
    
    
    // shell排序
    void shellSort(int a[], int n)
    {
        int d = n;
        
        int count = 0;
        while (true)
        {
            d = d/2;
            for (int x = 0; x < d; x++)
            {
                // 按d增量作插排
                for (int i = x + d; i < n; i += d)
                {
                    int temp = a[i];
                    int j = i - d;
                    for ( ; j >= 0 && a[j] > temp; j -= d)
                    {
                        a[j + d] = a[j];
                    }
                    
                    a[j + d] = temp;
                }
                
            }
            
            print(a, n, ++count);
            if (d == 1)
            {
                break;
            }
        }
    }
    
    // 简单选择排序
    void simpleSort(int a[], int n)
    {
        for (int i = 0; i < n; i++)
        {
            int index = i;
            for (int j = i + 1; j < n; j++)
            {
                if (a[i] > a[j])
                {
                    index = j;
                }
            }
            
            if (index != i)
            {
                int t = a[i];
                a[i] = a[index];
                a[index] = t;
            }
            
            print(a, n, i);
        }
    }
    
    
    // 堆选择排序
    void heapSort(int a[], int n)
    {
        
    }
    
    
    
};

int main(int argc, const char * argv[]) {
   
    
    const int kArraySize = abs(rand()%100) + 10;
    int *array = new int[kArraySize];
    memset(array, 0, kArraySize);

    for (int k = 0; k < kArraySize; k++)
    {
        array[k] = abs(rand()%1000) + 10;
    }

    SortSample ss;
    ss.print(array, kArraySize);
    
    cout << "=======冒泡排序======" << endl;
    
    int bubbleArray[kArraySize];
    memcpy(bubbleArray, array, 100);
    ss.bubbleSort(bubbleArray, kArraySize);
    
    
    cout << "=======插入排序======" << endl;
    ss.print(array, kArraySize);
    int insertArray[kArraySize];
    memcpy(insertArray, array, 100);
    ss.insertSort(insertArray, kArraySize);
    
    cout << "=======Shell排序======" << endl;
    ss.print(array, kArraySize);
    int shellArray[kArraySize];
    memcpy(shellArray, array, 100);
    ss.shellSort(shellArray, kArraySize);
    
    
    cout << "======= 简单排序======" << endl;
    ss.print(array, kArraySize);
    int simpleArray[kArraySize];
    memcpy(simpleArray, array, 100);
    ss.simpleSort(simpleArray, kArraySize);
    
    
    free(array);
    array = nullptr;
    
    
    return 0;
}
