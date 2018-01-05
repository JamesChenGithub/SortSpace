//
//  ConstoleTable.hpp
//  Console
//
//  Created by AlexiChen on 2018/1/4.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef ConstoleTable_hpp
#define ConstoleTable_hpp

#include <stdio.h>
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <unistd.h>

#ifndef IsMacOS
#define IsMacOS 1
#else
#define IsMacOS 0
#endif

#if IsMacOS
#define kHor "───"
#define kSpace "   "
#define kSpaceSize 3
#else
#define kHor "─"
#define kSpace "  "
#define kSpaceSize 1
#endif

template <typename T>
class ConsoleTable
{
private:
    unsigned int tableRow = 4;
    unsigned int tableColumn = 4;
    unsigned int tableRowMargin = 1;
    unsigned int tableColumnMargin = 1;
    
    const char *on[4] = { "┌", kHor, "┬", "┐" };
    const char *center[4] = { "├", kHor, "┼", "┤" };
    const char *down[4] = { "└", kHor, "┴", "┘" };
    const char *space[2] = { "│", kSpace };
    
    T *tableContent = nullptr;
    unsigned int tableSize = tableRow * tableColumn;
    
    unsigned int kMaxLenth = 2;
    
private:
    T gameScore = 0;
    
    
    
    
public:
    
    ~ConsoleTable()
    {
        std::cout << "释放表格====>>ConsoleTable[" << tableRow << "][" << tableColumn << "]" << std::endl;
        if (tableContent)
        {
            delete [] tableContent;
            tableContent = nullptr;
        }
    }
    
    ConsoleTable()
    {
        std::cout << "构建表格====>>ConsoleTable[" << tableRow << "][" << tableColumn << "]" << std::endl;
        if (!tableContent)
        {
            tableContent = new T[tableRow * tableColumn];
            tableSize = tableRow * tableColumn;
            memset(tableContent, 0, sizeof(T) * tableSize);
        }
    }
    
    ConsoleTable(unsigned int row, unsigned int column, unsigned int rowm = 1, unsigned int colm = 1):tableRow(row), tableColumn(column), tableRowMargin(rowm), tableColumnMargin(colm)
    {
        std::cout << "构建表格====>>ConsoleTable[" << tableRow << "][" << tableColumn << "]" << std::endl;
        if (!tableContent)
        {
            tableContent = new T[tableRow * tableColumn];
            tableSize = tableRow * tableColumn;
            memset(tableContent, 0, sizeof(T) * tableSize);
        }
    }
    
    unsigned int getMaxLength(std::function<unsigned int (T)> func = [](T)->unsigned int{
        return 2;
    })
    {
        return kMaxLenth;
    }
    
    void randContent(std::function<T (int i)> func)
    {
        for (int i = 0; i < tableSize; i++)
        {
            *(tableContent + i) = func(i);
        }
    }
    
    void resizeTable(unsigned int row, unsigned int column, std::function<T (int i)> func)
    {
        if (tableContent)
        {
            delete [] tableContent;
            tableContent = nullptr;
        }
        tableRow = row;
        tableColumn = column;
        tableContent = new T[tableRow * tableColumn];
        tableSize = tableRow * tableColumn;
        memset(tableContent, 0, sizeof(T) * tableSize);
        
        randContent(func);
    }
    
    void drawTable(std::function<void (T)> func = [](T v){
        std::cout << v;
    }) const
    {
        std::cout << "绘制表格["<< tableRow << "][" << tableColumn << "][ hor =" << tableRowMargin <<"][ver="<<tableColumnMargin<<"]====>>" << std::endl;
        drawTop();
        
        drawCenter(func);
        drawBottom();
        
    }
    
    void setmargin(unsigned int h, unsigned int v)
    {
        tableRowMargin = h;
        tableColumnMargin = v;
    }
    
public:
    void initGame2048(std::function<T (int i)> func, std::function<T ()> initScore,int row = 4, int col = 4)
    {
        resizeTable(row, col, func);
        gameScore = initScore();
    }
    
    
    void printGame(std::function<void (T)> gameShow, std::function<std::string (T)> toStrFunc, bool needclear = true) const
    {
        if (needclear)
        {
            //            system("clear");
        }
        std::string str = toStrFunc(gameScore);
        std::cout << "当前得分：" << (str.length() > 0 ? str : "0") << std::endl;
        drawTable(gameShow);
    }
    
    int maxStrWidht(std::function<std::string (T)> toStrFunc)
    {
        int maxlen = 0;
        for (int i = 0; i < tableSize; i++)
        {
            T ov = *(tableContent + i);
            std::string str = toStrFunc(ov);
            int strlen = (int)str.length();
            if (strlen > maxlen)
            {
                maxlen = strlen;
            }
        }
        
        return maxlen;
    }
    
    
    
    void game2048Start(std::function<T (int i)> func, std::function<T ()> initScore, std::function<std::string (T)> toStrFunc, std::function<T (bool)> genFunc, std::function<bool (T)> validFunc, std::function<bool (T &, T&, T&, bool)> mergeFunc)
    {
        initGame2048(func, initScore);
        
        bool stop = true;
        bool isFirst = true;
        
        int cellWidth = tableRowMargin * kSpaceSize;
        
        
        
        do
        {
            std::cout << "=*=*=*=*=*=*=*=*=*=*=*=*新一轮操作=*=*=*=*=*=*=*=*=*=*=*=*" << std::endl;
            if (maxStrWidht(toStrFunc) > cellWidth)
            {
                setmargin(tableRowMargin + 1, tableColumnMargin + 1);
            }
            
            std::function<void (T)> gameShow = [=](int i){
                
                std::string str = toStrFunc(i);
                
                int maxSpce = tableRowMargin * kSpaceSize;
                
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
                std::cout << "=*=*=*=*=*=*游戏结束=*=*=*=*=*=*" << std::endl;
                printGame(gameShow, toStrFunc);
                break;
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
                if (handleGame(c, validFunc, toStrFunc, mergeFunc, gameShow))
                {
                    break;
                }
                else
                {
                    usleep(1000000 * 2);
                }
                
            }while(true);
            
            printGame(gameShow, toStrFunc);
            
        }while(stop);
        
        
        
    }
    
    
private:
    
    bool handleGame(char c, std::function<bool (T)> validFunc, std::function<std::string (T)> toStrFunc, std::function<bool (T &, T&, T&, bool)> mergeFunc, std::function<void (T)> gameShow, bool print = false)
    {
        if (c == 'a')
        {
            // 左
            for (int i = 0; i < tableRow; i++)
            {
                // 合并
                {
                    int fromIndex = 0;
                    bool findfirst = false;
                    
                    for (int j = 0; j < tableColumn; j++)
                    {
                        if (print)
                            std::cout << "========>>>> 左合并" << std::endl;
                        int index =  i * tableColumn + j;
                        T v = *(tableContent + index);
                        if (validFunc(v))
                        {
                            if (findfirst)
                            {
                                bool succ = mergeFunc(*(tableContent + fromIndex), *(tableContent + index), gameScore, true);
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
                    for (int j = 0; j < tableColumn; j++)
                    {
                        if (print)
                            std::cout << "========>>>> 左平移" << std::endl;
                        int index =  i * tableColumn + j;
                        T v = *(tableContent + index);
                        
                        if (validFunc(v))
                        {
                            if (findFirst)
                            {
                                T temp;
                                mergeFunc(*(tableContent + fromIndex), *(tableContent + index), temp, false);
                                fromIndex = index;
                                findFirst = true;
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
            for (int i = 0; i < tableColumn; i++)
            {
                // 合并
                {
                    int fromIndex = 0;
                    bool findfirst = false;
                    
                    for (int j = 0; j < tableRow; j++)
                    {
                        if (print)
                            std::cout << "========>>>> 上合并" << std::endl;
                        int index =  j * tableColumn + i;
                        T v = *(tableContent + index);
                        if (validFunc(v))
                        {
                            if (findfirst)
                            {
                                bool succ = mergeFunc(*(tableContent + fromIndex), *(tableContent + index), gameScore, true);
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
                    for (int j = 0; j < tableRow; j++)
                    {
                        if (print)
                            std::cout << "========>>>> 上平移" << std::endl;
                        int index =  j * tableColumn + i;
                        T v = *(tableContent + index);
                        
                        if (validFunc(v))
                        {
                            if (findFirst)
                            {
                                T temp;
                                mergeFunc(*(tableContent + fromIndex), *(tableContent + index), temp, false);
                                fromIndex = index;
                                findFirst = true;
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
            for (int i = 0; i < tableRow; i++)
            {
                // 合并
                {
                    if (print)
                        std::cout << "========>>>> 右合并" << std::endl;
                    int fromIndex = 0;
                    bool findfirst = false;
                    
                    for (int j = tableColumn - 1; j >=0; j--)
                    {
                        int index =  i * tableColumn + j;
                        T v = *(tableContent + index);
                        if (validFunc(v))
                        {
                            if (findfirst)
                            {
                                bool succ = mergeFunc(*(tableContent + fromIndex), *(tableContent + index), gameScore, true);
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
                    for (int j = tableColumn - 1; j >=0; j--)
                    {
                        if (print)
                            std::cout << "========>>>> 右平移" << std::endl;
                        int index =  i * tableColumn + j;
                        T v = *(tableContent + index);
                        
                        if (validFunc(v))
                        {
                            if (findFirst)
                            {
                                T temp;
                                mergeFunc(*(tableContent + fromIndex), *(tableContent + index), temp, false);
                                
                                fromIndex = index;
                                findFirst = true;
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
            for (int i = 0; i < tableColumn; i++)
            {
                // 合并
                {
                    int fromIndex = 0;
                    bool findfirst = false;
                    
                    for (int j = tableRow - 1; j >= 0; j--)
                    {
                        if (print)
                            std::cout << "========>>>> 下合并" << std::endl;
                        int index =  j * tableColumn + i;
                        T v = *(tableContent + index);
                        if (validFunc(v))
                        {
                            if (findfirst)
                            {
                                bool succ = mergeFunc(*(tableContent + fromIndex), *(tableContent + index), gameScore, true);
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
                    for (int j = tableRow - 1; j >= 0; j--)
                    {
                        if (print)
                            std::cout << "========>>>> 下平移" << std::endl;
                        int index =  j * tableColumn + i;
                        T v = *(tableContent + index);
                        
                        if (validFunc(v))
                        {
                            if (findFirst)
                            {
                                T temp;
                                mergeFunc(*(tableContent + fromIndex), *(tableContent + index), temp, false);
                                fromIndex = index;
                                findFirst = true;
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
                    std::cout << "[" << i / tableColumn << "][" <<  i % tableColumn << "]" << "    ";
                });
            }
            int size = (int)empty.size();
            
            if(size > 0)
            {
                int randIndex = empty[(int)abs(rand()%size)];
                bool isTw0 = abs(rand()%3);
                T value = genFunc(isTw0);
                
                std::cout << std::endl <<"在：" << "[" << randIndex / tableColumn << "][" <<  randIndex % tableColumn << "]生成:"<< toStrFunc(value) << std::endl;
                *(tableContent + randIndex) = value;
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
        for (int i = 0; i < tableSize; i++)
        {
            T ov = *(tableContent + i);
            bool isV = validFunc(ov);
            if (!isV)
            {
                indexvec.push_back(i);
            }
        }
    }
    
    bool genValue(int index, T v, std::function<bool (T)> validFunc)
    {
        if (index >= 0 && index < tableSize)
        {
            T ov = *(tableContent + index);
            bool isV = validFunc(ov);
            if (!isV)
            {
                *(tableContent + index) = v;
                return true;
            }
            
            return false;
            
        }
        return false;
    }
    
    
protected:
    
    void drawContent()
    {
        
    }
    void drawHorMar() const
    {
        int k = 0;
        while(k < tableRowMargin)
        {
            std::cout<<on[1];
            k++;
        }
    }
    void drawHorSpace() const
    {
        int k = 0;
        while(k < tableRowMargin)
        {
            std::cout<<space[1];
            k++;
        }
    }
    
    void drawSpaceVer() const
    {
        //输出顶部字符
        for (int i = 0; i < tableColumn + 1; i++)
        {
            if (i < tableColumn)
            {
                std::cout << space[0];
                drawHorSpace();
            }
            else
            {
                std::cout << space[0];
            }
        }
        std::cout << std::endl;
    }
    
    void drawContentRow(int row ,std::function<void (T)> func) const
    {
        //输出顶部字符
        for (int i = 0; i < tableColumn + 1; i++)
        {
            if (i < tableColumn)
            {
                std::cout << space[0];
                int index = row * tableColumn + i;
                func(*(tableContent + index));
            }
            else
            {
                std::cout << space[0];
            }
        }
        std::cout << std::endl;
    }
    
    void drawRow () const
    {
        for (int i = 0; i < tableColumn + 1; i++)
        {
            if (i == 0)
            {
                std::cout<< center[0];
                drawHorMar();
            }
            else if (i < tableColumn)
            {
                std::cout << center[2];
                drawHorMar();
            }
            else
            {
                std::cout << center[3];
            }
        }
        std::cout << std::endl;
    }
    
    void drawTop() const
    {
        //输出顶部字符
        for (int i = 0; i < tableColumn + 1; i++)
        {
            if (i == 0)
            {
                std::cout<< on[0];
                drawHorMar();
            }
            else if (i < tableColumn)
            {
                std::cout << on[2];
                drawHorMar();
            }
            else
            {
                std::cout << on[3];
            }
        }
        std::cout << std::endl;
    }
    
    void drawCenter(std::function<void (T)> func) const
    {
        for (int i = 0; i < tableRow; i++)
        {
            int vermargin = tableColumnMargin;
            if (vermargin > 1)
            {
                while(vermargin > 1)
                {
                    drawSpaceVer();
                    vermargin--;
                }
            }
            
            drawContentRow(i, func);
            
            if (i != tableRow - 1)
            {
                drawRow();
            }
        }
    }
    void drawBottom() const
    {
        for (int i = 0; i < tableColumn + 1; i++)
        {
            if (i == 0)
            {
                std::cout<< down[0];
                drawHorMar();
            }
            else if (i < tableColumn)
            {
                std::cout << down[2];
                drawHorMar();
            }
            else
            {
                std::cout << down[3];
            }
        }
        std::cout << std::endl;
    }
    
    
    
};

#endif /* ConstoleTable_hpp */
