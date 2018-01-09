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


template <typename T>
class TEightCell : public ConsoleTable<int> {
    
    
    struct CellStatus
    {
        unsigned int row;
        unsigned int col;
        unsigned int tableSize;
        T   *cells;
        int step;
        int spaceIndex;
        CellStatus *lastStatusRef;
        std::list<CellStatus *> openList;
        
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
            if (*(cells + spaceIndex) == 0)
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
        
        
    };
    
    
    class  TEightCellBFSearcher
    {
        CellStatus *startStatus;
        CellStatus *targetStatus;
        
        
        std::queue<CellStatus *> searchqueue;
        
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
        
        bool startSearch(unsigned int arow, unsigned int acol, T *Cells, T *targetCells)
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
                            oldspace -= from->row;
                        }
                        
                        break;
                    case 3:
                        // 下
                        if (row <= from->row - 2)
                        {
                            oldspace += from->row;
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
        
        bool startSearch(CellStatus *from, CellStatus *target)
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
                                searchqueue.push(staus);
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
    
private:
    
    T   *targetCells;
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
    
    TEightCell(unsigned int row, unsigned int column, unsigned int rowm = 1, unsigned int colm = 1):ConsoleTable<int>(row, column, rowm, column){
        targetCells = nullptr;
    }
    
    void printGame(int type, bool needclear = true)
    {
        if (needclear)
        {
            system("clear");
        }
        std::cout << "向" << (type == 0 ? "上" : type == 1 ? "左" : type == 2 ? "右" : "下") << "走" << std::endl;
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
        
        targetCells = new int[this->tableSize];
        memset(targetCells, 0, sizeof(int) * this->tableSize);
        
        
        for (int i = 0; i < this->tableSize; i++)
        {
            *(this->tableContent + i) = i+1;
        }
        
        *(this->tableContent + this->tableSize - 1) = 0;
        spaceIndex = this->tableSize - 1;
        memcpy(targetCells, this->tableContent, sizeof(int) * this->tableSize);
        
        
        srand( (unsigned)time(NULL));
        int count = 0;
        int laststep = -1;
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
                }
                else
                {
                    count--;
                }
            }
        }
        
        std::cout << "============开始算法回调============" << std::endl;
        
        TEightCellBFSearcher  *searcher = new  TEightCellBFSearcher;
        bool succ = searcher->startSearch(this->tableRow, this->tableColumn, this->tableContent, this->targetCells);
        if (succ)
        {
            std::stack<int> & stack = searcher->stepStack;
            
            do {
                int step = stack.top();
                stack.pop();
                move(step);
                usleep(1000000 * 1);
            } while (!stack.empty());
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
                    oldspace -= this->tableRow;
                }
                
                break;
            case 3:
                // 下
                if (row <= this->tableRow - 2)
                {
                    oldspace += this->tableRow;
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
