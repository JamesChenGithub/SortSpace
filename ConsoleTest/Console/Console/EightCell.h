//
//  EightCell.h
//  Console
//
//  Created by AlexiChen on 2018/1/5.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef EightCell_h
#define EightCell_h

#include "ConsoleTable.hpp"

#include <queue>
#include <list>
#include <map>
#include <stack>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

long labs(long a)
{
    return a > 0 ? a : -a;
}


template <typename T>
class TEightCell : public ConsoleTable<int> {
    
    
    struct CellStatus
    {
        unsigned int row;
        unsigned int col;
        unsigned int tableSize;
        T   *cells = nullptr;
        int step = 0;
        int spaceIndex = -1;
        CellStatus *lastStatusRef = nullptr;
        bool hasSearched = false;
        std::list<CellStatus *> openList;
        
        
        long gValue;
        long hValue;
        long fValue;
        
        inline bool operator < (CellStatus const &other) const
        {
            return fValue < other.fValue;
            
        }
        
        CellStatus(unsigned int arow, unsigned int acol, T *acells)
        {
            if(acells)
            {
                row = arow;
                col = acol;
                tableSize = arow * acol;
                cells = new T[tableSize];
                memcpy(cells, acells, sizeof(T) * tableSize);
            }
        }
        
        CellStatus(CellStatus *status)
        {
            if(status)
            {
                row = status->row;
                col = status->col;
                tableSize = status->row * status->col;
                cells = new T[tableSize];
                memcpy(cells, status->cells, sizeof(T) * tableSize);
            }
        }
        
        int getSpaceIndex()
        {
            
            if (spaceIndex >= 0 && spaceIndex < tableSize && *(cells + spaceIndex) == 0)
            {
                return spaceIndex;
            }
            else
            {
                for (int i = 0; i < tableSize; i++)
                {
                    if (*(cells + i) == 0)
                    {
                        spaceIndex = i;
                        return spaceIndex;
                    }
                }
            }
            
            return -1;
        }
        
        
        ~CellStatus()
        {
            if (cells)
            {
                delete [] cells;
                cells = nullptr;
            }
            
            lastStatusRef = nullptr;
            
            std::for_each(openList.begin(), openList.end(), [](CellStatus *sub){
                if (sub)
                {
                    delete sub;
                }
            });
            
            openList.clear();
        }
        
        std::string getStatudId()
        {
            std::stringstream ss;
            if (cells)
            {
                for (int i = 0; i < tableSize; i++)
                {
                    ss << *(cells + i) << "_";
                }
                return ss.str();
            }
            return  "";
        }
    };
    
    
    class  TEightCellBFSearcher
    {
    protected:
        CellStatus *startStatus = nullptr;
        CellStatus *targetStatus = nullptr;
        
        
        std::queue<CellStatus *> searchqueue;
        std::map<std::string, CellStatus *> closeMap;
        
    public:
        std::stack<int> stepStack;
    public:
        bool isTarget(CellStatus *status, bool isdebug = false)
        {
            if (status && targetStatus && status->tableSize == targetStatus->tableSize)
            {
                if(isdebug)
                    std::cout << "======================"<< std::endl;
                for (int i = 0; i < targetStatus->tableSize; i++)
                {
                    if(isdebug)
                        std::cout <<  *(targetStatus->cells + i)  << "    " << *(status->cells + i) << std::endl;
                    if (*(targetStatus->cells + i) != *(status->cells + i))
                    {
                        return false;
                    }
                }
                
                return true;
            }
            return false;
        }
        
        virtual bool startSearch2(unsigned int arow, unsigned int acol, T *Cells, T *targetCells)
        {
            if(Cells && targetCells)
            {
                
                std::stack<int> s;
                //                if (!stepStack.empty())
                //                    stepStack.swap(std::stack<int>());
                
                if (startStatus)
                {
                    delete startStatus;
                    startStatus = nullptr;
                }
                
                startStatus = new CellStatus(arow, acol, Cells);
                
                std::cout << "startStatus  : ";
                for (int i = 0; i < arow * acol; i++)
                {
                    std::cout << *(startStatus->cells + i) << "   ";
                }
                std::cout << std::endl;
                
                if (targetStatus)
                {
                    delete targetStatus;
                    targetStatus = nullptr;
                }
                
                targetStatus = new CellStatus(arow, acol, targetCells);
                
                std::cout << "targetStatus : ";
                for (int i = 0; i < arow * acol; i++)
                {
                    std::cout << *(targetStatus->cells + i) << "   ";
                }
                std::cout << std::endl;
                
                searchqueue.push(startStatus);
                closeMap.insert(std::make_pair(startStatus->getStatudId(), startStatus));
                do
                {
                    CellStatus *from = searchqueue.front();
                    searchqueue.pop();
                    
                    bool succ = startSearch(from, targetStatus);
                    if(succ == true)
                    {
                        return true;
                    }
                }while (!searchqueue.empty());
                
            }
            return false;
        }
        
        
        virtual bool search()
        {
            searchqueue.push(startStatus);
            
            do
            {
                CellStatus *from = searchqueue.front();
                searchqueue.pop();
                
                bool succ = startSearch(from, targetStatus);
                if(succ == true)
                {
                    return true;
                }
            }while (!searchqueue.empty());
            
            return false;
        }
        
        CellStatus * move(CellStatus *from, int type)
        {
            if (from)
            {
                int spaceIndex = from->getSpaceIndex();
                
                if (spaceIndex == -1)
                {
                    return nullptr;
                }
                
                int oldspace = spaceIndex;
                int row = spaceIndex / from->col;
                int col = spaceIndex % from->col;
                switch (type) {
                    case 0:
                        // 上
                        if (row > 0)
                        {
                            oldspace -= from->col;
                        }
                        
                        break;
                    case 3:
                        // 下
                        if (row <= from->row - 2)
                        {
                            oldspace += from->col;
                        }
                        break;
                    case 1:
                        // 左
                        if (col > 0)
                        {
                            oldspace -= 1;
                        }
                        break;
                    case 2:
                        // 右
                        if (col <= from->col - 2)
                        {
                            oldspace += 1;
                        }
                        
                        break;
                        
                    default:
                        break;
                }
                
                if (oldspace != spaceIndex)
                {
                    CellStatus *newstatus = new CellStatus(from);
                    from->openList.push_back(newstatus);
                    newstatus->lastStatusRef = from;
                    
                    int temp = *(newstatus->cells + spaceIndex);
                    *(newstatus->cells + spaceIndex) = *(newstatus->cells + oldspace);
                    *(newstatus->cells + oldspace) = temp;
                    spaceIndex = oldspace;
                    newstatus->spaceIndex = spaceIndex;
                    newstatus->step = type;
                    
                    return newstatus;
                }
            }
            
            return nullptr;
        }
        
        virtual bool startSearch(CellStatus *from, CellStatus *target, bool isReverse = false)
        {
            if (from && target)
            {
                if (isTarget(from))
                {
                    CellStatus *end = from;
                    do
                    {
                        stepStack.push(end->step);
                        end = end->lastStatusRef;
                    } while (end != nullptr);
                    
                    return true;
                }
                else
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (from != startStatus && i == 3 - from->step)
                        {
                            continue;
                        }
                        
                        std::string fromid = from->getStatudId();
                        CellStatus *staus = move(from, i);
                        if (staus)
                        {
                            if (isTarget(staus))
                            {
                                CellStatus *end = staus;
                                do
                                {
                                    stepStack.push(end->step);
                                    end = end->lastStatusRef;
                                } while (end != startStatus);
                                
                                return true;
                            }
                            else
                            {
                                std::string statusid = staus->getStatudId();
                                
                                // std::cout << " 出点串 : " << fromid << "   向" << (i == 0 ? "上" : i == 1 ? "左" : i == 2 ? "右" : "下") << "("<<i<<")走    " <<" 状态串 : " << statusid << std::endl;
                                
                                if (closeMap.find(statusid) == closeMap.end())
                                {
                                    closeMap.insert(std::make_pair(statusid, staus));
                                    searchqueue.push(staus);
                                }
                            }
                            
                        }
                    }
                    
                    return false;
                }
            }
            else
            {
                return false;
                
            }
        }
        
        
    };

    
    class  TEightCellDBFSearcher : public TEightCellBFSearcher
    {
    protected:
        std::queue<CellStatus *> reverseSearchqueue;
        std::map<std::string, CellStatus *> reverseCloseMap;
        
    public:
        virtual bool search()
        {
            this->searchqueue.push(this->startStatus);
            reverseSearchqueue.push(this->targetStatus);
            
            do
            {
                CellStatus *from = this->searchqueue.front();
                this->searchqueue.pop();
                
                bool succ = this->startSearch(from, this->targetStatus, false);
                if(succ == true)
                {
                    return true;
                }
                else
                {
                    CellStatus *last = this->searchqueue.back();
                    std::string lastid = last->getStatudId();
                    
                    auto it = reverseCloseMap.find(lastid);
                    if (it != reverseCloseMap.end())
                    {
                       // 说明找到
                        std::list<int> steplist;
                        
                        CellStatus * end = last;
                        do
                        {
                            steplist.push_front(end->step);
                            end = end->lastStatusRef;
                        } while (end != this->startStatus);
                        
                        
                        CellStatus *reverseend = it->second;
                        reverseend = reverseend->lastStatusRef;
                        do
                        {
                            steplist.push_back(3 - reverseend->step);
                            reverseend = reverseend->lastStatusRef;
                        } while (reverseend != this->targetStatus);
                        
                        while (!this->stepStack.empty())
                        {
                            this->stepStack.pop();
                        }
                        
                        std::for_each(steplist.rbegin(), steplist.rend(), [=](int step){
                            this->stepStack.push(step);
                        });
                        
                        return true;
                    }
                    
                }
                
                
                CellStatus *to = this->reverseSearchqueue.front();
                this->reverseSearchqueue.pop();
                
                succ = this->startSearch(to, this->startStatus);
                if(succ == true)
                {
                    return true;
                }
                else
                {
                    CellStatus *last = this->reverseSearchqueue.back();
                    std::string lastid = last->getStatudId();
                    auto it = this->closeMap.find(lastid);
                    if (this->closeMap.find(lastid) != this->closeMap.end())
                    {
                        // 说明找到
                        
                        // 说明找到
                        std::list<int> steplist;
                        CellStatus * end = it->second;
                        do
                        {
                            steplist.push_front(end->step);
                            end = end->lastStatusRef;
                        } while (end != this->startStatus);
                        
                        
                        CellStatus *reverseend = last;
                        reverseend = reverseend->lastStatusRef;
                        do
                        {
                            steplist.push_back(3 - reverseend->step);
                            reverseend = reverseend->lastStatusRef;
                        } while (reverseend != this->targetStatus);
                        
                        while (!this->stepStack.empty())
                        {
                            this->stepStack.pop();
                        }
                        
                        std::for_each(steplist.rbegin(), steplist.rend(), [=](int step){
                            this->stepStack.push(step);
                        });
                        
                        return true;
                    }
                }
                
            }while (!this->searchqueue.empty() || !this->reverseSearchqueue.empty());
            
            return false;
        }
    };
    
    
    class TEightAStarSearcher : public TEightCellBFSearcher
    {
    protected:
//        std::priority_queue<CellStatus *> searchPriorityQueue;
//    public:
//
//        virtual bool startSearch2(unsigned int arow, unsigned int acol, T *Cells, T *targetCells)
//        {
//            if(Cells && targetCells)
//            {
//
//                std::stack<int> s;
//                //                if (!stepStack.empty())
//                //                    stepStack.swap(std::stack<int>());
//
//                if (this->startStatus)
//                {
//                    delete this->startStatus;
//                    this->startStatus = nullptr;
//                }
//
//                this->startStatus = new CellStatus(arow, acol, Cells);
//
//                std::cout << "startStatus  : ";
//                for (int i = 0; i < arow * acol; i++)
//                {
//                    std::cout << *(this->startStatus->cells + i) << "   ";
//                }
//                std::cout << std::endl;
//
//                if (this->targetStatus)
//                {
//                    delete this->targetStatus;
//                    this->targetStatus = nullptr;
//                }
//
//                this->targetStatus = new CellStatus(arow, acol, targetCells);
//
//                std::cout << "targetStatus : ";
//                for (int i = 0; i < arow * acol; i++)
//                {
//                    std::cout << *(this->targetStatus->cells + i) << "   ";
//                }
//                std::cout << std::endl;
//
//                searchPriorityQueue.push(this->startStatus);
//                this->closeMap.insert(std::make_pair(this->startStatus->getStatudId(), this->startStatus));
//                do
//                {
//                    CellStatus *from = searchPriorityQueue.禾火;
//                    searchPriorityQueue.pop();
//
//                    bool succ = startSearch(from, this->targetStatus);
//                    if(succ == true)
//                    {
//                        return true;
//                    }
//                }while (!this->searchPriorityQueue.empty());
//
//            }
//            return false;
//        }
        virtual void estimateToTarget(CellStatus *&status)
        {
            CellStatus *target = this->targetStatus;
            if (target)
            {
                // 计算每一个方块距离它正确位置的距离
                // 曼哈顿距离
                long manhattanDistance = 0;
                for (int index = 0; index < status->tableSize; ++index)
                {
                    // 略过空格
                    if (index == status->getSpaceIndex())
                    {
                        continue;
                    }

                    int value = status->cells[index];
                    int targetValue = this->targetStatus->cells[index];
                    manhattanDistance += labs(value / status->col - targetValue / target->col) + labs( value % status->col - targetValue % target->col);
                }

                // 增大权重
                status->hValue = 5 * manhattanDistance;
            }
        }
        
        virtual bool startSearch(CellStatus *from, CellStatus *target, bool isReverse = false)
        {
            if (from && target)
            {
                if (this->isTarget(from))
                {
                    CellStatus *end = from;
                    do
                    {
                        this->stepStack.push(end->step);
                        end = end->lastStatusRef;
                    } while (end != nullptr);
                    
                    return true;
                }
                else
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (from != this->startStatus && i == 3 - from->step)
                        {
                            continue;
                        }
                        
                        std::string fromid = from->getStatudId();
                        CellStatus *staus = this->move(from, i);
                        if (staus)
                        {
                            if (this->isTarget(staus))
                            {
                                CellStatus *end = staus;
                                do
                                {
                                    this->stepStack.push(end->step);
                                    end = end->lastStatusRef;
                                } while (end != this->startStatus);
                                
                                return true;
                            }
                            else
                            {
                                std::string statusid = staus->getStatudId();
                                
                                // std::cout << " 出点串 : " << fromid << "   向" << (i == 0 ? "上" : i == 1 ? "左" : i == 2 ? "右" : "下") << "("<<i<<")走    " <<" 状态串 : " << statusid << std::endl;
                                
                                if (this->closeMap.find(statusid) == this->closeMap.end())
                                {
                                    this->closeMap.insert(std::make_pair(statusid, staus));
                                    
                                    staus->gValue = from->gValue + 1;
                                    
                                    estimateToTarget(staus);
                                    
                                    
                                    staus->fValue = staus->gValue + staus->hValue;
                                    
                                    this->searchqueue.push(staus);
                                    
                                    
                                    std::vector<CellStatus *> templist;
                                    while(!this->searchqueue.empty())
                                    {
                                        templist.push_back(this->searchqueue.front());
                                        this->searchqueue.pop();
                                    }
                                    
                                    std::sort(templist.begin(), templist.end(), [](CellStatus *a, CellStatus *b)->long{
                                        return a->fValue - b->fValue;
                                    });
                                    
                                    
                                    std::for_each(templist.begin(), templist.end(), [=](CellStatus *a){
//                                        std::cout << a->fValue << "  ";
                                        this->searchqueue.push(a);
                                    });
                                    std::cout << std::endl;
                                    
                                }
                            }
                            
                        }
                    }
                    
                    return false;
                }
            }
            else
            {
                return false;
                
            }
        }
    };
    
    
protected:
    
    T   *targetCells = nullptr;
    int spaceIndex;
    
    std::vector<int> stepRec;
public:
    
    ~TEightCell()
    {
        if (targetCells)
        {
            delete [] targetCells;
            targetCells = nullptr;
        }
    }
    
    TEightCell():ConsoleTable<int>()
    {
        targetCells = nullptr;
    }
    
    TEightCell(unsigned int row, unsigned int column, unsigned int rowm = 1, unsigned int colm = 1):ConsoleTable<int>(row, column, rowm, colm){
        targetCells = nullptr;
    }
    
    void printGame(int type = -1, bool needclear = true)
    {
        if (needclear)
        {
            system("clear");
        }
        if (type != -1)
        {
            std::cout << "向" << (type == 0 ? "上" : type == 1 ? "左" : type == 2 ? "右" : "下") << "("<<type<<")走" << std::endl;
        }
        this->drawTable2([](int v)->std::string{
            if (v == 0)
            {
                return "";
            }
            return std::to_string(v);
        });
    }
    
    void randomGame(int step = 10)
    {
        stepRec.clear();
        
        memset(this->tableContent, 0, sizeof(int) * this->tableSize);
        
        
        if (targetCells)
        {
            delete [] targetCells;
            targetCells = nullptr;
        }
        
        targetCells = new T[this->tableSize];
        memset(targetCells, 0, sizeof(int) * this->tableSize);
        
        
        for (int i = 0; i < this->tableSize; i++)
        {
            *(this->tableContent + i) = i+1;
        }
        
        *(this->tableContent + this->tableSize - 1) = 0;
        spaceIndex = this->tableSize - 1;
        memcpy(targetCells, this->tableContent, sizeof(int) * this->tableSize);
        
        printGame();
        
        
        srand((unsigned)time(NULL));
        int count = 0;
        int laststep = -1;
        std::vector<int> stepss;
        while (++count <= step)
        {
            int i = rand()%4;
            
            if (i + laststep == 3)
            {
                count--;
            }
            else
            {
                if (move(i))
                {
                    laststep = i;
                    stepss.push_back(i);
                }
                else
                {
                    count--;
                }
            }
        }
        
        std::cout << "产生的路径是:" << std::endl;
        std::for_each(stepss.begin(), stepss.end(), [](int step){
            std::cout << step <<", ";
        });
        std::cout<< std::endl;
        
        T *cells = new T[this->tableSize];
        memcpy(cells, this->tableContent, sizeof(int) * this->tableSize);
        
        {
            std::cout << "============开始A*先算法回调============" << std::endl;
            TEightAStarSearcher *asearcher = new  TEightAStarSearcher;
            bool succ = asearcher->startSearch2(this->tableRow, this->tableColumn, cells, this->targetCells);
            if (succ)
            {
                std::stack<int> & stack = asearcher->stepStack;
                int stepcount = 0;
                do {
                    std::cout << "=============第" << ++stepcount << "步=============" << std::endl;
                    int step = stack.top();
                    stack.pop();
                    move(step);
                    usleep(1000000 * 1);
                } while (!stack.empty());
            }
            else
            {
                std::cout << "=============未找到合适的路径=============" << std::endl;
            }
            delete asearcher;
            asearcher = nullptr;
        }
        
//        {
//            std::cout << "============开始宽度优先算法回调============" << std::endl;
//            TEightCellBFSearcher  *searcher = new  TEightCellBFSearcher;
//            bool succ = searcher->startSearch2(this->tableRow, this->tableColumn, cells, this->targetCells);
//            if (succ)
//            {
//                std::stack<int> & stack = searcher->stepStack;
//                int stepcount = 0;
//                do {
//                    std::cout << "=============第" << ++stepcount << "步=============" << std::endl;
//                    int step = stack.top();
//                    stack.pop();
//                    move(step);
//                    usleep(1000000 * 1);
//                } while (!stack.empty());
//            }
//            else
//            {
//                std::cout << "=============未找到合适的路径=============" << std::endl;
//            }
//            delete searcher;
//            searcher = nullptr;
//        }
//
//        {
//            std::cout << "============开始双向宽度优先算法回调============" << std::endl;
//            TEightCellDBFSearcher  *searcher = new  TEightCellDBFSearcher;
//            bool succ = searcher->startSearch2(this->tableRow, this->tableColumn, cells, this->targetCells);
//            if (succ)
//            {
//                std::stack<int> & stack = searcher->stepStack;
//                int stepcount = 0;
//                do {
//                    std::cout << "=============第" << ++stepcount << "步=============" << std::endl;
//                    int step = stack.top();
//                    stack.pop();
//                    move(step);
//                    usleep(1000000 * 1);
//                } while (!stack.empty());
//            }
//            else
//            {
//                std::cout << "=============未找到合适的路径=============" << std::endl;
//            }
//            delete searcher;
//            searcher = nullptr;
//        }
        
        delete []cells;
        cells = nullptr;
        
    }
    
    
    void randomGameByStep(std::vector<int> vec)
    {
        stepRec.clear();
        
        memset(this->tableContent, 0, sizeof(int) * this->tableSize);
        
        
        if (targetCells)
        {
            delete [] targetCells;
            targetCells = nullptr;
        }
        
        targetCells = new T[this->tableSize];
        memset(targetCells, 0, sizeof(int) * this->tableSize);
        
        
        for (int i = 0; i < this->tableSize; i++)
        {
            *(this->tableContent + i) = i+1;
        }
        
        *(this->tableContent + this->tableSize - 1) = 0;
        spaceIndex = this->tableSize - 1;
        memcpy(targetCells, this->tableContent, sizeof(int) * this->tableSize);
        
        printGame();
        
        
        std::cout << "产生的路径是:" << std::endl;
        std::for_each(vec.begin(), vec.end(), [](int step){
            std::cout << step <<", ";
        });
        std::cout<< std::endl;
        
        std::for_each(vec.begin(), vec.end(), [=](int step){
            this->move(step);
        });
        
        
        //        srand((unsigned)time(NULL));
        //        int count = 0;
        //        int laststep = -1;
        //        while (++count <= step)
        //        {
        //            int i = rand()%4;
        //
        //            if (i + laststep == 3)
        //            {
        //                count--;
        //            }
        //            else
        //            {
        //                if (move(i))
        //                {
        //                    laststep = i;
        //                }
        //                else
        //                {
        //                    count--;
        //                }
        //            }
        //        }
        
        std::cout << "============开始宽度优先算法回调============" << std::endl;
        {
            TEightCellBFSearcher  *searcher = new  TEightCellBFSearcher;
            bool succ = searcher->startSearch(this->tableRow, this->tableColumn, this->tableContent, this->targetCells);
            if (succ)
            {
                std::stack<int> & stack = searcher->stepStack;
                int stepcount = 0;
                do {
                    std::cout << "=============第" << ++stepcount << "步=============" << std::endl;
                    int step = stack.top();
                    stack.pop();
                    move(step);
                    usleep(1000000 * 1);
                } while (!stack.empty());
            }
            else
            {
                std::cout << "=============未找到合适的路径=============" << std::endl;
            }
        }
        
        std::cout << "============开始双向宽度优先算法回调============" << std::endl;
        {
            TEightCellDBFSearcher  *searcher = new  TEightCellDBFSearcher;
            bool succ = searcher->startSearch(this->tableRow, this->tableColumn, this->tableContent, this->targetCells);
            if (succ)
            {
                std::stack<int> & stack = searcher->stepStack;
                int stepcount = 0;
                do {
                    std::cout << "=============第" << ++stepcount << "步=============" << std::endl;
                    int step = stack.top();
                    stack.pop();
                    move(step);
                    usleep(1000000 * 1);
                } while (!stack.empty());
            }
            else
            {
                std::cout << "=============未找到合适的路径=============" << std::endl;
            }
        }
    }
    
    void reverse(unsigned int steps = 0)
    {
        unsigned int size = (unsigned int)stepRec.size();
        if (size > 0 && steps <= size)
        {
            if (steps == 0)
            {
                reverse(size);
            }
            else
            {
                int count = 0;
                while(count < steps)
                {
                    int reversetype = 3 - stepRec.back();
                    move(reversetype, true);
                    stepRec.pop_back();
                    count++;
                }
                
            }
        }
    }
    
    bool move(int type, bool reverse = false)
    {
        int oldspace = spaceIndex;
        int row = spaceIndex / this->tableColumn;
        int col = spaceIndex % this->tableColumn;
        switch (type) {
            case 0:
                // 上
                if (row > 0)
                {
                    oldspace -= this->tableColumn;
                }
                
                break;
            case 3:
                // 下
                if (row <= this->tableRow - 2)
                {
                    oldspace += this->tableColumn;
                }
                break;
            case 1:
                // 左
                if (col > 0)
                {
                    oldspace -= 1;
                }
                break;
            case 2:
                // 右
                if (col <= this->tableColumn - 2)
                {
                    oldspace += 1;
                }
                
                break;
                
            default:
                break;
        }
        
        if (oldspace != spaceIndex)
        {
            int temp = *(this->tableContent + spaceIndex);
            *(this->tableContent + spaceIndex) = *(this->tableContent + oldspace);
            *(this->tableContent + oldspace) = temp;
            spaceIndex = oldspace;
            if (!reverse)
            {
                stepRec.push_back(type);
            }
            printGame(type);
            return true;
        }
        
        return false;
    }
};



#endif /* EightCell_h */
