//
//  ConsoleTable.hpp
//  Console
//
//  Created by AlexiChen on 2018/1/4.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef ConsoleTable_hpp
#define ConsoleTable_hpp

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
protected:
    unsigned int tableRow = 4;
    unsigned int tableColumn = 4;
    unsigned int tableRowMargin = 1;
    unsigned int tableColumnMargin = 1;
    
protected:
    const char *on[4] = { "┌", kHor, "┬", "┐" };
    const char *center[4] = { "├", kHor, "┼", "┤" };
    const char *down[4] = { "└", kHor, "┴", "┘" };
    const char *space[2] = { "│", kSpace };
    
protected:
    T *tableContent = nullptr;
    unsigned int tableSize = tableRow * tableColumn;
    
    unsigned int kMaxLenth = 2;
    
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
    
    void drawTable2(std::function<std::string (T)> toStrFunc = [](T v)->std::string{
        return std::to_string(v);
    })
    {
        int maxSpce = tableRowMargin * kSpaceSize;
       
        drawTable([&](T value) {
            std::string str = toStrFunc(value);
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
        });
        
    }
    
    void setmargin(unsigned int h, unsigned int v)
    {
        tableRowMargin = h;
        tableColumnMargin = v;
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



#endif /* ConsoleTable_hpp */
