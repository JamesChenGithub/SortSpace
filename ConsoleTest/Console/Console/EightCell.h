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


template <typename T>
class TEightCell : public ConsoleTable<int> {
    
    
    struct CellStatus
    {
        unsigned int tableSize;
        T   *targetCells;
        int step;
        CellStatus *lastStatusRef;
        std::list<CellStatus *> openList;
        
        ~CellStatus()
        {
            if (targetCells)
            {
                delete [] targetCells;
                targetCells = nullptr;
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
        
        std::string statusId() const
        {
            
        }
    };
    
    
    class  TEightCellBFSearcher
    {
        CellStatus *startStatus;
        CellStatus *targetStatus;
        
        std::map<std::string, CellStatus *> tagedStatus;
        
        bool isTarget(CellStatus *status)
        {
            return false;
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
    
    void printGame(int type)
    {
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
        while (++count <= step)
        {
            int i = rand()%4;
            move(i);
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
    
    void move(int type, bool reverse = false)
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
        }
    }
};



#endif /* EightCell_h */
