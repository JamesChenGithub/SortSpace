//
//  Game2048.h
//  Console
//
//  Created by AlexiChen on 2018/1/5.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef Game2048_h
#define Game2048_h

#include "ConstoleTable.hpp"

template <typename T>
class Game2048:  ConsoleTable<T>
{
protected:
    T gameScore = 0;
public:
    
    ~Game2048()
    {
    }
    
    Game2048():ConsoleTable<T>()
    {
    }
    
    Game2048(unsigned int row, unsigned int column, unsigned int rowm = 1, unsigned int colm = 1):ConsoleTable<T>(row, column, rowm, column){
        
    }
    
    
    
    
    
    void printGame(std::function<void (T)> gameShow, std::function<std::string (T)> toStrFunc, bool needclear = true) const
    {
        if (needclear)
        {
            //            system("clear");
        }
        std::string str = toStrFunc(gameScore);
        std::cout << "当前得分：" << (str.length() > 0 ? str : "0") << std::endl;
        this->drawTable(gameShow);
    }
    
    
    
    bool isRealGameOver(std::function<bool (T, T)> equalFunc)
    {
        // 水平检查
        for (int i = 0; i < this->tableRow - 1; i++)
        {
            for (int j = 0; j < this->tableColumn - 1; j++)
            {
                T hor1 = *(this->tableContent + (i * this->tableColumn + j));
                T hor2 = *(this->tableContent + (i * this->tableColumn + j + 1));
                if (equalFunc(hor1, hor2))
                {
                    return false;
                }
                
                T ver2 = *(this->tableContent + ((i+1) * this->tableColumn + j));
                if (equalFunc(hor1, ver2))
                {
                    return false;
                }
            }
        }
        return true;
    }
    
    
    
    void game2048Start(std::function<T (int i)> func, std::function<T ()> initScore, std::function<std::string (T)> toStrFunc, std::function<T (bool)> genFunc, std::function<bool (T)> validFunc, std::function<bool (T &, T&, T&, bool)> mergeFunc, std::function<bool (T, T)> equalFunc)
    {
        initGame2048(func, initScore);
        
        bool stop = true;
        bool isFirst = true;
        
        int cellWidth = this->tableRowMargin * kSpaceSize;
        int stepcount = 0;
        do
        {
            
            std::function<void (T)> gameShow = [=](int i){
                
                std::string str = toStrFunc(i);
                
                int maxSpce = this->tableRowMargin * kSpaceSize;
                
                if (str.length() < maxSpce)
                {
                    int count = (int)(maxSpce - str.length());
                    while(count > 0)
                    {
                        count--;
                        std::cout << " ";
                    }
                    std::cout << str;
                }
            };
            
            
            bool isOver = randValue((isFirst ? 4 : 1), validFunc, genFunc, toStrFunc);
            isFirst = false;
            if (isOver)
            {
                bool isRealOver = isRealGameOver(equalFunc);
                if (isRealOver)
                {
                    std::cout << "=*=*=*=*=*=*游戏结束=*=*=*=*=*=*" << std::endl;
                    printGame(gameShow, toStrFunc);
                    break;
                }
            }
            
            std::cout << "=*=*=*=*=*=*=*=*=*=*=*=*第"<< ++stepcount << "轮操作=*=*=*=*=*=*=*=*=*=*=*=*" << std::endl;
            if (this->maxStrWidht(toStrFunc) >= cellWidth)
            {
                this->setmargin(this->tableRowMargin + 1, this->tableColumnMargin + 1);
                cellWidth = this->tableRowMargin * kSpaceSize;
            }
            
            printGame(gameShow, toStrFunc);
            // 等用户按键
            char c = 0;
            do
            {
                std::cout << "请输入 a(左),w(上),d(右),s(下)建行操作：";
                std::string str;
                getline(std::cin, str);
                const char *cstr = str.c_str();
                c = *cstr;
                if (c >= 96 && handleGame(c, validFunc, toStrFunc, mergeFunc, gameShow))
                {
                    break;
                }
                else
                {
                    usleep(1000000 * 2);
                }
                
            }while(true);
            
            
            if (isRealGameOver(equalFunc))
            {
                std::cout << "=*=*=*=*=*=*游戏结束=*=*=*=*=*=*" << std::endl;
                printGame(gameShow, toStrFunc);
                break;
            }
            
            
        }while(stop);
    }
    
    
private:
    
    void initGame2048(std::function<T (int i)> func, std::function<T ()> initScore,int row = 4, int col = 4)
    {
        this->resizeTable(row, col, func);
        gameScore = initScore();
    }
    
    bool handleGame(char c, std::function<bool (T)> validFunc, std::function<std::string (T)> toStrFunc, std::function<bool (T &, T&, T&, bool)> mergeFunc, std::function<void (T)> gameShow, bool print = false)
    {
        if (c == 'a')
        {
            // 左
            for (int i = 0; i < this->tableRow; i++)
            {
                // 合并
                {
                    int fromIndex = 0;
                    bool findfirst = false;
                    
                    for (int j = 0; j < this->tableColumn; j++)
                    {
                        if (print)
                            std::cout << "========>>>> 左合并" << std::endl;
                        int index =  i * this->tableColumn + j;
                        T v = *(this->tableContent + index);
                        if (validFunc(v))
                        {
                            if (findfirst)
                            {
                                bool succ = mergeFunc(*(this->tableContent + fromIndex), *(this->tableContent + index), gameScore, true);
                                if (succ)
                                {
                                    fromIndex = 0;
                                    findfirst = false;
                                }
                                else
                                {
                                    fromIndex = index;
                                    findfirst = true;
                                }
                                if (print)
                                    printGame(gameShow, toStrFunc);
                            }
                            else
                            {
                                fromIndex = index;
                                findfirst = true;
                            }
                        }
                    }
                }
                
                // 平移
                {
                    int fromIndex = -1;
                    bool findFirst = false;
                    for (int j = 0; j < this->tableColumn; j++)
                    {
                        if (print)
                            std::cout << "========>>>> 左平移" << std::endl;
                        int index =  i * this->tableColumn + j;
                        T v = *(this->tableContent + index);
                        
                        if (validFunc(v))
                        {
                            if (findFirst)
                            {
                                T temp;
                                mergeFunc(*(this->tableContent + fromIndex), *(this->tableContent + index), temp, false);
                                
                                int col = fromIndex%this->tableColumn + 1;
                                if (col < j)
                                {
                                    while (col < j)
                                    {
                                        int colindex =  i * this->tableColumn + col;
                                        T v = *(this->tableContent + colindex);
                                        col++;
                                        if(!validFunc(v))
                                        {
                                            fromIndex = colindex;
                                            findFirst = true;
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    fromIndex = index;
                                    findFirst = true;
                                }
                                
                                
                                if (print)
                                    printGame(gameShow, toStrFunc);
                            }
                        }
                        else
                        {
                            if(!findFirst)
                            {
                                fromIndex = index;
                                findFirst = true;
                            }
                        }
                    }
                }
            }
            if (print)
                printGame(gameShow, toStrFunc);
            
            return true;
        }
        else if (c == 'w')
        {
            // 上
            for (int i = 0; i < this->tableColumn; i++)
            {
                // 合并
                {
                    int fromIndex = 0;
                    bool findfirst = false;
                    
                    for (int j = 0; j < this->tableRow; j++)
                    {
                        if (print)
                            std::cout << "========>>>> 上合并" << std::endl;
                        int index =  j * this->tableColumn + i;
                        T v = *(this->tableContent + index);
                        if (validFunc(v))
                        {
                            if (findfirst)
                            {
                                bool succ = mergeFunc(*(this->tableContent + fromIndex), *(this->tableContent + index), gameScore, true);
                                if (succ)
                                {
                                    fromIndex = 0;
                                    findfirst = false;
                                }
                                else
                                {
                                    fromIndex = index;
                                    findfirst = true;
                                }
                                if (print)
                                    printGame(gameShow, toStrFunc);
                            }
                            else
                            {
                                fromIndex = index;
                                findfirst = true;
                            }
                        }
                    }
                }
                
                // 平移
                {
                    int fromIndex = -1;
                    bool findFirst = false;
                    for (int j = 0; j < this->tableRow; j++)
                    {
                        if (print)
                            std::cout << "========>>>> 上平移" << std::endl;
                        int index =  j * this->tableColumn + i;
                        T v = *(this->tableContent + index);
                        
                        if (validFunc(v))
                        {
                            if (findFirst)
                            {
                                T temp;
                                mergeFunc(*(this->tableContent + fromIndex), *(this->tableContent + index), temp, false);
                                
                                
                                int col = fromIndex/this->tableColumn + 1;
                                if (col < j)
                                {
                                    while (col < j)
                                    {
                                        int colindex =  i * this->tableColumn + col;
                                        T v = *(this->tableContent + colindex);
                                        col++;
                                        if(!validFunc(v))
                                        {
                                            fromIndex = colindex;
                                            findFirst = true;
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    fromIndex = index;
                                    findFirst = true;
                                }
                                
                                if (print)
                                    printGame(gameShow, toStrFunc);
                            }
                        }
                        else
                        {
                            if(!findFirst)
                            {
                                fromIndex = index;
                                findFirst = true;
                            }
                        }
                    }
                }
            }
            if (print)
                printGame(gameShow, toStrFunc);
            
            return true;
        }
        else if (c == 'd')
        {
            // 右
            for (int i = 0; i < this->tableRow; i++)
            {
                // 合并
                {
                    if (print)
                        std::cout << "========>>>> 右合并" << std::endl;
                    int fromIndex = 0;
                    bool findfirst = false;
                    
                    for (int j = this->tableColumn - 1; j >=0; j--)
                    {
                        int index =  i * this->tableColumn + j;
                        T v = *(this->tableContent + index);
                        if (validFunc(v))
                        {
                            if (findfirst)
                            {
                                bool succ = mergeFunc(*(this->tableContent + fromIndex), *(this->tableContent + index), gameScore, true);
                                if (succ)
                                {
                                    fromIndex = 0;
                                    findfirst = false;
                                }
                                else
                                {
                                    fromIndex = index;
                                    findfirst = true;
                                }
                                if (print)
                                    printGame(gameShow, toStrFunc);
                            }
                            else
                            {
                                fromIndex = index;
                                findfirst = true;
                            }
                        }
                    }
                }
                
                // 平移
                {
                    int fromIndex = -1;
                    bool findFirst = false;
                    for (int j = this->tableColumn - 1; j >=0; j--)
                    {
                        if (print)
                            std::cout << "========>>>> 右平移" << std::endl;
                        int index =  i * this->tableColumn + j;
                        T v = *(this->tableContent + index);
                        
                        if (validFunc(v))
                        {
                            if (findFirst)
                            {
                                T temp;
                                mergeFunc(*(this->tableContent + fromIndex), *(this->tableContent + index), temp, false);
                                
                                int col = fromIndex%this->tableColumn - 1;
                                if (col > j)
                                {
                                    while (col > j)
                                    {
                                        int colindex =  i * this->tableColumn + col;
                                        T v = *(this->tableContent + colindex);
                                        col--;
                                        if(!validFunc(v))
                                        {
                                            fromIndex = colindex;
                                            findFirst = true;
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    fromIndex = index;
                                    findFirst = true;
                                }
                                
                                
                                if (print)
                                    printGame(gameShow, toStrFunc);
                            }
                        }
                        else
                        {
                            if(!findFirst)
                            {
                                fromIndex = index;
                                findFirst = true;
                            }
                        }
                    }
                }
            }
            if (print)
                printGame(gameShow, toStrFunc);
            return true;
        }
        else if (c == 's')
        {
            // 下
            for (int i = 0; i < this->tableColumn; i++)
            {
                // 合并
                {
                    int fromIndex = 0;
                    bool findfirst = false;
                    
                    for (int j = this->tableRow - 1; j >= 0; j--)
                    {
                        if (print)
                            std::cout << "========>>>> 下合并" << std::endl;
                        int index =  j * this->tableColumn + i;
                        T v = *(this->tableContent + index);
                        if (validFunc(v))
                        {
                            if (findfirst)
                            {
                                bool succ = mergeFunc(*(this->tableContent + fromIndex), *(this->tableContent + index), gameScore, true);
                                if (succ)
                                {
                                    fromIndex = 0;
                                    findfirst = false;
                                    
                                    if (print)
                                        printGame(gameShow, toStrFunc);
                                }
                                else
                                {
                                    fromIndex = index;
                                    findfirst = true;
                                }
                                
                            }
                            else
                            {
                                fromIndex = index;
                                findfirst = true;
                            }
                        }
                    }
                }
                if (print)
                    printGame(gameShow, toStrFunc);
                // 平移
                {
                    int fromIndex = -1;
                    bool findFirst = false;
                    for (int j = this->tableRow - 1; j >= 0; j--)
                    {
                        if (print)
                            std::cout << "========>>>> 下平移" << std::endl;
                        int index =  j * this->tableColumn + i;
                        T v = *(this->tableContent + index);
                        
                        if (validFunc(v))
                        {
                            if (findFirst)
                            {
                                T temp;
                                mergeFunc(*(this->tableContent + fromIndex), *(this->tableContent + index), temp, false);
                                int col = fromIndex/this->tableColumn - 1;
                                if (col > j)
                                {
                                    while (col > j)
                                    {
                                        int colindex =  i * this->tableColumn + col;
                                        T v = *(this->tableContent + colindex);
                                        col--;
                                        if(!validFunc(v))
                                        {
                                            fromIndex = colindex;
                                            findFirst = true;
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    fromIndex = index;
                                    findFirst = true;
                                }
                                if (print)
                                    printGame(gameShow, toStrFunc);
                            }
                        }
                        else
                        {
                            if(!findFirst)
                            {
                                fromIndex = index;
                                findFirst = true;
                            }
                        }
                    }
                }
            }
            if (print)
                printGame(gameShow, toStrFunc);
            
            return true;
        }
        
        return false;
    }
    
    bool randValue(int count, std::function<bool (T)> validFunc, std::function<T (bool)> genFunc, std::function<std::string (T)> toStrFunc, bool printlog = false)
    {
        int i = count;
        std::vector<int> empty;
        srand( (unsigned)time( NULL ) );
        bool isOver = false;
        while(i > 0)
        {
            empty.clear();
            getEmptySpace(empty, validFunc);
            if (printlog)
            {
                std::cout << "空的格有：" << std::endl;
                std::for_each(empty.begin(), empty.end(), [&](int i){
                    std::cout << "[" << i / this->tableColumn << "][" <<  i % this->tableColumn << "]" << "    ";
                });
            }
            int size = (int)empty.size();
            
            if(size > 0)
            {
                int randIndex = empty[(int)abs(rand()%size)];
                bool isTw0 = abs(rand()%3);
                T value = genFunc(isTw0);
                
                std::cout << std::endl <<"在：" << "[" << randIndex / this->tableColumn << "][" <<  randIndex % this->tableColumn << "]生成:"<< toStrFunc(value) << std::endl;
                *(this->tableContent + randIndex) = value;
                i--;
            }
            else
            {
                isOver = true;
                break;
            }
        }
        return isOver;
        
    }
    
    void getEmptySpace(std::vector<int> &indexvec, std::function<bool (T)> validFunc) const
    {
        for (int i = 0; i < this->tableSize; i++)
        {
            T ov = *(this->tableContent + i);
            bool isV = validFunc(ov);
            if (!isV)
            {
                indexvec.push_back(i);
            }
        }
    }
    
    bool genValue(int index, T v, std::function<bool (T)> validFunc)
    {
        if (index >= 0 && index < this->tableSize)
        {
            T ov = *(this->tableContent + index);
            bool isV = validFunc(ov);
            if (!isV)
            {
                *(this->tableContent + index) = v;
                return true;
            }
            
            return false;
            
        }
        return false;
    }
    
};


#endif /* Game2048_h */
