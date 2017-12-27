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

#include "BaseTree.h"
#include "BSTree.h"

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
    
    BSTree<int> *bstRoot = BSTree<int>::buildBSTree(bstArray, 8);
    
    bstRoot->printTreeLikeTree([](int value){
        cout << value;
    });
    
    
    bstRoot->insertNode(std::move(bstRoot), 1);
    bstRoot->printTreeLikeTree();
    
    bstRoot->insertNode(std::move(bstRoot), 7);
    bstRoot->printTreeLikeTree();
    
    bstRoot->searchMin();
    bstRoot->searchMax();
    
    bstRoot->search(23);
    
    bstRoot->search(3);
    return 0;
}
