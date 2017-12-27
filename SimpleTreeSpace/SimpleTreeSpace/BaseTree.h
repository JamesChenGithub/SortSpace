//
//  BaseTree.h
//  SimpleTreeSpace
//
//  Created by AlexiChen on 2017/12/22.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//

#ifndef BaseTree_h
#define BaseTree_h

#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <tuple>

using namespace std;



template <class T>
struct BTNode
{
public:
    T          mValue;
    BTNode<T>  *mLeft;
    BTNode<T>  *mRight;
    
private:
    static std::function<void (T)> valuePrintFunc;
    
public:
    BTNode<T>():mLeft(nullptr), mRight(nullptr) {
        
    }
    BTNode<T>(T value):BTNode<T>()
    {
        mValue = value;
    }
    
    ~BTNode<T>()
    {
        printValue();
        if (mLeft)
        {
            delete mLeft;
            mLeft = nullptr;
        }
        
        if (mRight)
        {
            delete mRight;
            mRight = nullptr;
        }
    }
    
    static void setPrintFunc(std::function<void (T)>& printFunc)
    {
        valuePrintFunc = printFunc;
    }
    
public:
    void printValue() const
    {
        if (valuePrintFunc)
        {
            valuePrintFunc(mValue);
        }
    }
    
    const T value() const
    {
        return mValue;
    }
    
    
    T& value()
    {
        return mValue;
    }
    
public:
    int treeHeight() const
    {
        if (mLeft == nullptr && mRight == nullptr)
        {
            return 1;
        }
        else
        {
            int lh = 0;
            int rh = 0;
            
            if (mLeft)
            {
                lh = mLeft->treeHeight();
            }
            
            if (mRight)
            {
                rh = mRight->treeHeight();
            }
            
            int height = lh > rh ? lh : rh;
            return height + 1;
        }
    }
    
//    int treeWhidth() const
//    {
//
//        int lmin;
//
//        if (mLeft == nullptr)
//        {
//            return 0;
//        }
//        else
//        {
//
//        }
//
//    }
//
//    int treeWhidth(int &lmin, int &rmax) const
//    {
//        if (mLeft)
//        {
//
//        }
//        else
//        {
//
//        }
//    }
    
    void mirror() const
    {
        BTNode<T> *node = mLeft;
        mLeft = mRight;
        mRight = node;
        
        if (mLeft)
        {
            mLeft->mirror();
        }
        
        if (mRight)
        {
            mRight->mirror();
        }
    }
    
    
    void printTreeByLevel() const
    {
        typedef std::pair<int, const BTNode<T> *> BTNodePair;
        std::queue<BTNodePair> queue;
        queue.push({0, this});
        
        do {
            BTNodePair pair = queue.front();
            
            queue.pop();
            
            int lev = pair.first;
            const BTNode<T> *node = pair.second;
            
            node->printValue();
            
            if (node->mLeft)
            {
                queue.push({lev + 1, node->mLeft});
            }
            
            if (node->mRight)
            {
                queue.push({lev+1, node->mRight});
            }
            
            BTNodePair nextPair = queue.front();
            if (nextPair.first != lev)
            {
                cout << endl;
            }
            
        }while(!queue.empty());
    }
    
    
    
    
    void printTreeLikeTree(std::function<void (T)> printFunc = [](T v){
        cout << v;
    }) const
    {
        typedef std::tuple<int, int, const BTNode<T> *> BTNodeTuple;
        std::vector<BTNodeTuple> rootQueue;
        std::vector<BTNodeTuple> childQueue;
    
        int height = treeHeight();
        
        rootQueue.push_back(std::make_tuple(height, 2 * height - 1, this));
        std::function<void (T)> printCall= printFunc;
        const char place = ' ';
        do
        {
            // 输出 rootQueue
            int start = 0;
            std::for_each(rootQueue.begin(), rootQueue.end(), [&](BTNodeTuple rootTuple) {
                int rw = std::get<1>(rootTuple);
                const BTNode<T> *node = std::get<2>(rootTuple);
                int count = 0;
                
                if (start == 0)
                {
                    start = rw;
                    count = start;
                    
                    while(count > 0)
                    {
                        cout << place;
                        count--;
                    }
                }
                else
                {
                    count = rw - start;
                    start = rw;
                    
                    while(count > 1)
                    {
                        cout << place;
                        count--;
                    }
                }
                
                
                printCall(node->mValue);
            });
            
            cout << endl;
            
            // 输出支干
            start = 0;
            std::for_each(rootQueue.begin(), rootQueue.end(), [&](BTNodeTuple rootTuple) {
                int rw =  std::get<1>(rootTuple);
                const BTNode<T> *node = std::get<2>(rootTuple);
                int count = 0;
                
                if (start == 0)
                {
                    start = rw;
                    count = start;
                }
                else
                {
                    count = rw - start;
                    start = rw;
                }
                
                if (node->mLeft)
                {
                    while(count > 1)
                    {
                        cout << place;
                        count--;
                    }
                    
                    cout << "/";
                    
                    if (node->mRight)
                    {
                        cout << place <<"\\";
                    }
                }
                else
                {
                    count += 2;
                    while(count > 1)
                    {
                        cout << place;
                        count--;
                    }
                    
                    if (node->mRight)
                    {
                        cout << "\\";
                    }
                }
            
            });
            cout << endl;
            // 读入chileQueue
            std::for_each(rootQueue.begin(), rootQueue.end(), [&](BTNodeTuple rootTuple) {
                int rh = std::get<0>(rootTuple);
                int rw = std::get<1>(rootTuple);
                const BTNode<T> *node = std::get<2>(rootTuple);
                
                if(node->mLeft)
                {
                    childQueue.push_back({rh - 1, rw - 2, node->mLeft});
                }
                
                if(node->mRight)
                {
                    childQueue.push_back({rh - 1, rw + 2, node->mRight});
                }
            });
            
            
            // 清空root
            
            rootQueue.clear();
            
            std::for_each(childQueue.begin(), childQueue.end(), [&](BTNodeTuple rootTuple) {
                rootQueue.push_back(rootTuple);
            });
            
            childQueue.clear();
        }while(!rootQueue.empty());
        
    }
    
    
//    int printLikeTree() const
//    {
//        
//    }
    
    int preOrderTraversal() const
    {
        printValue();
        if (mLeft)
        {
            mLeft->printValue();
        }
        
        if (mRight)
        {
            mRight->printValue();
        }
    }
    
    int inOrderTraversal() const
    {
        
        if (mLeft)
        {
            mLeft->printValue();
        }
        printValue();
        if (mRight)
        {
            mRight->printValue();
        }
    }
    
    int postOrderTraversal() const
    {
        
        if (mLeft)
        {
            mLeft->printValue();
        }
        
        if (mRight)
        {
            mRight->printValue();
        }
        
        printValue();
    }
    
    
public:
    static BTNode<T> *randomTree(std::function<bool (T &value)> getTFunc, std::function<string (T)> toStrFunc)
    {
        BTNode<T> *root = nullptr;
        T value;
        bool succ = false;
        std::queue<BTNode<T> *> queue;
        
        do
        {
            if (root == nullptr)
            {
                cout << "输入根结点:";
                succ = getTFunc(value);
                if (succ)
                {
                    root = new BTNode<T>(value);
                    queue.push(root);
                }
                else
                {
                    cout << "未获取到正确的结点值" << endl;
                    break;
                }
            }
            else
            {
                BTNode<T> *node = queue.front();
                queue.pop();
                
                cout << "输入"<< toStrFunc(node->mValue) <<"结点在左结点:";
                
                succ = getTFunc(value);
                if (succ)
                {
                    BTNode<T> *leftNode = new BTNode<T>(value);
                    node->mLeft = leftNode;
                    queue.push(leftNode);
                }
                
                cout << "输入"<< toStrFunc(node->mValue) <<"结点在右结点:";
                succ = getTFunc(value);
                if (succ)
                {
                    BTNode<T> *rightNode = new BTNode<T>(value);
                    node->mRight = rightNode;
                    queue.push(rightNode);
                }
            }
            
        }while(!queue.empty());
        
        
        return root;
    }
    
};

template <class T>
std::function<void (T)> BTNode<T>::valuePrintFunc = [] (T v) {
    cout << v << " ";
};




#endif /* BaseTree_h */
