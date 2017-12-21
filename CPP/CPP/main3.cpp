//
//  main1.cpp
//  CPP
//
//  Created by AlexiChen on 2017/12/6.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//

#include <stdio.h>
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

class Sameple16
{
public:
    typedef struct LinkNode
    {
        int _value;
        LinkNode *_next;
        
        LinkNode():_value(0), _next(nullptr)
        {
            
        }
        
        ~LinkNode()
        {
            cout << _value << "  ";
            if (_next)
            {
                delete _next;
                _next = nullptr;
            }
            else
            {
                cout << endl;
            }
        }
        
        void print()
        {
            cout << _value << "  ";
            if (_next)
            {
                _next->print();
            }
            else
            {
                cout << endl;
            }
        }
        
    }*LinkList;
    
private:
    LinkList _list;
    
public:
    const LinkList& list() const
    {
        return _list;
    }
    
public:
    Sameple16():_list(nullptr)
    {
        
    }
    
    ~Sameple16()
    {
        delete _list;
        _list = nullptr;
    }
    
public:
    void addValue(int v)
    {
        if (_list == nullptr)
        {
            _list = new LinkNode;
            _list->_value = v;
        }
        else
        {
            LinkNode *node = new LinkNode;
            node->_value = v;
            
            LinkNode *preNode = _list;
            while (preNode)
            {
                if (preNode->_next == nullptr)
                {
                    break;
                }
                else
                {
                    preNode = preNode->_next;
                }
            }
            
            preNode->_next = node;
        }
    }
    
    LinkNode * findKNode(int k)
    {
        if (k < 0)
        {
            return nullptr;
        }
        
        LinkNode *right = _list;
        int i = 0;
        while (i < k -1 && right != nullptr)
        {
            i++;
            right = right->_next;
        }
        
        if (right == nullptr)
        {
            return nullptr;
        }
        
        LinkNode *left = nullptr;
        while (right != nullptr)
        {
            if (left == nullptr)
            {
                left = _list;
            }
            else
            {
                left = left->_next;
            }
            right = right->_next;
        }
        return left;
    }
    
    
    void reverseLinkList()
    {
        LinkNode *lHeader = _list;
        LinkNode *lHeaderNext = nullptr;
        
        if (lHeader)
        {
            lHeaderNext = lHeader->_next;
        }
        
        while(lHeaderNext != nullptr)
        {
            LinkNode *temp = lHeaderNext->_next;
            
            if (lHeader == _list)
            {
                lHeader->_next = nullptr;
            }
            
            lHeaderNext->_next = lHeader;
            lHeader = lHeaderNext;
            lHeaderNext = temp;
        }
        
        _list = lHeader;
    }
    
    void printList() const
    {
        _list->print();
    }
    
    
    // 合并两个排序的链表
    
public:
    static LinkList mergeLinkList(LinkList list1, LinkList list2)
    {
        
        LinkNode *lh1 = list1;
        LinkNode *lh2 = list2;
        
        if (lh1 == nullptr)
        {
            return lh2;
        }
        
        if (lh2 == nullptr)
        {
            return lh1;
        }
        
        LinkNode *newHead = nullptr;
        LinkNode *curNewNode = nullptr;
        LinkNode *node = nullptr;
        do{
            node = lh1->_value <= lh2->_value ? lh1 : lh2;
            
            if (curNewNode == nullptr)
            {
                newHead = new LinkNode();
                newHead->_value = node->_value;
                curNewNode = newHead;
            }
            else
            {
                LinkNode *newNode = new LinkNode();
                newNode->_value = node->_value;
                curNewNode->_next = newNode;
                curNewNode = newNode;
            }
            
            if (node == lh1)
            {
                lh1 = lh1->_next;
            }
            
            if (node == lh2)
            {
                lh2 = lh2->_next;
            }
            
        }while (lh1 != nullptr && lh2 != nullptr);
        
        
        node = lh1 == nullptr ? lh2 : lh1;
        
        while (node)
        {
            LinkNode *newNode = new LinkNode();
            newNode->_value = node->_value;
            curNewNode->_next = newNode;
            curNewNode = newNode;
            
            node = node->_next;
        }
        
        return newHead;
    }
    
    
};


class Sameple17
{
public:
    
    void printMatrix2(int *matrix, int row, int col)
    {
        if (matrix)
        {
            int hormin = 0;
            int hormax = col - 1;
            
            int vermin = 0;
            int vermax = row - 1;
            
            int rindex = hormin;
            int cindex = vermin;
            
            int printcount = 0;
            
            int direction = 0;
            
            do
            {
                printcount++;
                int printindex = rindex * row + cindex;
                cout << "matrix[" << rindex << "][" << cindex << "] =" << *(matrix + printindex) << endl;
                
                if (direction == 0)
                {
                    if (cindex + 1 <= vermax)
                    {
                        cindex++;
                    }
                    else
                    {
                        rindex++;
                        
                        direction = 1;
                    }
                }
                else if (direction == 1)
                {
                    if (rindex + 1 <= hormax)
                    {
                        rindex++;
                    }
                    else
                    {
                        cindex--;
                        
                        direction = 2;
                    }
                }
                else if (direction == 2)
                {
                    if (cindex - 1 >= 0)
                    {
                        cindex--;
                    }
                    else
                    {
                        rindex--;
                        
                        direction = 3;
                    }
                }
                else if (direction == 3)
                {
                    if (rindex - 1 > hormin)
                    {
                        rindex--;
                    }
                    else
                    {
                        cindex++;
                        vermin++;
                        hormin++;
                        vermax--;
                        hormax--;
                        direction = 0;
                    }
                }
                
                
                
            }while(printcount < (row * col));
            
            
            
            
            
            
        }
    }
    
    void printMatrix(int *matrix, int row, int col)
    {
        if (matrix)
        {
            int hormin = 0;
            int hormax = col - 1;
            
            int vermin = 0;
            int vermax = row - 1;
            
            int rindex = hormin;
            int cindex = vermin;
            
            int printcount = 0;
            bool isHor = true;
            bool isVer = true;
            int reverCount = 0;
            
            
            do{
                printcount++;
                
                int printindex = rindex * row + cindex;
                cout << "matrix[" << rindex << "][" << cindex << "] =" << *(matrix + printindex) << endl;
                
                if (*(matrix + printindex) == 9) {
                    
                }
                
                if (rindex == hormin || rindex == hormax)
                {
                    // 水平移动
                    if (isHor)
                    {
                        if (cindex + 1 > vermax)
                        {
                            // 要转向
                            isHor = false;
                            reverCount++;
                            rindex++;
                        }
                        else
                        {
                            cindex++;
                        }
                    }
                    else
                    {
                        if (rindex - 1 < hormin)
                        {
                            // 要转向
                            isHor = true;
                            reverCount++;
                            cindex--;
                        }
                        else
                        {
                            if (isVer)
                            {
                                if (cindex == 0)
                                {
                                    rindex--;
                                }
                                else
                                {
                                    cindex--;
                                }
                                
                            }
                            else
                            {
                                rindex--;
                            }
                            
                        }
                    }
                }
                else
                {
                    // 纵向移动
                    if (isVer)
                    {
                        if (rindex + 1 > vermax)
                        {
                            // 要转向
                            isVer = false;
                            reverCount++;
                            cindex--;
                        }
                        else
                        {
                            rindex++;
                        }
                    }
                    else
                    {
                        if (cindex - 1 < vermin)
                        {
                            // 要转向
                            isVer = true;
                            reverCount++;
                            rindex++;
                        }
                        else
                        {
                            if (isHor)
                            {
                                
                            }
                            else
                            {
                                cindex--;
                            }
                        }
                    }
                    
                    
                }
                
                if (reverCount == 4)
                {
                    hormin++;
                    hormax--;
                    vermin++;
                    vermax--;
                }
                
                
            }while(printcount < (row * col));
        }
    }
};


class Sameple18
{
private:
    std::stack<int> _stack;
public:
    void push(int v)
    {
        _stack.push(v);
    }
    
    int top()
    {
        return _stack.top();
    }
    
    void pop()
    {
        _stack.pop();
    }
    
    int min()
    {
        std::stack<int> ts;
        
        int min = _stack.top();
        do {
            
            int x = _stack.top();
            ts.push(x);
            if (x < min)
            {
                min = x;
            }
            
            _stack.pop();
            
            
            
        } while (!_stack.empty());
        
        do {
            _stack.push(ts.top());
            ts.pop();
            
        }while (!ts.empty());
        
        
        return min;
    }
};

class Sameple19
{
public:
    bool isPopOrder(int *pushOrder, int *popOrder, int size)
    {
        int pushIndex = 0;
        int popIndex = 0;
        
        stack<int> pushStack;
        
        do {
            
            if ((pushIndex == popIndex) && (pushOrder[pushIndex] == popOrder[popIndex]))
            {
                pushIndex++;
                popIndex++;
                // 相同则不进栈
            }
            else
            {
                if (pushStack.empty())
                {
                    pushStack.push(pushOrder[pushIndex]);
                    
                    if (pushIndex + 1 > size)
                    {
                        break;
                    }
                    else
                    {
                        pushIndex++;
                    }
                }
                else
                {
                    int top = pushStack.top();
                    if (top == popOrder[popIndex])
                    {
                        pushStack.pop();
                        popIndex++;
                    }
                    else
                    {
                        pushStack.push(pushOrder[pushIndex]);
                        if (pushIndex + 1 > size)
                        {
                            break;
                        }
                        else
                        {
                            pushIndex++;
                        }
                    }
                }
            }
            
        } while (pushIndex < size || popIndex < size);
        
        bool isOrder = pushStack.empty();
        
        cout << (isOrder ? "是" : "否" ) << endl;
        return isOrder;
    }
    
};


class Sameple20
{
public:
    typedef struct RandomListNode
    {
        int value;
        RandomListNode *next;
        RandomListNode *random;
        
        
        RandomListNode(int v) : value(v), next(nullptr), random(nullptr) {
            
        }
        
        ~RandomListNode()
        {
            cout << value << "  ";
            
            if (next)
            {
                delete next;
                next = nullptr;
            }
            else
            {
                cout << endl;
            }
        }
        
        void print() const
        {
            cout << "当前结点是：" << value << "  ";
            
            if (random)
            {
                cout << "Random指向：" << random->value << endl;
            }
            else
            {
                cout << "Random未指向" << endl;
            }
            
            
            if (next)
            {
                next->print();
            }
            
        }
        
    }RandomListNode, *RandomLinkList;
    
    
    RandomLinkList randomLoopList()
    {
        RandomLinkList list = new RandomListNode(1);
        RandomListNode *head = list;
        
        const int nodeCount = 5;
        
        int i = 2;
        
        while (i <= nodeCount)
        {
            head->next = new RandomListNode(i++);
            head = head->next;
        }
        
        RandomListNode *last = head;
        int randv = abs(rand() % nodeCount) + 1;
        
        cout << "尾指针指向第" << randv << "个结点" << endl;
        
        head = list;
        while (head)
        {
            if (head->value == randv)
            {
                last->next = head;
                break;
            }
            else
            {
                head = head->next;
            }
        }
        
        return list;
    }
    
    bool isLoopList(const RandomLinkList &list)
    {
        RandomListNode *first = list;
        RandomListNode *second = list;
        
        
        do
        {
            if (first && first->next)
            {
                first = first->next;
            }
            
            if (second && second-> next)
            {
                second = second->next;
                
                if (second && second-> next)
                {
                    second = second->next;
                }
            }
            
            if (first == second)
            {
                return true;
            }
            
            
        }while(first && second && first != second);
        return false;
    }
    
    bool isLoopList2(const RandomLinkList &list)
    {
        std::list<RandomListNode *> lmap;
        RandomListNode *head = list;
        while (head)
        {
            if (std::find(lmap.begin(), lmap.end(), head) != lmap.end())
            {
                cout << "尾指针错向" << head->value << endl;
                return true;
            }
            else
            {
                lmap.push_back(head);
                head = head->next;
            }
            
        }
        
        return false;
    }
    
    bool isLoopList3(const RandomLinkList &list)
    {
        std::map<RandomListNode *, int> map;
        RandomListNode *head = list;
        while (head)
        {
            if (map.find(head) != map.end())
            {
                cout << "尾指针错向" << head->value << endl;
                return true;
            }
            else
            {
                map.insert(std::make_pair(head, head->value));
                head = head->next;
            }
            
        }
        
        return false;
    }
    
    RandomLinkList randomNewList()
    {
        RandomLinkList list = new RandomListNode(1);
        
        RandomListNode *head = list;
        
        const int nodeCount = 20;
        
        int i = 2;
        
        while (i <= nodeCount)
        {
            head->next = new RandomListNode(i++);
            head = head->next;
        }
        
        
        // random
        head = list;
        
        i = 0;
        while (i < nodeCount && head != nullptr)
        {
            int randv = abs(rand() % nodeCount);
            
            if (randv == 0)
            {
                head = head->next;
            }
            else
            {
                RandomListNode *randhead = list;
                while (randhead)
                {
                    if (randhead->value == randv)
                    {
                        head->random = randhead;
                        head = head->next;
                        break;
                    }
                    else
                    {
                        randhead = randhead->next;
                    }
                }
            }
            i++;
        }
        
        
        
        return list;
    }
    
    RandomLinkList deepCopy(const RandomLinkList alist)
    {
        
        RandomLinkList list = nullptr;
        
        RandomListNode *ahead = alist;
        RandomListNode *head = list;
        
        do
        {
            if (ahead)
            {
                if (head == nullptr)
                {
                    head = new RandomListNode(ahead->value);
                    list = head;
                }
                else
                {
                    head->next = new RandomListNode(ahead->value);
                    head = head->next;
                }
                
                ahead = ahead->next;
            }
            
        }while(ahead != nullptr);
        
        
        ahead = alist;
        head = list;
        
        do
        {
            if (ahead)
            {
                if (ahead->random)
                {
                    int randV = ahead->random->value;
                    
                    RandomListNode *temp = list;
                    while (temp)
                    {
                        if (temp->value == randV)
                        {
                            head->random = temp;
                            
                            break;
                        }
                        
                        temp = temp->next;
                    }
                }
                
                head = head->next;
                ahead = ahead->next;
            }
        }while(ahead != nullptr);
        
        return list;
    }
    
    
};


int main3()
{
    
    Sameple20 s20;
    Sameple20::RandomLinkList list = s20.randomNewList();
    list->print();
    cout << "==============" << endl;
    Sameple20::RandomLinkList nl = s20.deepCopy(list);
    
    cout << "==============" << endl;
    nl->print();
    
    cout << "==============" << endl;
    Sameple20::RandomLinkList loopList = s20.randomLoopList();
    s20.isLoopList(loopList);
    s20.isLoopList2(loopList);
    s20.isLoopList3(loopList);
    
    return 0;
    
    Sameple19 s19;
    const int s19Count = 6;
    int push[s19Count] = {1,2,3, 4, 5, 6};
    int pop[s19Count] = {3,1, 4,5,2,6,};
    s19.isPopOrder(push, pop, s19Count);
    return 0;
    
    
    Sameple18 s18;
    s18.push(4);
    s18.push(2);
    s18.push(3);
    
    int min = s18.min();
    cout << min << endl;
    return 0;
    Sameple17 s17;
    
    const int row = 10;
    const int col = 10;
    
    int *martrix_array = new int[row*row];
    int (*martrix)[col] = (int (*)[col])martrix_array;
    
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            martrix[i][j] = i * row + j + 1;
            cout << martrix[i][j] << "  ";
        }
        
        cout << endl;
    }
    
    
    s17.printMatrix2(martrix_array, row, col);
    return 0;
    Sameple16 s16;
    int k = 1;
    while(k <= 20)
    {
        s16.addValue(k++);
    }
    
    Sameple16::LinkNode *node = s16.findKNode(10);
    if (node)
    {
        
        cout << node->_value << endl;
    }
    s16.printList();
    s16.reverseLinkList();
    s16.printList();
    
    Sameple16 s16_1;
    k = 1;
    while(k <= 5)
    {
        if (k%2 == 1)
        {
            s16_1.addValue(k++);
        }
        else
        {
            k++;
        }
        
    }
    s16_1.printList();
    
    Sameple16 s16_2;
    k = 1;
    while(k <= 5)
    {
        if (k%2 == 0)
        {
            s16_2.addValue(k++);
        }
        else
        {
            k++;
        }
        
    }
    s16_2.printList();
    
    Sameple16::LinkList newlist = Sameple16::mergeLinkList(s16_1.list(), s16_2.list());
    cout << "====== : ";
    newlist->print();
    delete newlist;
    return 0;
}
