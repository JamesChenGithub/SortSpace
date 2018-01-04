#include <stdio.h>
#include <string.h>

#include "ConstoleTable.hpp"

int main()
{
    ConsoleTable<int> table;
     ConsoleTable<int> table2(5,5);
    return 0;
}

int main2()
{
    char *on[4] = { "┌", "─", "┬", "┐" };
    char *center[4] = { "├", "─", "┼", "┤" };
    char *down[4] = { "└", "─", "┴", "┘" };
    char *space[2] = { "│", "  " };
    int rows, lines;
    int i, j, k;
    //printf("%c",on[0]);
    scanf("%d",&rows);
    scanf("%d",&lines);
    
    //输出顶部字符
    for (i = 0; i < 2 * lines + 1; i++)
    {
        if (i == 0)
            printf("%s",on[0]);
        else if (i == 2 * lines)
            printf("%s",on[3]);
        else
        {
            if (i % 2 == 0)
                printf("%s",on[2]);
            else
                printf("%s",on[1]);
        }
    }
    printf("\n");
    
    //输出中间字符
    for (i = 0; i < 2 * rows - 1; i++)
    {
        if ((i + 1) % 2 == 0)
        {
            for (j = 0; j < 2 * lines + 1; j++)
            {
                if (j == 0)
                    printf("%s",center[0]);
                else if (j == 2 * lines)
                    printf("%s",center[3]);
                else
                {
                    if (j % 2 == 0)
                        printf("%s",center[2]);
                    else
                        printf("%s",center[1]);
                }
            }
        }
        else
        {
            for (k = 0; k < 2 * lines + 1; k++)
            {
                if ((k + 1) % 2 == 0)
                    printf("%s",space[1]);
                else
                    printf("%s",space[0]);
            }
        }
        printf("\n");
    }
    
    //输出底部字符
    for (i = 0; i < 2 * lines + 1; i++)
    {
        if (i == 0)
            printf("%s",down[0]);
        else if (i == 2 * lines)
            printf("%s",down[3]);
        else
        {
            if (i % 2 == 0)
                printf("%s",down[2]);
            else
                printf("%s",down[1]);
        }
    }
    printf("\n");
    
    return 0;
}
