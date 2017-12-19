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
    
    void swap(int &a, int &b)
    {
        b = a + b;
        a = b - a;
        b = b - a;
    }
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
    
    void bubbleSortV2(int a[], int n)
    {
        bool flag = true;
        int k = n;
        while (flag)
        {
            flag = false;
            
            for (int i = 1; i < k; i++)
            {
                if (a[i-1] > a[i])
                {
                    swap(a[i-1], a[i]);
                    flag = true;
                }
            }
            k--;
            print(a, n, n-k);
        }
        
        bool succ = check(a, n);
        cout << "排序" << (succ ? "成功" : "失败") << endl;
        
    }
    
    void bubbleSortV3(int a[], int n)
    {
        int flag = n;
        int k = n;
        while (flag > 0)
        {
            flag = 0;
            
            for (int i = 1; i < k; i++)
            {
                if (a[i-1] > a[i])
                {
                    swap(a[i-1], a[i]);
                    flag = i;
                }
            }
            k--;
            print(a, n, n-k);
        }
        
        bool succ = check(a, n);
        cout << "排序" << (succ ? "成功" : "失败") << endl;
        
    }
    
    
    // 插入排序
    void insertSort(int a[], int n)
    {
        for (int i = 1; i < n; i++)
        {
            if (a[i - 1] > a[i])
            {
                int temp = a[i];
                int k = i;
                for (int j = i ; j > 0 && a[j - 1] > temp; j--)
                {
                    a[j] = a[j-1];
                    k = j-1;
                }
                
                a[k] = temp;
            }
            
            
            print(a, n, i);
        }
        bool succ = check(a, n);
        cout << "排序" << (succ ? "成功" : "失败") << endl;
    }
    
    void insertSortV2(int a[], int n)
    {
        for (int i = 1; i < n; i++) {
            for(int j = i - 1; j >= 0 && a[j] > a[j+1]; j--){
                swap(a[j], a[j+1]);
            }
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
    
    void shellSortV2(int a[], int n)
    {
        for (int gap = n/2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i++) {
                for(int j = i - gap; j >= 0 && a[j] > a[j+gap]; j-= gap){
                    swap(a[j], a[j+gap]);
                }
            }
            print(a, n, gap);
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
                swap(a[i], a[index]);
            }
            
            print(a, n, i);
        }
        
        bool succ = check(a, n);
        cout << "排序" << (succ ? "成功" : "失败") << endl;
    }
    
    
    // 快排序
    
    int quickPartitionPivot(int a[], int n, int low, int heigh)
    {
        
        cout << "==========" << endl;
        if (low < heigh)
        {
            
            int pos = low;
            int left = low;
            int right = heigh;
            int pivotValue = a[pos];
            
            while (left < right)
            {
                while (left < right && a[right] >= pivotValue)
                {
                    right--;
                }
                
                if (left < right)
                {
                    a[left++] = a[right];
                }
                
                print(a, n);
                
                while (left < right && a[left] <= pivotValue)
                {
                    left++;
                }
                
                if (left < right)
                {
                    a[right--] = a[left];
                }
                print(a, n);
            }
            
            a[left] = pivotValue;
            print(a, n);
            return left;
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
                quickSort(a, n, low, pivot-1);
                quickSort(a, n, pivot + 1, heigh);
               
            }
        }
        
        print(a, n);
    }
    
    
    
    // 堆排
    
    // 合并排序
    void mergeArray(int a[], int left, int mid, int right)
    {
        
        int *temp = new int[(right - left + 1)];
        
        if (a[mid] <= a[mid + 1])
        {
            return;
        }
        else
        {
            print(a+left, right - left+1);
            int i = left;
            int j = mid + 1;
            int k = 0;
            while (i <= mid && j <= right)
            {
                if (a[i] <= a[j])
                {
                    temp[k++] = a[i++];
                }
                else
                {
                    temp[k++] = a[j++];
                }
            }
            
            while (i <= mid)
            {
                temp[k++] = a[i++];
            }
            
            while (j <= right)
            {
                temp[k++] = a[j++];
            }
            
            
            memcpy(a+left, temp, sizeof(int) * (right - left + 1));
        }
//        print(temp, right - left + 1);
        free(temp);
        temp = nullptr;
    }
    
    void mergeSort(int a[], int left, int right)
    {
        if (left < right)
        {
            cout << " left = " << left <<  ", right = " << right << endl;
            int mid = (left + right)/2;
            
            if (mid != left)
            {
                mergeSort(a, left, mid);
//                print(a + left, right - left+1);
            }
            
            
            if (mid + 1 != right)
            {
                mergeSort(a, mid+1, right);
                
//                print(a + left, right - left+1);
            }
            
            mergeArray(a, left, mid, right);
            
            print(a + left, right - left+1);
        }
    }
    
    void mergeSort(int a[], int n)
    {
        mergeSort(a, 0, n-1);
    }
    
    
    // 基排序
    
    
    // 一个大小为n的数组，里面的数的范围在[0, n - 1], 有不确定的重复远元素，找到到至少一个重复元素；
    void checkHasRepeat(int array[], int n)
    {
        int a[n];
        memcpy(a, array, sizeof(a));
        
        
        for (int i = 0; i < n; i++)
        {
            
            while (i != a[i])
            {
                if (a[i] == a[a[i]])
                {
                    cout << "找到重复元素:" << a[i] << endl;
                    break;
                }
                swap(a[i], a[a[i]]);
                
                print(a, n, i);
            }
        }
    }
    
    void buildHeap(int array[], int heapSize)
    {
        int parent = (heapSize-1)/2;
        for (int i = parent; i >= 0; i--)
        {
            maxHeapAdjust(array, heapSize, i);
        }
    }
    
    void buildHeapV2(int array[], int heapSize)
    {
        int parent = (heapSize-1)/2;
        for (int i = parent; i >= 0; i--)
        {
            maxHeapAdjustV2(array, heapSize, i);
        }
    }
    
    void maxHeapAdjust(int array[], int heapSize, int index)
    {
        
        int imax = index;
        int iLeft = 2*index + 1;
        int iRight = 2*index + 2;
        
        if (iLeft < heapSize && array[iLeft] > array[index])
        {
            imax = iLeft;
        }
        
        if (iRight < heapSize && array[iRight] > array[imax]) {
            
            imax = iRight;
        }
        
        if (imax != index)
        {
            swap(array[index], array[imax]);
            
            maxHeapAdjust(array, heapSize, imax);
        }
    }
    
    void maxHeapAdjustV2(int array[], int heapSize, int index)
    {
        int imax, iLeft, iRight;
        while (true)
        {
             imax = index;
             iLeft = 2*index + 1;
             iRight = 2*index + 2;
            
            if (iLeft < heapSize && array[iLeft] > array[index])
            {
                imax = iLeft;
            }
            
            if (iRight < heapSize && array[iRight] > array[imax]) {
                imax = iRight;
            }
            
            if (imax != index)
            {
                swap(array[index], array[imax]);
                index = imax;
            }
            else
            {
                break;
            }
        }
    }
    
    
    
    void heapSort(int array[], int n)
    {
        buildHeap(array, n);
        
        for (int i = n - 1; i > 0; i--)
        {
            swap(array[0], array[i]);
            maxHeapAdjust(array, i, 0);
        }
        
        bool succ = check(array, n);
        cout << "排序" << (succ ? "成功" : "失败") << endl;
    }
    
    void heapSortV2(int array[], int n)
    {
        buildHeapV2(array, n);
        
        for (int i = n - 1; i > 0; i--)
        {
            swap(array[0], array[i]);
            maxHeapAdjustV2(array, i, 0);
        }
        
        bool succ = check(array, n);
        cout << "排序" << (succ ? "成功" : "失败") << endl;
    }
};

int main(int argc, const char * argv[]) {
   
    
    const int kArraySize = abs(rand()%50) ;
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

    cout << "=======冒泡2排序======" << endl;
    memcpy(bubbleArray, array, sizeof(bubbleArray));
    ss.bubbleSortV2(bubbleArray, kArraySize);
    
    cout << "=======冒泡3排序======" << endl;
    memcpy(bubbleArray, array, sizeof(bubbleArray));
    ss.bubbleSortV3(bubbleArray, kArraySize);
    
    
    int bt[10] = {2,1,3,4,5,6,7,8,9,10};
    cout << "=======冒泡2排序======" << endl;
    ss.bubbleSortV2(bt, 10);
    cout << "=======冒泡3排序======" << endl;
    ss.bubbleSortV3(bt, 10);
    int bt2[10] = {1,2,3,4,5,6,7,8,9,10};
    cout << "=======冒泡2排序======" << endl;
    ss.bubbleSortV2(bt, 10);
    cout << "=======冒泡3排序======" << endl;
    ss.bubbleSortV2(bt, 10);

    cout << "=======插入排序======" << endl;
    ss.print(array, kArraySize);
    int insertArray[kArraySize];
    memcpy(insertArray, array, sizeof(insertArray));
    ss.insertSort(insertArray, kArraySize);
    cout << "=======插入排序V2======" << endl;
    memcpy(insertArray, array, sizeof(insertArray));
    ss.insertSortV2(insertArray, kArraySize);
    

    cout << "=======Shell排序======" << endl;
    ss.print(array, kArraySize);
    int shellArray[kArraySize];
    memcpy(shellArray, array, sizeof(shellArray));
    ss.shellSort(shellArray, kArraySize);
    
    cout << "=======Shell V2排序======" << endl;
    memcpy(shellArray, array, sizeof(shellArray));
    ss.shellSortV2(shellArray, kArraySize);
    
    
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
    
    
    cout << "======= 归并排序======" << endl;
    ss.print(array, kArraySize);
    int mergeArray[kArraySize];
    memcpy(mergeArray, array, sizeof(mergeArray));
    ss.mergeSort(mergeArray, kArraySize);
    ss.print(mergeArray, kArraySize);
    
    cout << "======= 堆排序======" << endl;
    ss.print(array, kArraySize);
    int heapArray[kArraySize];
    memcpy(heapArray, array, sizeof(heapArray));
    ss.heapSort(heapArray, kArraySize);
    ss.print(heapArray, kArraySize);
    
    cout << "======= 堆排序V2======" << endl;
    ss.print(array, kArraySize);
    int heapArrayv2[kArraySize];
    memcpy(heapArrayv2, array, sizeof(heapArrayv2));
    ss.heapSortV2(heapArrayv2, kArraySize);
    ss.print(heapArrayv2, kArraySize);
    
    
    
    
    free(array);
    array = nullptr;
    
    
    
//    int arr[6] = {3, 1, 4, 2, 6,5};
//    ss.quickSort(arr, 6, 0, 5);
//
//    int arr2[6] = {3, 1, 4, 2, 6,5};
//    ss.mergeSort(arr2, 6);
//
//    const int kSize = abs(rand()%50) ;
//    int *tesArray = new int[kSize];
//    memset(tesArray, 0, kArraySize);
//
//    for (int k = 0; k < kSize; k++)
//    {
//        tesArray[k] = abs(rand()%kSize);
//    }
//
//    ss.print(tesArray, kSize);
//    ss.checkHasRepeat(tesArray, kSize);
//
//    int temp[3] = {0,1,2};
//    ss.checkHasRepeat(temp, 3);
//
//
//    free(tesArray);
//    tesArray = nullptr;
    
    return 0;
}
