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
    
public:
    static std::function<void (T)> valuePrintFunc;
    static bool mPrintValueInDelete;
    
public:
    BTNode<T>():mLeft(nullptr), mRight(nullptr) {
        
    }
    BTNode<T>(T value):BTNode<T>()
    {
        mValue = value;
    }
    
    ~BTNode<T>()
    {
        if (mPrintValueInDelete)
        {
            printValue();
        }
        
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
        
        cout << "当前树" << (BTNode::isAVLTree(this) ? "是" : "不是") << "平衡二叉树, " << (this->isBSTree() ? "是" : "不是") <<"二叉查找树, " << (this->isAVLBSTree() ? "是" : "不是") << "平衡二叉查找树" << endl;
        int avlheight = 0;
        cout << "当前树" << (BTNode::isAVLTree(this, avlheight) ? "是" : "不是") << "平衡二叉树" << endl;
        
        
        
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
    
    
    static BTNode<T> *buildTreeBy(std::vector<T> tVec)
    {
        BTNode<T> *root = nullptr;
        T value;
        std::queue<BTNode<T> *> queue;
        int nodeCount = 0;
        const int vecCount = tVec.size();
        do
        {
//            nodeCount++;
//            if ()
            
            
        }while(nodeCount < vecCount);
        
        return root;
    }
    
public:
//    定义
//
//    父节点的左子树和右子树的高度之差不能大于1，也就是说不能高过1层，否则该树就失衡了，此时就要旋转节点，在

    static  bool isAVLTree(const BTNode<T> *root)
    {
        
        if (!root)
        {
            return true;
        }
        
        if (!isAVLTree(root->mLeft))
        {
            return false;
        }
        
        if (!isAVLTree(root->mRight))
        {
            return false;
        }
        
        
        int leftheight = root->mLeft ? root->mLeft->treeHeight() : 0;
        int rightheight = root->mRight ? root->mRight->treeHeight() : 0;
        
        if (abs(leftheight - rightheight) >= 2)
        {
            return false;
        }
        return true;
    }
    
    static bool isAVLTree(const BTNode<T> *root, int& height)
    {
        if (!root) return true;
        
        int left = 0;
        
        int right = 0;
        
        if (!isAVLTree(root->mLeft, left)) return false;
        
        if (!isAVLTree(root->mRight, right)) return false;
        
        if (abs(left - right) >= 2)
        {
            return false;
        }
        
        height = left > right ? left + 1 : right + 1;
        return true;
    }
    
    bool isBSTree(std::function<bool (T,T)> func = [](T v1, T v2)->bool{
        return v1 < v2;
    }) const
    {
        
        bool isLeft = true;
        if (mLeft)
        {
            isLeft = func(mLeft->mValue, mValue);
        }
        
        if (!isLeft)
        {
            return false;
        }
        
        bool isRight = true;
        if (mRight)
        {
            isRight = func(mValue, mRight->mValue);
        }
        
        if (!isRight)
        {
            return false;
        }
        
        if (mLeft)
        {
            if (mRight)
            {
                return mLeft->isBSTree(func) &&  mRight->isBSTree(func);
            }
            else
            {
                return mLeft->isBSTree(func);
            }
        }
        else
        {
            if (mRight)
            {
                return mRight->isBSTree(func);
            }
            else
            {
                return true;
            }

        }

    }
    
    bool isAVLBSTree() const
    {
        // 是否是
        return BTNode::isAVLTree(this) && this->isBSTree();
    }
    
    
    
    //二叉查找树
    //二叉查找树（英语：Binary Search Tree），也称二叉搜索树、有序二叉树（英语：ordered binary tree），排序二叉树（英语：sorted binary tree），是指一棵空树或者具有下列性质的二叉树：
    //
    //若任意节点的左子树不空，则左子树上所有节点的值均小于它的根节点的值；
    //若任意节点的右子树不空，则右子树上所有节点的值均大于它的根节点的值；
    //任意节点的左、右子树也分别为二叉查找树；
    //没有键值相等的节点。
    
public:
    
    
    static BTNode<T> *buildBTNode(T *treelist, int listSize, std::function<bool (const T rootV,const T insertValue)> compareFunc = [](const T rootV,const T insertValue)->bool{
        return rootV > insertValue;
    })
    {
        if (treelist == nullptr || listSize <= 0)
        {
            return nullptr;
        }
        T rtv = *treelist;
        BTNode<T> *root = new BTNode(rtv);
        int index = 1;
        std::function<bool (const T rootV,const T insertValue)>  comFunc = compareFunc;
        
        do {
            
            T value = *(treelist + index);
            BTNode::insertNode(root, value, comFunc);
            index++;
        } while (index < listSize);
        
        return root;
    }
    
    static void deleteNode(BTNode<T> *&root, const T value)
    {
        cout << "将删除 : " << value << "结点" << endl;
        BTNode<T> *valueRoot = nullptr;
        BTNode<T> *valueNode = BTNode::search(root, value, valueRoot);
        
        if (valueNode == nullptr)
        {
            cout << "没有该结点，不用删除" << endl;
            return;
        }
        
        
        if (valueNode->mLeft == nullptr && valueNode->mRight == nullptr)
        {
            if (valueRoot == nullptr)
            {
                delete valueNode;
                valueNode = nullptr;
                // 可能删除概结点
                
                if (valueNode == root)
                {
                    root = nullptr;
                }
            }
            else
            {
                if (valueRoot->mLeft == valueNode)
                {
                    valueRoot->mLeft = nullptr;
                }
                else if (valueRoot->mRight == valueNode)
                {
                    valueRoot->mRight= nullptr;
                }
                
                delete valueNode;
                valueNode = nullptr;
            }
        }
        else if (valueNode->mLeft && valueNode->mRight == nullptr)
        {
            if (valueNode == root)
            {
                root = (BTNode<T> *)valueNode->mLeft;
                
                valueNode->mLeft = nullptr;
                
                delete valueNode;
                valueNode = nullptr;
            }
            else
            {
                if (valueRoot)
                {
                    valueRoot->mLeft = valueNode->mLeft;
                    
                    valueNode->mLeft = nullptr;
                    
                    delete valueNode;
                    valueNode = nullptr;
                }
                else
                {
                    // 代码有误
                }
            }
        }
        else if (valueNode->mLeft == nullptr && valueNode->mRight)
        {
            if (valueNode == root)
            {
                root = (BTNode<T> *)valueNode->mRight;
                
                valueNode->mRight = nullptr;
                
                delete valueNode;
                valueNode = nullptr;
            }
            else
            {
                if (valueRoot)
                {
                    valueRoot->mRight = valueNode->mRight;
                    
                    valueNode->mRight = nullptr;
                    
                    delete valueNode;
                    valueNode = nullptr;
                }
                else
                {
                    // 代码有误
                }
            }
        }
        else
        {
            BTNode<T> *successor = valueNode->searchSuccessor();
            T temp = successor->mValue;
            //删除后继结点
            BTNode::deleteNode(root, successor->mValue);
            valueNode->mValue = temp;
        }
        
        
        
        
    }
    
    BTNode<T> * searchSuccessor()
    {
        if (this->mRight)
        {
            return (BTNode<T> *)BTNode::searchMin((BTNode<T> *)this->mRight);
        }
        else
        {
            return (BTNode<T> *)(this->mLeft);
        }
    }
    
    static void insertNode(BTNode<T> *&root,const T value, std::function<bool (const T rootV,const T insertValue)> compareFunc = [](const T rootV,const T insertValue)->bool{
        return insertValue < rootV;
    })
    {
        if (root == nullptr)
        {
            root = new BTNode(value);
        }
        else
        {
            T rv = root->mValue;
            bool isLittle = compareFunc(rv, value);
            if (isLittle)
            {
                BTNode::insertNode(root->mLeft, value, compareFunc);
            }
            else
            {
                BTNode::insertNode(root->mRight, value, compareFunc);
            }
        }
    }
    
    static const BTNode<T> * searchMin(BTNode<T> *root, std::function<void (T)> func = [](T n){ cout << n << "  ";})
    {
        if (root)
        {
            func(root->mValue);
            if (root->mLeft == nullptr)
            {
                cout << endl;
                return root;
            }
            else
            {
                BTNode<T> *leftTree = (BTNode<T> *)root->mLeft;
                return BTNode::searchMin(leftTree, func);
            }
        }
        else
        {
            return nullptr;
        }
    }
    
    static const BTNode<T> * searchMax(BTNode<T> *root, std::function<void (T)> func = [](T n){ cout << n << "  ";})
    {
        if (root)
        {
            std::function<void (T)> function = func;
            func(root->mValue);
            if (root->mRight == nullptr)
            {
                cout << endl;
                return root;
            }
            else
            {
                BTNode<T> *rightTree = (BTNode<T> *)root->mRight;
                return BTNode::searchMax(rightTree, function);
            }
        }
        else
        {
            return nullptr;
        }
    }
    
    
    static BTNode<T> * search(BTNode<T> *root, const T rootV, std::function<void (T)> func = [](T n){ cout << n << "  ";})
    {
        if (root)
        {
            func(root->mValue);
            if (root->mValue == rootV)
            {
                cout << endl;
                return std::move(root);
            }
            else if (rootV < root->mValue)
            {
                if (root->mLeft)
                {
                    BTNode<T> *leftTree = (BTNode<T> *)root->mLeft;
                    return BTNode::search(leftTree, rootV, func);
                }
                else
                {
                    cout << "not found" << endl;
                    return nullptr;
                }
            }
            else if (rootV > root->mValue)
            {
                if (root->mRight)
                {
                    BTNode<T> *rightTree = (BTNode<T> *)root->mRight;
                    return BTNode::search(rightTree, rootV, func);
                }
                else
                {
                    cout << "not found" << endl;
                    return nullptr;
                }
            }
            else
            {
                return nullptr;
            }
        }
        else
        {
            return nullptr;
        }
    }
    
    static BTNode<T> * search(BTNode<T> *root, const T rootV,  BTNode<T> *&searvalueParent,std::function<void (T)> func = [](T n){ cout << n << "  ";})
    {
        if (root)
        {
            func(root->mValue);
            if (root->mValue == rootV)
            {
                cout << endl;
                return root;
            }
            else if (rootV < root->mValue)
            {
                if (root->mLeft)
                {
                    BTNode<T> *leftTree = (BTNode<T> *)root->mLeft;
                    searvalueParent = root;
                    return BTNode::search(leftTree, rootV, searvalueParent, func);
                }
                else
                {
                    cout << "not found" << endl;
                    searvalueParent = nullptr;
                    return nullptr;
                }
            }
            else if (rootV > root->mValue)
            {
                if (root->mRight)
                {
                    BTNode<T> *rightTree = (BTNode<T> *)root->mRight;
                    searvalueParent = root;
                    return BTNode::search(rightTree, rootV, searvalueParent);
                }
                else
                {
                    cout << "not found" << endl;
                    searvalueParent = nullptr;
                    return nullptr;
                }
            }
            else
            {
                searvalueParent = nullptr;
                return nullptr;
            }
        }
        else
        {
            searvalueParent = nullptr;
            return nullptr;
        }
    }
    
    
    //=================================================
    // 创建平衡二叉查找树

//    static BTNode<T> *buildAVLBTNode(T *treelist, int listSize, std::function<bool (const T rootV,const T insertValue)> compareFunc = [](const T rootV,const T insertValue)->bool{
//        return rootV > insertValue;
//    })
//    {
//        if (treelist == nullptr || listSize <= 0)
//        {
//            return nullptr;
//        }
//        T rtv = *treelist;
//        BTNode<T> *root = new BTNode(rtv);
//        int index = 1;
//        std::function<bool (const T rootV,const T insertValue)>  comFunc = compareFunc;
//
//        do {
//
//            T value = *(treelist + index);
//            BTNode::insertNode(root, value, comFunc);
//            index++;
//        } while (index < listSize);
//
//        return root;
//    }
    
};

template <class T>
std::function<void (T)> BTNode<T>::valuePrintFunc = [] (T v) {
    cout << v << " ";
};

template <class T>
bool BTNode<T>::mPrintValueInDelete = true;



#endif /* BaseTree_h */
