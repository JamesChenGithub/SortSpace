//
//  Student.hpp
//  STLStudy
//
//  Created by AlexiChen on 2018/1/23.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef Student_hpp
#define Student_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>

struct Student
{
    std::string mName;
    int mScore;
    bool sex;
    
    Student& operator= (Student s)
    {
        this->mName = s.mName;
        this->mScore = s.mScore;
        this->sex = s.sex;
        
        return *this;
    }
    
    
    bool operator <(const Student &a)
    {
        return this->mName < a.mName;
    }
    
    bool operator >(const Student &a)
    {
        return this->mName > a.mName;
    }
    
    bool operator==(const Student &s)
    {
        return this->mName == s.mName;
    }
    
    

    std::string toString() const
    {
        std::ostringstream os;
        os << "姓名："  << this->mName << "    性别：" << (this->sex ? "男" : "女") << "    分数：" << this->mScore << std::endl;
        return os.str();
    }
    
};




//Student & operator= (Student &a, const Student& s)
//{
//    a.mName = s.mName;
//    a.mScore = s.mScore;
//    a.sex = s.sex;
//
//    return a;
//}

bool operator <(const Student &a, const Student& b)
{
    return a.mName < b.mName;
}


struct StudentDisplay
{
    friend struct Student;
    void operator() (const Student& s) const
    {
        std::cout << "姓名："  << s.mName << "    性别：" << (s.sex ? "男" : "女") << "    分数：" << s.mScore << std::endl;
    }
};

//class even_two1 {
//public:
//    int operator() () const
//    {
//        return _x += 2;
//    }
//private:
//    static int _x;
//};
//int even_two1::_x = 0;

class StudentGenerator
{
public:
    Student operator() () const
    {
        return genStu();
    }
    Student genStu() const
    {
        //        srand(time(0));
        Student s;
        
        char namePre[5] = "";
        int i = 0;
        while ( i < 4)
        {
            namePre[i++] = 'a' + rand()%26;
        }
        namePre[4] = '\0';
        s.mName = namePre + std::to_string(rand()%100000);
        s.mScore = rand()%100;
        s.sex = rand()%2;
        return s;
    }
};

class STClass
{
    
private:
    std::set<Student> mStudentSet;
    std::vector<Student> mStudentVector;
    
public:
    void generate(int size = 50)
    {
        generateVector(size);
    }
    
    void display() const
    {
        displayVector();
    }
    
    void sortByName()
    {
        sortByNameVector();
    }
    
   
    
    
private:
    void generateSet(int size)
    {
//        mStudentSet.clear();
//        std::generate_n(mStudentSet.begin(), size, StudentGenerator());
    }
    
private:
    void generateVector(int size)
    {
        mStudentVector.clear();
        mStudentVector.resize(size);
        
        std::generate(mStudentVector.begin(), mStudentVector.end(), StudentGenerator());
    }
    
    void displayVector() const
    {
        std::for_each(mStudentVector.begin(), mStudentVector.end(), StudentDisplay());
    }
    
    void sortByNameVector() 
    {
        
        std::cout << "===========按名称排序==========" << std::endl;
        std::sort(mStudentVector.begin(), mStudentVector.end());
        
        displayVector();
        
        std::cout << "===========按分数排序==========" << std::endl;
        std::sort(mStudentVector.begin(), mStudentVector.end(), [](Student s1, Student s2)->bool{
            return s1.mScore > s2.mScore;
        });
        
        displayVector();
        
        std::cout << "===========按性别排序==========" << std::endl;
        std::sort(mStudentVector.begin(), mStudentVector.end(), [](Student s1, Student s2)->bool{
            if (s1.sex < s2.sex)
            {
                return true;
            }
            else
            {
                return s1.mScore > s2.mScore;
            }
        });
        displayVector();
        std::cout << "===========找出分数大于60分的同学==========" << std::endl;
        auto grades = std::find_if(mStudentVector.begin(), mStudentVector.end(), [](Student s)->bool{
            return s.mScore > 60;
        });
        
        std::cout << grades->toString() << std::endl;
    
        
        std::cout << std::count_if(mStudentVector.begin(), mStudentVector.end(), [](Student s)->bool{
            return s.mScore > 60;
        }) << std::endl;
        
        
        
        
    }
    
    
    void sortBySexVector()
    {
        
    }
    
    
};

#endif /* Student_hpp */
