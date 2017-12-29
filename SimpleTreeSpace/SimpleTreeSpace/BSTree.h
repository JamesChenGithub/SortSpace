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
            BSTree::insertNode(root, value, comFunc);
            index++;
        } while (index < listSize);
        
        return root;
    }
    
    static void deleteNode(BSTree<T> *&root, const T value)
    {
        BSTree<T> *valueRoot = nullptr;
        BSTree<T> *valueNode = BSTree::search(root, value, valueRoot);
        
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
                    root = (BSTree<T> *)valueNode->mLeft;
                    
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
                    root = (BSTree<T> *)valueNode->mRight;
                    
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
                BSTree<T> *successor = valueNode->searchSuccessor();
                T temp = successor->mValue;
                //删除后继结点
                BSTree::deleteNode(root, successor->mValue);
                valueNode->mValue = temp;
            }
        
        
        
        
    }
    
    BSTree<T> * searchSuccessor()
    {
        if (this->mRight)
        {
            return (BSTree<T> *)BSTree::searchMin((BSTree<T> *)this->mRight);
        }
        else
        {
            return (BSTree<T> *)(this->mLeft);
        }
    }
    
    static void insertNode(BTNode<T> *&&root,const T value, std::function<bool (const T rootV,const T insertValue)> compareFunc = [](const T rootV,const T insertValue)->bool{
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
                BSTree::insertNode(std::move(root->mLeft), value, compareFunc);
            }
            else
            {
                BSTree::insertNode(std::move(root->mRight), value, compareFunc);
            }
        }
    }
    
    static const BSTree<T> * searchMin(BSTree<T> *root, std::function<void (T)> func = [](T n){ cout << n << "  ";})
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
                BSTree<T> *leftTree = (BSTree<T> *)root->mLeft;
                return BSTree::searchMin(leftTree, func);
            }
        }
        else
        {
            return nullptr;
        }
    }
    
    static const BSTree<T> * searchMax(BSTree<T> *root, std::function<void (T)> func = [](T n){ cout << n << "  ";})
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
                BSTree<T> *rightTree = (BSTree<T> *)root->mRight;
                return BSTree::searchMax(rightTree, function);
            }
        }
        else
        {
            return nullptr;
        }
    }
    
    
    static BSTree<T> * search(BSTree<T> *root, const T rootV, std::function<void (T)> func = [](T n){ cout << n << "  ";})
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
                    BSTree<T> *leftTree = (BSTree<T> *)root->mLeft;
                    return BSTree::search(leftTree, rootV, func);
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
                    BSTree<T> *rightTree = (BSTree<T> *)root->mRight;
                    return BSTree::search(rightTree, rootV, func);
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
    
    static BSTree<T> * search(BSTree<T> *root, const T rootV,  BSTree<T> *&searvalueParent,std::function<void (T)> func = [](T n){ cout << n << "  ";})
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
                    BSTree<T> *leftTree = (BSTree<T> *)root->mLeft;
                    searvalueParent = root;
                    return BSTree::search(leftTree, rootV, searvalueParent, func);
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
                    BSTree<T> *rightTree = (BSTree<T> *)root->mRight;
                    searvalueParent = root;
                    return BSTree::search(rightTree, rootV, searvalueParent);
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
    
    virtual bool isBSTree(std::function<bool(T,T)> func = []{}) const
    {
        
    }
    
    virtual bool isAVLTree() const
    {
        int leftheight = mLeft ? mLeft->treeHeight() : 0;
        int rightheight = mRight ? mRight->treeHeight() : 0;
        
        if (abs(leftheight - rightheight) >= 2)
        {
            return false;
        }
        return true;
    }
};

#endif /* BSTree_H */
