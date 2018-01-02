//
//  main.m
//  SimpleTreeSpace
//
//  Created by AlexiChen on 2017/12/21.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//

#include <iostream>
#include <functional>
#include <string>
#include <vector>

#include "BaseTree.h"

using namespace std;

void printIntInTree(int value)
{
    cout << value << "   ";
}

int main()
{
    
    //    std::function<void (int)> func = [](int value){
    //       cout << value << " ";
    //    };
    //    BTNode<int>::setPrintFunc(func);
    //    
    //    int i = 0;
    //    while (i <= 10)
    //    {
    //        BTNode<int> *root = BTNode<int>::randomTree([](int &value)->bool {
    //            scanf("%d", &value);
    //            return value != 0;
    //        }, [](int value)->string{
    //            return std::to_string(value);
    //        });
    //        
    //        if (root)
    //        {
    //            
    //            root->printTreeByLevel();
    //            
    //            root->printTreeLikeTree([](int v){
    //                cout << v;
    //            });
    //        }
    //        i++;
    //        
    //        cout << endl << "删除树";
    //        delete root;
    //        root = nullptr;
    //        
    //        cout << endl;
    //    }
    
    int bstArray[8] = {8,6,10,23,12,59,13,46};
    
    BTNode<int> *bstRoot = BTNode<int>::buildBTNode(bstArray, 8);
    
    bstRoot->printTreeLikeTree([](int value){
        cout << value;
    });
    
    
    bstRoot->insertNode(bstRoot, 1);
    bstRoot->printTreeLikeTree();
    
    bstRoot->insertNode(bstRoot, 7);
    bstRoot->printTreeLikeTree();
    
    BTNode<int>::searchMin(bstRoot);
    BTNode<int>::searchMax(bstRoot);
    
    BTNode<int>::search(bstRoot, 23);
    
    BTNode<int>::search(bstRoot, 3);
    
    BTNode<int>::mPrintValueInDelete = false;
    
    cout << "===========" << endl;
    BTNode<int>::deleteNode(bstRoot, 1);
    bstRoot->printTreeLikeTree();
    
    cout << "===========" << endl;
    BTNode<int>::deleteNode(bstRoot, 13);
    bstRoot->printTreeLikeTree();
    
    cout << "===========" << endl;
    BTNode<int>::deleteNode(bstRoot, 7);
    bstRoot->printTreeLikeTree();
    
    cout << "===========" << endl;
    BTNode<int>::deleteNode(bstRoot, 8);
    bstRoot->printTreeLikeTree();
    
    cout << "===========" << endl;
    BTNode<int>::deleteNode(bstRoot, 23);
    bstRoot->printTreeLikeTree();
    
    cout << "===========" << endl;
    BTNode<int>::insertNode(bstRoot, 8);
    bstRoot->printTreeLikeTree();
    
    cout << "===========" << endl;
    BTNode<int>::insertNode(bstRoot, 7);
    bstRoot->printTreeLikeTree();
    
    
    cout << "===========" << endl;
    BTNode<int>::insertNode(bstRoot, 9);
    bstRoot->printTreeLikeTree();
    
    
    cout << "===========" << endl;
    BTNode<int>::deleteNode(bstRoot, 8);
    bstRoot->printTreeLikeTree();
    
    cout << "===========" << endl;
    BTNode<int>::deleteNode(bstRoot, 10);
    bstRoot->printTreeLikeTree();
    
    delete bstRoot;
    bstRoot = nullptr;
    
    //===============================
    cout << endl << "===========" << endl;
    BTNode<int>::mPrintValueInDelete = true;
    std::vector<int> vec = {1,4,7,2,5,8,3,6,9};
    BTNode<int> *root = BTNode<int>::buildTreeBy(vec);
    if (root)
    {
        delete root;
        root = nullptr;
    }
    
    cout << endl << "===========" << endl;
    int array[9] = {1,4,7,2,5,8,3,6,9};
    root = BTNode<int>::buildTreeBy(array, 9);
    if (root)
    {
        delete root;
        root = nullptr;
    }

    
    cout << endl << "===========" << endl;
    int array2[15] = {1,4,7,2,5,0,8,3, 0, 10,6, 0,9,11,0};
    root = BTNode<int>::buildTreeBy(array2, 15, [](int v)->bool{
        return v > 0;
    });
    if (root)
    {
        delete root;
        root = nullptr;
    }
    
    
    cout << endl << "===========" << endl;
    int arrayLL[4] = {1,2,0,3};
    root = BTNode<int>::buildTreeBy(arrayLL, 4,[](int v)->bool{
        return v > 0;
    });
    
    
    BTNode<int>::singleRotateLL(root);
    root->printTreeLikeTree();
    
    if (root)
    {
        delete root;
        root = nullptr;
    }
    
    cout << endl << "===========" << endl;
    int arrayRR[7] = {1,0, 2,0,0,0,3};
    root = BTNode<int>::buildTreeBy(arrayRR, 7,[](int v)->bool{
        return v > 0;
    });
    
    
    BTNode<int>::singleRotateRR(root);
    root->printTreeLikeTree();
    
    if (root)
    {
        delete root;
        root = nullptr;
    }
    
    cout << endl << "===========" << endl;
    int arrayLR[5] = {3, 1, 0, 0, 2};
    root = BTNode<int>::buildTreeBy(arrayLR, 5,[](int v)->bool{
        return v > 0;
    });
    
    
    BTNode<int>::doublerotateLR(root);
    root->printTreeLikeTree();
    
    if (root)
    {
        delete root;
        root = nullptr;
    }
    
    
    cout << endl << "===========" << endl;
    int arrayRL[6] = {1, 0, 3, 0, 0, 2};
    root = BTNode<int>::buildTreeBy(arrayRL, 6,[](int v)->bool{
        return v > 0;
    });
    
    
    BTNode<int>::doublerotateRL(root);
    root->printTreeLikeTree();
    
    if (root)
    {
        delete root;
        root = nullptr;
    }
    
    
    
    //==================================
    cout << endl << "=================" << "构建平衡二叉查找树" << "=================" << endl;
    int avlLL[4] = {9,7,0,10};
    root = BTNode<int>::buildAVLTree(avlLL, 4);
    root->printTreeLikeTree();
    
    BTNode<int>::insertAVLNode(root, 4);
    root->printTreeLikeTree();
    
    BTNode<int>::insertAVLNode(root, 5);
    root->printTreeLikeTree();
    
    BTNode<int>::insertAVLNode(root, 3);
    root->printTreeLikeTree();
    
    BTNode<int>::insertAVLNode(root, 1);
    root->printTreeLikeTree();
    
    BTNode<int>::insertAVLNode(root, 6);
    root->printTreeLikeTree();
    
    BTNode<int>::insertAVLNode(root, 8);
    root->printTreeLikeTree();
    
    BTNode<int>::insertAVLNode(root, 2);
    root->printTreeLikeTree();
    
    BTNode<int>::insertAVLNode(root, 12);
    root->printTreeLikeTree();
    
    root->printTreeLikeTree();
    return 0;
}
