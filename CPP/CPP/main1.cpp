//
//  main.m
//  CPP
//
//  Created by AlexiChen on 2017/11/23.
//  Copyright © 2017年 AlexiChen. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <math.h>
#include <initializer_list>

using namespace std;
//============================
// sample1
//
//在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

void sample1()
{
    vector<vector<int>> array;
    int row = abs(rand()) % 10 + 5;
    while (row > 0)
    {
        vector<int> rowarray;
        
        int col = abs(rand()) % 10 + 10;
        int bignum = 1000;
        int delta = 1000/col;
        while (col > 0)
        {
            int num = rand()%delta + bignum;
            rowarray.push_back(num);
            bignum -= delta;
            col--;
        }
        array.push_back(rowarray);
        row--;
    }
    
    for (auto rowarray : array)
    {
        for (auto num : rowarray)
        {
            cout << num << " ";
        }
        
        cout << endl;
    }
    
    int findnum ;
    cin >> findnum;
    
    
    for (auto rowarray : array)
    {
        for (auto num : rowarray)
        {
            if (num == findnum)
            {
                vector<vector<int>>::iterator row = find(array.begin(), array.end(), rowarray);
                vector<int>::iterator col = find(rowarray.begin(), rowarray.end(), num);
                
                cout << "find num at row =" << row -  array.begin() << "  col = " << col - rowarray.begin() << endl;
                break;
            }
        }
    }
    cout << "1 not found" << endl;
    
    for (vector<vector<int>>::iterator it = array.begin(); it != array.end(); it++)
    {
        if (!(findnum > *(it->begin()) || findnum < *(it->rbegin())))
        {
            vector<int>::iterator col = find(it->begin(), it->end(), findnum);
            if (col != it->end())
            {
                cout << "find num at row =" << it -  array.begin() << "  col = " << col - it->begin() << endl;
                break;
            }
        }
    }
    
    cout << "2 not found" << endl;
    
    for (vector<vector<int>>::iterator it = array.begin(); it != array.end(); it++)
    {
        vector<int>::iterator col = find(it->begin(), it->end(), findnum);
        if (col != it->end())
        {
            cout << "find num at row =" << it -  array.begin() << "  col = " << col - it->begin() << endl;
            break;
        }
    }
    
    cout << "3 not found" << endl;
    
}

//=========================
// sample 2
//请实现一个函数，将一个字符串中的空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

void sameple2()
{
    string str;
    getline(cin, str);
    getline(cin, str);
    
    string::size_type pos(0);
    string blank(" ");
    
    while (true) {
        pos = str.find(blank);
        if (pos == string::npos)
        {
            break;
        }
        else
        {
            str.replace(pos, blank.length(), "%20");
        }
    }
    
    cout << str << endl;
}

//=========================
// sample 3
// 输入一个链表，从尾到头打印链表每个节点的值。
typedef struct ListNode
{
    int value;
    ListNode *next;
    
    ListNode(int a = 0) : value (a), next(NULL){
        
    }
    
    ~ListNode() {
        
        cout << value << " ";
        if (next)
        {
            delete next;
            next = nullptr;
        }
    }
    
    void addValue(int a)
    {
        ListNode *node = new ListNode(a);
        
        if (next)
        {
            ListNode *curNode = next;
            while(curNode->next)
            {
                curNode = curNode->next;
            }
            
            curNode->next = node;
        }
        else
        {
            next = node;
        }
        
    }
    
    
    void reversePrint()
    {
        if (next == nullptr)
        {
            cout << value <<" ";
        }
        else
        {
            next->reversePrint();
            cout << value <<" ";
        }
        
    }
    
} ListNode, LinkList;

void sample3()
{
    int row = 3;abs(rand()) % 10 + 5;
    LinkList *ll = new ListNode();
    while (row-- >= 0)
    {
        int va = abs(rand()) % 10 + 5;
        cout << va << " ";
        ll->addValue(va);
    }
    cout << endl;
    LinkList *llTemp = ll->next;
    
    while (llTemp)
    {
        cout << llTemp->value << " ";
        llTemp = llTemp->next;
    }
    
    cout << endl;
    
    ll->reversePrint();
    
    cout << endl;
    delete ll;
    ll = NULL;
}


//==========================

double factorial(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    else
    {
        return n*factorial(n-1);
    }
}

double denominator(int n)
{
    if (n == 1)
    {
        return 3;
    }
    else
    {
        return (2 * n + 1) * denominator(n - 1);
    }
    
}

double func(int n)
{
    if (n <= 0)
    {
        return 1;
    }
    else
    {
        double fa = factorial(n);
        double de = denominator(n);
        return fa/de + func(n-1);
    }
}

void PI()
{
    int n = 150;
    double PI = 2 * func(n);
    
    printf("%.100f\n", PI);
    
}

//==========================
//二叉树
//输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
typedef struct TreeNode{
    int value;
    char c;
    TreeNode *left;
    TreeNode *right;
    
    TreeNode(int a = 0) : value (a), left(nullptr), right(nullptr){
        
    }
    
    
    ~TreeNode()
    {
        printValue();
        if (left)
        {
            delete left;
            left = nullptr;
        }
        
        if (right)
        {
            delete right;
            right = nullptr;
        }
    }
    
    
    void mirror()
    {
        TreeNode *temp = left;
        left = right;
        right = temp;
        
        if (left)
        {
            left->mirror();
        }
        
        if (right)
        {
            right->mirror();
        }
        
    }
    
    bool addValue(bool aleft, int value)
    {
        if (aleft)
        {
            if (left)
            {
                return false;
            }
            else
            {
                this->left = new TreeNode(value);
                return true;
            }
        }
        else
        {
            if (right)
            {
                return false;
            }
            else
            {
                this->right = new TreeNode(value);
                return false;
            }
        }
    }
    
    int treeheight()
    {
        if (left == nullptr && right == nullptr)
        {
            return 1;
        }
        else
        {
            int lh = 0;
            int rh = 0;
            if (left)
            {
                lh = left->treeheight();
            }
            
            if (right)
            {
                rh = right->treeheight();
            }
            
            int height =  lh > rh ? lh : rh;
            return height + 1;
        }
    }
    
    void printValue()
    {
        if (value != 0)
        {
            cout << value << " ";
        }
        else
        {
            cout << c << " ";
        }
    }
    
    void printValueInLevel()
    {
        if (value != 0)
        {
            cout << value << " ";
        }
        else
        {
            cout << c << " ";
        }
    }
    
    void printByLevel()
    {
        typedef std::pair<int, TreeNode *>  TreeNodePair;
        TreeNodePair pair;
        int level = 0;
        std::queue<TreeNodePair> queue;
        queue.push(std::make_pair(level, this));
        
        
        do
        {
            TreeNodePair pair = queue.front();
            
            queue.pop();
            
            int lev = pair.first;
            TreeNode *node = pair.second;
            
            node->printValue();
            
            if (node->left)
            {
                queue.push(std::make_pair(lev+1, node->left));
            }
            
            if (node->right)
            {
                queue.push(std::make_pair(lev+1, node->right));
            }
            
            
            TreeNodePair newpair = queue.front();
            
            if (newpair.first != lev)
            {
                cout << endl;
            }
            
        }while(!queue.empty());
        
    }
    
    
    void printLikeTree()
    {
        typedef std::pair<int, TreeNode *>  TreeNodePair;
        TreeNodePair pair;
        int level = 0;
        std::queue<TreeNodePair> queue;
        queue.push(std::make_pair(level, this));
        
        
        do
        {
            TreeNodePair pair = queue.front();
            
            queue.pop();
            
            int lev = pair.first;
            TreeNode *node = pair.second;
        
            if (node->left)
            {
                int lh = node->left->treeheight();
                for (int i = 0; i < lh; i++)
                {
                    cout << " ";
                }
                queue.push(std::make_pair(lev+1, node->left));
            }
            
            node->printValue();
            
            if (node->right)
            {
                queue.push(std::make_pair(lev+1, node->right));
            }
            
            
            TreeNodePair newpair = queue.front();
            
            if (newpair.first != lev)
            {
                cout << endl;
            }
            
        }while(!queue.empty());
        
    }
    
    void preOrderTraversal()
    {
        printValue();
        if (left)
        {
            left->preOrderTraversal();
        }
        
        if (right)
        {
            right->preOrderTraversal();
        }
    }
    
    
    void inOrderTraversal()
    {
       
        if (left)
        {
            left->inOrderTraversal();
        }
        
        printValue();
        
        if (right)
        {
            right->inOrderTraversal();
        }
    }
    
    void postOrderTraversal()
    {
        
        if (left)
        {
            left->postOrderTraversal();
        }
        
        if (right)
        {
            right->postOrderTraversal();
        }
        
        printValue();
    }
    
} TreeNode;

//1 2 4 6 7 8 3 5
//4 7 6 8 2 1 3 5
//7 8 6 4 2 5 3 1

TreeNode *rebuildNode(int *preOrderArray, int prefrom, int preend, int *inOrderArray, int infrom, int inend)
{
    if (prefrom > preend || infrom > inend)
    {
        return nullptr;
    }
    
    TreeNode *root = new TreeNode(preOrderArray[prefrom]);
    
    for (int i = infrom; i <= inend; i++)
    {
        if (inOrderArray[i] == preOrderArray[prefrom])
        {
            root->left = rebuildNode(preOrderArray, prefrom + 1, i - infrom + prefrom, inOrderArray, infrom, i - 1);
            root->right = rebuildNode(preOrderArray, i - infrom + prefrom + 1, preend, inOrderArray, i+1, inend);
        }
    }
    
    
    return root;
    
}




TreeNode *rebuildTree(int *preOrderArray, int *inOrderArray, int size)
{
    if (preOrderArray == nullptr || inOrderArray == nullptr || size <= 0)
    {
        cerr << "参数错误" << endl;
        return nullptr;
    }
    
    
    return rebuildNode(preOrderArray, 0, size - 1, inOrderArray, 0, size - 1);
}

void randGetAdd(int &nodeCount, int &hasGen, int parVale, TreeNode *&node)
{
    // 创建随机的二叉树
    if (nodeCount == 0)
    {
        cout << parVale << "无子结点 ：";
        if (node)
        {
            delete node;
            node = nullptr;
        }
        else
        {
            node = nullptr;
        }
    }
    else
    {
        if (hasGen > 0)
        {
            cout << hasGen << endl;
        }
        
        nodeCount--;
        node = new TreeNode(hasGen);
        
        parVale = hasGen;
        if (rand()%2)
        {
            cout << parVale << "左结点 ：";
            hasGen++;
            randGetAdd(nodeCount, hasGen, parVale, node->left);
        }
        else
        {
            cout << hasGen << "无左结点" << endl;
        }
        
        
        if (rand()%2)
        {
            cout << parVale << "右结点 ：";
            hasGen++;
            randGetAdd(nodeCount, hasGen, parVale, node->right);
        }
        else
        {
            cout << hasGen << "无右结点" << endl;
        }
        
        
    }
    
    
}


TreeNode *randTree()
{
    TreeNode *rootNode = nullptr;
    std::queue<TreeNode *> queue;
    
    do
    {
        if (rootNode == nullptr)
        {
            cout << "输入根结点:";
            char root;
            root = getc(stdin);
            rootNode = new TreeNode(0);
            rootNode->c = root;
            queue.push(rootNode);
            getc(stdin);
        
        }
        else
        {
            TreeNode *node = queue.front();
            queue.pop();
            
            cout << "输入"<< node->c <<"结点在左结点:";
            char left;
            left = getc(stdin);
            
           
            if (isalnum(left))
            {
                TreeNode *leftNode = new TreeNode(0);
                leftNode->c = left;
                node->left = leftNode;
                queue.push(leftNode);
                
                getc(stdin);
            }
            
            
            cout << "输入"<< node->c <<"结点在右结点:";
            char right;
            
            right = getc(stdin);
            if (isalnum(right))
            {
                TreeNode *rightNode = new TreeNode(0);
                rightNode->c = right;
                node->right = rightNode;
                queue.push(rightNode);
                
                
                getc(stdin);
            }
        }
        
    }while (!queue.empty());
    
    
    rootNode->printByLevel();
    
    return rootNode;
}


// 使用完全二叉树数组生成树
// nodeNum < 32
TreeNode *randTreeBy()
{
    const int kMaxNode = 8;
    const int kMaxNodeArraySize = kMaxNode << 1;
    
    uint8_t *nodeArray = (uint8_t *)malloc(kMaxNodeArraySize);
    bzero(nodeArray, 2 * kMaxNodeArraySize);
    
    nodeArray[0] =  1;
    nodeArray[1] =  1;
    nodeArray[2] =  1;
    
    int nn = 3;
    int level = 2;
    
    
    // 生成二维数据的连续空立
    
    
    
    
    while (nn < kMaxNode)
    {
        level++;
        
        // 第level层有的数据个数
        int min = 1 << (level - 1);
        int max = 1 << level;
        
        int count = 0;
        int arrindex = min-1;
        int notleafCount = 0;
        while (count < max - min && nn < kMaxNode)
        {
            
            
            int rooiIndex = arrindex >> 1;
            
            if ( rooiIndex < kMaxNode && nodeArray[rooiIndex] != 0)
            {
                
                if (abs(rand()%2) == 0)
                {
                    nn++;
                    nodeArray[arrindex++] = 1;
                }
                else
                {
                    arrindex++;
                    notleafCount++;
                }
            }
            count++;
        }
        
        if (notleafCount == max - min)
        {
            break;
        }
        
    }
    
    
    for (int i = 0; i < kMaxNode; i++)
    {
        cout << nodeArray[i];
    }
    
    cout << endl;
    
    
    

    int arrindex = 0;
    
    TreeNode *root = new TreeNode(nodeArray[arrindex]);
    std::pair<int, TreeNode *> rootPair = std::make_pair(arrindex, root);
    std::queue<std::pair<int, TreeNode *>> rootQueue;
    rootQueue.push(rootPair);
    
    int start = nodeArray[arrindex];
    
    
    do
    {
        std::pair<int, TreeNode *> pair = rootQueue.front();
        rootQueue.pop();
        
        int index = pair.first;
        TreeNode *node = pair.second;
        if ( 2*index + 1 < kMaxNode && nodeArray[2*index + 1] == 1)
        {
            node->left = new TreeNode(start+1);
            std::pair<int, TreeNode *> rootPair = std::make_pair(2*index + 1, node->left);
            rootQueue.push(rootPair);
        }
        
        if ( 2*index + 2 < kMaxNode && nodeArray[2*index + 2] == 1)
        {
            node->left = new TreeNode(start+1);
            std::pair<int, TreeNode *> pair = std::make_pair(2*index + 2, node->right);
            rootQueue.push(pair);
        }
    }while (!rootQueue.empty());
    
    free(nodeArray);
    
    return nullptr;
}







//TreeNode *createTree(int nodeCount)
//{
//    TreeNode *root = new TreeNode(0);
//    nodeCount--;
//
//    int hasGen = 1;
//
//
//    if (nodeCount > 0)
//    {
//        randGetAdd(nodeCount, hasGen, root->left);
//    }
//
//    if (nodeCount > 0)
//    {
//        randGetAdd(nodeCount, hasGen, root->right);
//    }
//
//
//    return root;
//}


//1 2 4 6 7 8 3 5
//4 7 6 8 2 1 3 5
//7 8 6 4 2 5 3 1


//==========================

int main1(int argc, const char * argv[]) {
    
//    sample3();
    
    
    
    TreeNode * root = randTree();
    cout << endl;
    root->printLikeTree();
    cout << endl;
    root->preOrderTraversal();
    cout << endl;
    root->inOrderTraversal();
    cout << endl;
    root->postOrderTraversal();
    cout << endl;
    
    
    cout << "====================" << endl;
    root->mirror();
    
    cout << endl;
    root->printLikeTree();
    cout << endl;
    root->preOrderTraversal();
    cout << endl;
    root->inOrderTraversal();
    cout << endl;
    root->postOrderTraversal();
    cout << endl;
    
    return 0;
    
    
    
//    TreeNode *root = nullptr;
//    int treenum = 10;
//    int hasCount = 0;
//    randGetAdd(treenum, hasCount, -1, root);
//
//    cout << endl;
//    if (root)
//    {
//        root->preorderTraversal();
//        delete root;
//        root = nullptr;
//    }
    
    //1 2 4 6 7 8 3 5
    //4 7 6 8 2 1 3 5
    
    int preOrder[]={1,2,4,6,7,8,3,5};
    int inOrder[]={4,7,6,8,2,1,3,5};
    TreeNode *nroot = rebuildTree(preOrder, inOrder, 8);
    
    cout << endl;
    nroot->printLikeTree();
    cout << endl;
    nroot->preOrderTraversal();
    cout << endl;
    nroot->inOrderTraversal();
    cout << endl;
    nroot->postOrderTraversal();
    cout << endl;
    
    
    return 0;
}
