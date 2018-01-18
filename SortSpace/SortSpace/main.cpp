//
//  main.m
//  SortSpace
//
//  Created by AlexiChen on 2017/12/11.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

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


class Sample28
{
public:
    void MoreThanHalfNum_Solution(std::vector<int> vec)
    {
        std::sort(std::begin(vec), std::end(vec), [](int a, int b)->int{
            return b - a;
        });
        int count = (int)vec.size();
        int last = *vec.begin();
        bool succ = false;
        int t = 1;
        std::for_each(vec.begin() + 1, vec.end(), [&](int a){
            if (!succ)
            {
                if (last == a)
                {
                    t++;
                    if (t > count/2)
                    {
                        std::cout << "超半数的字为" << last << endl;
                        succ = true;
                    }
                }
                else
                {
                    t = 1;
                    last = a;
                }
            }
            
        });
        
        {
            int count = (int)vec.size();
            int last = *vec.begin();
            bool succ = false;
            int t = 1;
            int idex =  1;
            auto func = [&](int a)->bool{
                idex++;
                if (last == a)
                {
                    t++;
                    if (t > count/2)
                    {
                        succ = true;
                        return true;
                    }
                }
                else
                {
                    t = 1;
                    last = a;
                }
                return false;
            };
            
            auto findx = std::find_if(vec.begin() + 1, vec.end(), func);
            if (findx != vec.end())
            {
                std::cout << "超半数的字为" << *findx << endl;
            }
        }
        
    }
    
    //输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,。
    std::vector<int> getLeastNumbers_Solution(vector<int> input, int k)
    {
        std::vector<int> outvec;
        
        std::sort(input.begin(), input.end());
        std::for_each(input.begin(), input.end(), [](int a){std::cout << a << "  ";});
        std::cout << std::endl;
        
        auto iter = std::unique(input.begin(), input.end());
        while(iter != input.end())
        {
            input.erase(iter);
        }
        
        
        std::for_each(input.begin(), input.end(), [](int a){std::cout << a << "  ";});
        std::cout << std::endl;
        
        std::copy(input.begin(), input.begin() + k, std::back_inserter(outvec));
        
        std::for_each(outvec.begin(), outvec.end(), [](int a){std::cout << a << "  ";});
        std::cout << std::endl;
        
        return outvec;
    }
    
    int findGreatestSumOfSubArray(vector<int> array)
    {
        {
            std::cout << "====================" << std::endl;
            std::for_each(array.begin(), array.end(), [](int a) { std::cout << a << "  ";});
            std::cout << std::endl;
             std::cout << std::endl;
             std::cout << std::endl;
            // 穷举
            if (array.size() > 0)
            {
                
                std::vector<std::vector<int>> outmap;
                
                int i = 0;
                while(i < array.size())
                {
                
                    std::vector<int> outvec;
                    outvec.push_back(*(array.begin() + i));
                    int index = 0;
                    std::for_each(array.begin() + i + 1, array.end(), [&](int a){
                        outvec.push_back(outvec[index] + a);
                        index++;
                    });
                    
                    std::for_each(outvec.begin(), outvec.end(), [](int a) { std::cout << a << "  ";});
                    std::cout << std::endl;
                    
                    outmap.push_back(outvec);
                    i++;
                }
                
                int j = 0;
                auto temp = *outmap.begin();
                auto max = std::max_element(temp.begin(), temp.end());
                
                int maxIndex = j;
                int maxvecIndex = max - temp.begin();
                
                int maxint = *max;
                std::cout << "max sub sum : " << *max << endl;
                j++;
                while (j < outmap.size())
                {
                    std::cout << j << "=====>>>>>";
                    auto temp2 = *(outmap.begin() + j);
                    std::for_each(temp2.begin(), temp2.end(), [](int a) { std::cout << a << "  ";});
                    auto max2 = std::max_element(temp2.begin(), temp2.end());
                    std::cout << "==================>>>>>>   max is " << *max2  << "    " << outmap[maxIndex][maxvecIndex] << std::endl;
                    if (*max2  > maxint)
                    {
                        maxint = *max2;
                        maxIndex = j;
                        maxvecIndex = max2 - temp2.begin();
                        std::cout << "===>>>>>==>>>>>max sub sum : " << *max2 << "    " << outmap[maxIndex][maxvecIndex]  << "    " << maxint << endl;
                    }
                    j++;
                }
                
                
                std::cout << "<<<<< max sub sum : " << outmap[maxIndex][maxvecIndex]  << "    " << maxint << endl;
                return maxint;
            }
            std::cout << " ===================================" << std::endl;
            {
                // 动态规划：
                int max = -100000000;
                int curmax = 0;
                
                std::for_each(array.begin(), array.end(), [&](int a) {
                    if (curmax <= 0)
                    {
                        curmax = a;
                    }
                    else
                    {
                        curmax += a;
                    }
                    
                    if (max < curmax)
                    {
                        max = curmax;
                    }
                });
                
                std::cout << "max sub sum : " << max << endl;
            }
        }
        return 0;
    }
    
    int getUglyNum(int n)
    {
        if (n <= 0)
        {
            return 0;
        }
        
        if (n == 1)
        {
            return 1;
        }
        
        std::vector<int> ugleVec = {1};
        int p2 = 0;
        int p3 = 0;
        int p5 = 0;
        
        int nextIndex = 1;
        while (nextIndex < n)
        {
            int min = std::min({ugleVec[p2] * 2, ugleVec[p3] * 3, ugleVec[p5] * 5}, [](int a, int b)->bool{
                return a < b ? true : false;
                
            });
            ugleVec.push_back(min);
            
            while (ugleVec[p2] * 2 <= ugleVec[nextIndex]) {
                p2++;
            }
            
            while (ugleVec[p3] * 3 <= ugleVec[nextIndex]) {
                p3++;
            }
            
            while (ugleVec[p5] * 5 <= ugleVec[nextIndex]) {
                p5++;
            }
            
            nextIndex++;
            
        }
        
        return ugleVec[nextIndex - 1];
    }
    
    
    
    struct DisableCompare : public std::binary_function<char, char, bool>
    {
        bool operator()(char lhs, char rhs)  const
        {
            return true;
        }
    };
    
    char firstNotRepeatingChar(std::string str)
    {
        {
            int map[128];
            bzero(map, 128 * sizeof(int));
            const char *cstr = str.c_str();
            
            int i = 0;
            while (i < str.length())
            {
                char c = *(cstr + i);
                if (map[c] == 0)
                {
                    map[c] = 1;
                }
                else
                {
                    map[c] = -1;
                }
                i++;
            }
             i = 0;
            while (i < str.length())
            {
                char c = *(cstr + i);
                if (map[c] == 1)
                {
                    std::cout << str << "首次出现一次的字符是 :" <<  c << std::endl;
                    return c;
                }
                i++;
            }
            
            std::cout << str << "首次出现一次的字符是 : 未找到" << std::endl;
        }
        
        return 0;
    }
    
    char firstNotRepeatingChar2(std::string str)
    {
        std::unordered_map<char, int> map;
         const char *cstr = str.c_str();
        int i = 0;
        while (i < str.length())
        {
            char c = *(cstr + i);
            auto key = map.find(c);
            if (key == map.end()) {
                map[c] = 1;
            }
            else
            {
                key->second++;
            }
            i++;
        }
        
        
        
        std::for_each(map.cbegin(), map.cend(), [](std::pair<char, int> pair){
            cout << "key = " << pair.first << ", value =" << pair.second << std::endl;
        });
        
        std::for_each(map.begin(), map.end(), [](std::pair<char, int> pair){
            cout << "key = " << pair.first << ", value =" << pair.second << std::endl;
        });
        
        auto fk = std::find_if(map.cbegin(), map.cend(), [](std::pair<char, int> pair)->bool{
            if (pair.second == 1)
            {
                return true;
            }
            return false;
        });
        if (fk != map.cend())
        {
        
            std::cout << str << "首次出现一次的字符是 :" <<  fk->first << std::endl;
        }
        else
        {
            std::cout << str << "首次出现一次的字符是 : 未找到" << std::endl;
        }
        return 0;
    }
};


int main(int argc, const char * argv[]) {
    Sample28 s28;
//    s28.MoreThanHalfNum_Solution(std::vector<int>{1,2,3,2,2,2,5,4,2});
//    s28.getLeastNumbers_Solution({4,5,1,6,2,7,3,8,11,23,1,2,2,3}, 4);
////    s28.findGreatestSumOfSubArray({6,-3,-2,7,-15,1,2,2});
//
//    s28.findGreatestSumOfSubArray({-6,-3,-2,-7,-15,-1,-2,-2});
//
//    std::cout << "=======获取丑数========" << std::endl;
//    for (int i = 0; i < 10; i++)
//    {
//        std::cout << "第" << i << "个丑数是:" << s28.getUglyNum(i) << std::endl;
//    }
    
    std::string test = "baidu";
    s28.firstNotRepeatingChar(test);
    s28.firstNotRepeatingChar2(test);
    
    test = "google";
    s28.firstNotRepeatingChar(test);
    s28.firstNotRepeatingChar2(test);
    
    test = "dcba";
    s28.firstNotRepeatingChar(test);
    s28.firstNotRepeatingChar2(test);
    
    test = "dcbadcb";
    s28.firstNotRepeatingChar(test);
    s28.firstNotRepeatingChar2(test);
    
    return 0;
    
    
    
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
