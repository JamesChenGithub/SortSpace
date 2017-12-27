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
template <class T>
struct BSTree : BTNode<T>
{
    
public:
    BSTree<T>(T value):BTNode<T>()
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
        
        BSTree<T> *root = new BSTree(*treelist);
        int index = 1;
        std::function<bool (const T rootV,const T insertValue)>  comFunc = compareFunc;
        
        do {
            T value = *(treelist + index);
            root->insertNode(value, comFunc);
            index++;
        } while (index < listSize);
        
        return root;
    }
    
    void deleteNode(const T value)
    {
        
    }
    
    static void insertNode(const T value, std::function<bool (const T rootV,const T insertValue)> compareFunc)
    {
        if ()
        
    }
};

#endif /* BSTree_H */
