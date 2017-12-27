//
//  Header.h
//  SimpleTreeSpace
//
//  Created by AlexiChen on 2017/12/22.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//

#ifndef BSTree_H
#define BSTree_H

#include "BaseTree.h"

//二叉查找树
//二叉查找树（英语：Binary Search Tree），也称二叉搜索树、有序二叉树（英语：ordered binary tree），排序二叉树（英语：sorted binary tree），是指一棵空树或者具有下列性质的二叉树：
//
//若任意节点的左子树不空，则左子树上所有节点的值均小于它的根节点的值；
//若任意节点的右子树不空，则右子树上所有节点的值均大于它的根节点的值；
//任意节点的左、右子树也分别为二叉查找树；
//没有键值相等的节点。
template <class T>
struct BSTree : public BTNode<T>
{
    
public:
    BSTree<T>(T value):BTNode<T>(value)
    {
        
    }
    
    static BSTree<T> *buildBSTree(T *treelist, int listSize, std::function<bool (const T rootV,const T insertValue)> compareFunc = [](const T rootV,const T insertValue)->bool{
        return rootV > insertValue;
    })
    {
        if (treelist == nullptr || listSize <= 0)
        {
            return nullptr;
        }
        T rtv = *treelist;
        BSTree<T> *root = new BSTree(rtv);
        int index = 1;
        std::function<bool (const T rootV,const T insertValue)>  comFunc = compareFunc;
        
        do {
            
            T value = *(treelist + index);
            root->insertNode(root, value, comFunc);
            index++;
        } while (index < listSize);
        
        return root;
    }
    
    void deleteNode(const T value)
    {
        
    }
    
    void insertNode(BTNode<T> *&&root,const T value, std::function<bool (const T rootV,const T insertValue)> compareFunc = [](const T rootV,const T insertValue)->bool{
        return insertValue < rootV;
    })
    {
        if (root == nullptr)
        {
            root = new BSTree(value);
        }
        else
        {
            T rv = root->mValue;
            bool isLittle = compareFunc(rv, value);
            if (isLittle)
            {
                insertNode(std::move(root->mLeft), value, compareFunc);
            }
            else
            {
                insertNode(std::move(root->mRight), value, compareFunc);
            }
        }
    }
    
    const BSTree<T> *&& searchMin(std::function<void (T)> func = [](T n){ cout << n << "  ";}) const
    {
        func(this->mValue);
        if (this->mLeft == nullptr)
        {
            cout << endl;
            return std::move(this);
        }
        else
        {
            BSTree<T> *leftTree = (BSTree<T> *)this->mLeft;
            return leftTree->searchMin(func);
        }
    }
    
    const BSTree<T> *&& searchMax(std::function<void (T)> func = [](T n){ cout << n << "  ";}) const
    {
        func(this->mValue);
        if (this->mRight == nullptr)
        {
            cout << endl;
            return std::move(this);
        }
        else
        {
            BSTree<T> *rightTree = (BSTree<T> *)this->mRight;
            return rightTree->searchMax(func);
        }
    }
    
    const T search(const T rootV, std::function<void (T)> func = [](T n){ cout << n << "  ";}) const
    {
        func(this->mValue);
        if (this->mValue == rootV)
        {
            cout << endl;
            return this->mValue;
        }
        else if (rootV < this->mValue)
        {
            if (this->mLeft)
            {
                BSTree<T> *leftTree = (BSTree<T> *)this->mLeft;
                return leftTree->search(rootV);
            }
            else
            {
                cout << "not found" << endl;
                return -1;
            }
        }
        else if (rootV > this->mValue)
        {
            if (this->mRight)
            {
                BSTree<T> *rightTree = (BSTree<T> *)this->mRight;
                return rightTree->search(rootV);
            }
            else
            {
                cout << "not found" << endl;
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
};

#endif /* BSTree_H */
