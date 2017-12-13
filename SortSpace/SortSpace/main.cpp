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
    
    bool check(int a[], int n)
    {
        int i = 0;
        while (i < (n-1) && a[i++] <= a[i]);
        
        
        bool isSorted = i == (n - 1);
        
        return isSorted;
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
        bool succ = check(a, n);
        cout << "排序" << (succ ? "成功" : "失败") << endl;
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
        bool succ = check(a, n);
        cout << "排序" << (succ ? "成功" : "失败") << endl;
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
        
        bool succ = check(a, n);
        cout << "排序" << (succ ? "成功" : "失败") << endl;
    }
    
    // 简单选择排序
    void simpleSort(int a[], int n)
    {
        for (int i = 0; i < n; i++)
        {
            int index = i;
            int temp = a[index];
            for (int j = i + 1; j < n; j++)
            {
                if (temp > a[j])
                {
                    temp = a[j];
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
        
        bool succ = check(a, n);
        cout << "排序" << (succ ? "成功" : "失败") << endl;
    }
    
    
    // 堆选择排序
    
    int quickPartitionPivot(int a[], int n, int low, int heigh)
    {
        if (low < heigh)
        {
            
            int pos = low;
            int left = pos + 1;
            int right = heigh;
            int pivotValue = a[pos];
            
            while (true)
            {
                while (a[left] <= pivotValue)
                {
//                    a[left - 1] = a[left];
                    left++;
                }
                a[left - 1] = pivotValue;
                
                while (a[right] >= pivotValue) {
                    right--;
                }
                
                
                if (left >= right)
                {
                    break;
                }
                
//                int temp = a[left];
//                a[left] = a[right];
//                a[right] = temp;
                
            }
            
            return right;
        }
        
        
        print(a, n);
        
        return -1;
        
    }
    
    void quickSort(int a[], int n, int low, int heigh)
    {
        if (low < heigh)
        {
            int pivot = quickPartitionPivot(a, n, low, heigh);
            
            if (pivot >= low && pivot <= heigh)
            {
                quickSort(a, n, low, pivot - 1);
                quickSort(a, n, pivot + 1, heigh);
               
            }
        }
        
        print(a, n);
    }
    
    
    
    
    
    
};

int main(int argc, const char * argv[]) {
   
    
    const int kArraySize = abs(random()%20) ;
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
    memcpy(bubbleArray, array, sizeof(bubbleArray));
    ss.print(bubbleArray, kArraySize);
    ss.bubbleSort(bubbleArray, kArraySize);


    cout << "=======插入排序======" << endl;
    ss.print(array, kArraySize);
    int insertArray[kArraySize];
    memcpy(insertArray, array, sizeof(insertArray));
    ss.insertSort(insertArray, kArraySize);

    cout << "=======Shell排序======" << endl;
    ss.print(array, kArraySize);
    int shellArray[kArraySize];
    memcpy(shellArray, array, sizeof(shellArray));
    ss.shellSort(shellArray, kArraySize);
    
    
    cout << "======= 简单排序======" << endl;
    ss.print(array, kArraySize);
    int simpleArray[kArraySize];
    memcpy(simpleArray, array, sizeof(simpleArray));
    ss.simpleSort(simpleArray, kArraySize);
    
    
    cout << "======= 快排序======" << endl;
    const int kQASize = kArraySize;
    int quickArray[kQASize];
    ss.print(array, kQASize);
    memcpy(quickArray, array, sizeof(quickArray));
    ss.quickSort(quickArray, kArraySize, 0, kArraySize - 1);
    bool succ = ss.check(quickArray, kArraySize);
    cout << "排序" << (succ ? "成功" : "失败") << endl;
    
    int arr[3] = {817, 259, 83};
    ss.quickSort(arr, 3, 0, 3 - 1);
    
//    free(array);
//    array = nullptr;
    
    
    return 0;
}
