#include <stdio.h>


#include <string>
#include <unordered_set>

#include "ConsoleTable.hpp"

#include "Game2048.hpp"

#include "EightCell.h"

int main()
{
//    std::hash<std::string> h;
//    size_t n = h("Just");
//    std::cout << n << std::endl;
//
//    n = h("Justa");
//    std::cout << n << std::endl;
//
//    n = h("Justb");
//    std::cout << n << std::endl;
//
//
//    std::unordered_set<int, std::hash<int> > c0;
//    c0.insert(10);
//    std::cout << *c0.find(3) << std::endl;
    
    
    TEightCell<int> cell;
    cell.randomGame(100);
    
//    cell.move(0);
//    cell.move(1);
//    cell.move(2);
//    cell.move(3);
    
    

//    ConsoleTable<int> table;
//    table.drawTable([](int i){
//        printf("%-3d", i);
//    });
//
//    table.resizeTable(3, 3,[](int i)->int{
//        if(i%3 == 0)
//        {
//            return 0;
//        }
//        else
//        {
//            return i;
//        }
//    });
//
//    table.drawTable([](int i){
//        if (i == 0)
//        {
//            printf("   ");
//        }
//        else
//        {
//            printf("%-3d", i);
//        }
//
//    });
//
//
//
//
//    ConsoleTable<int> table2(5,5);
//    table2.drawTable([](int i){
//        printf("%3d", i);
//    });
//
//    ConsoleTable<char> tablec(5,5);
//    tablec.setmargin(2, 2);
//    tablec.drawTable([](char i){
//        printf("%6d", i);
//    });
//    tablec.resizeTable(4, 1, [](int i)->char{
//        return 'a'+i;
//
//    });
//
//    tablec.setmargin(1, 1);
//    tablec.drawTable([](char i){
//        printf("  %c", i);
//    });
//
//    Game2048<int> game;
//    game.game2048Start([](int i)->int{
//        return 0;
//    }, []()->int{
//        return 0;
//    }, [](int v)->std::string{
//        if (v == 0)
//        {
//            return "";
//        }
//        return std::to_string(v);
//    }, [] (bool is2)->int {
//        return is2 ? 2 : 4;
//    }, [](int v)->bool{
//        return v > 0;
//    }, [](int &a, int &b, int& score, bool isScore)->bool{
//        if(isScore)
//        {
//            if (a == b)
//            {
//                a = a + b;
//                score += b;
//                b = 0;
//                return true;
//            }
//            return false;
//        }
//        else
//        {
//            a = b;
//            b = 0;
//            return true;
//        }
//    }, [](int a, int b)->bool{
//        return a == b;
//    });
   
    return 0;
}

//int main2()
//{
//    char *on[4] = { "┌", "─", "┬", "┐" };
//    char *center[4] = { "├", "─", "┼", "┤" };
//    char *down[4] = { "└", "─", "┴", "┘" };
//    char *space[2] = { "│", "  " };
//    int rows, lines;
//    int i, j, k;
//    //printf("%c",on[0]);
//    scanf("%d",&rows);
//    scanf("%d",&lines);
//
//    //输出顶部字符
//    for (i = 0; i < 2 * lines + 1; i++)
//    {
//        if (i == 0)
//            printf("%s",on[0]);
//        else if (i == 2 * lines)
//            printf("%s",on[3]);
//        else
//        {
//            if (i % 2 == 0)
//                printf("%s",on[2]);
//            else
//                printf("%s",on[1]);
//        }
//    }
//    printf("\n");
//
//    //输出中间字符
//    for (i = 0; i < 2 * rows - 1; i++)
//    {
//        if ((i + 1) % 2 == 0)
//        {
//            for (j = 0; j < 2 * lines + 1; j++)
//            {
//                if (j == 0)
//                    printf("%s",center[0]);
//                else if (j == 2 * lines)
//                    printf("%s",center[3]);
//                else
//                {
//                    if (j % 2 == 0)
//                        printf("%s",center[2]);
//                    else
//                        printf("%s",center[1]);
//                }
//            }
//        }
//        else
//        {
//            for (k = 0; k < 2 * lines + 1; k++)
//            {
//                if ((k + 1) % 2 == 0)
//                    printf("%s",space[1]);
//                else
//                    printf("%s",space[0]);
//            }
//        }
//        printf("\n");
//    }
//
//    //输出底部字符
//    for (i = 0; i < 2 * lines + 1; i++)
//    {
//        if (i == 0)
//            printf("%s",down[0]);
//        else if (i == 2 * lines)
//            printf("%s",down[3]);
//        else
//        {
//            if (i % 2 == 0)
//                printf("%s",down[2]);
//            else
//                printf("%s",down[1]);
//        }
//    }
//    printf("\n");
//
//    return 0;
//}

