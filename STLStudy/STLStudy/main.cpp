//
//  main.m
//  STLStudy
//
//  Created by AlexiChen on 2018/1/18.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#include "STLAlloctor.hpp"

#include <vector>
#include <iostream>

int main()
{
    int a[5] = {0,1,2,3,4};
    
    
    
    std::vector<int, STLStudy::STLAlloctor<int>> iv(a, a+5);
    for (unsigned int i = 0; i < iv.size(); i++) {
        std::cout << iv[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}
