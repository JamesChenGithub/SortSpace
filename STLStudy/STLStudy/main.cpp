//
//  main.m
//  STLStudy
//
//  Created by AlexiChen on 2018/1/18.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

//#include "STLAlloctor.hpp"

#include <vector>
#include <iostream>
#include <map>
#include <list>
#include <queue>
#include <vector>
#include <queue>
#include <numeric>
#include <functional>

#include <iterator>
#include <set>


#include "Student.hpp"



template<class T>
struct DisableCompare : public std::binary_function<T,T,bool>
{
    bool operator()(T lhs,T rhs)  const
    {
        return true;
    }
};

template<class T>
struct display
{
    void operator ()(const T &x) const
    {
        std::cout << x << "  ";
    }

};

struct even{
    bool operator()(int x){
        return x%2 ? false : true;
    }
};

class even_two {
public:
    int operator() () const
    {
        return _x += 2;
    }
private:
    static int _x;
};
int even_two::_x = 0;

int main()
{
    {
        STClass stc;
        stc.generate();
        stc.display();
        
        stc.sortByName();
        
//        std::set<Student> classset;
//        StudentGenerator sg;
//        StudentDisplay sd;
//        
//        Student s1 = sg();
//        sd(s1);
//    
//        Student s2 = s1;
//        sd(s2);
//        
//        classset.insert(sg());
//        
//        std::for_each(classset.begin(), classset.end(), [=](Student s){
//            sd(s);
//        });
//        std::generate_n(classset.begin(), 3, StudentGenerator());
//
//        std::generate_n(classset.begin(), 1, []()->Student{
//            Student s;
//            return s;
//        });
        
//        std::for_each(classset.begin(), classset.end(), StudentDisplay());
        
        
    }
    return 0;
    {
        int a[5] = {0,1,2,3,4};
        std::map<char, int, DisableCompare<char>> cimap;
        cimap['b'] = 1;
        cimap['a'] = 1;
        
        std::for_each(cimap.begin(), cimap.end(), [](std::pair<char, int> pair){
            std::cout << pair.first  << "   " << pair.second << std::endl;
        });
        
    }
    
    {
        std::multimap<char, int> cimap;
        
        cimap.insert({'c', 1});
        cimap.insert({'b', 1});
        cimap.insert({'a', 1});
        
        std::for_each(cimap.begin(), cimap.end(), [](std::pair<char, int> pair){
            std::cout << pair.first  << "   " << pair.second << std::endl;
        });
    }
    
    //    std::array<int, 10> arr = {0,1,1,1,1,0,1,1,1,1};
    //    std::for_each(std::begin(arr), std::end(arr), [&](int i){
    //        arr[i] = i;
    //    });
    
    {
        std::vector<int> vec = std::vector<int>{1,2,3,4,5,6,7};
        vec.emplace_back(1);
        vec.push_back(2);
        
        std::vector<int> vec2 ;
        vec.swap(vec2);
        
        std::cout << vec.capacity() << std::endl;
        std::cout << vec.size() << std::endl;
        
        vec.emplace_back(12);
        std::for_each(vec.begin(), vec.end(), [](int i){
            std::cout << i  << "   " ;
        });
        
        std::cout << std::endl;
        
        std::cout << std::endl;
        vec2.erase(vec2.begin() + 4);
        std::for_each(vec2.begin(), vec2.end(), [](int i){
            std::cout << i  << "   " ;
        });
        std::cout << std::endl;
        
        auto it = std::find(vec2.begin(), vec2.end(), 3);
        std::cout << *it  << std::endl;
        
        
        vec2.pop_back();
        std::for_each(vec2.begin(), vec2.end(), [](int i){
            std::cout << i  << "   " ;
        });
        std::cout << std::endl;
        vec2.front();
        std::for_each(vec2.begin(), vec2.end(), [](int i){
            std::cout << i  << "   " ;
        });
        std::cout << std::endl;
        vec2.back();
        std::for_each(vec2.begin(), vec2.end(), [](int i){
            std::cout << i  << "   " ;
        });
        std::cout << std::endl;
        auto cit = vec2.rbegin();
        std::cout << *cit  << std::endl;
        
        std::cout << *(vec2.rend())  << std::endl;
        
        auto it2 = std::find(vec2.begin(), vec2.end(), 10);
        std::cout << *it  << std::endl;
        
        std::cout << std::endl;
        
        
    }
    
    {
        std::list<int> list;
        list.push_back(1);
        list.push_front(2);
        list.push_back(3);
        list.push_front(4);
        list.push_back(5);
        list.push_front(6);
        list.push_back(1);
        list.push_front(2);
        list.push_back(1);
        list.push_front(2);
        list.push_back(1);
        list.push_front(2);
        std::for_each(list.begin(), list.end(), [](int i){
            std::cout << i  << "   " ;
        });
        std::cout << std::endl;
        
        list.unique([](int a, int b)->bool{
            return a == b;
        });
        
        std::for_each(list.begin(), list.end(), [](int i){
            std::cout << i  << "  --  " ;
        });
        std::cout << std::endl;
        list.unique();
        std::for_each(list.begin(), list.end(), [](int i){
            std::cout << i  << "   " ;
        });
        std::cout << std::endl;
    }
    
    {
        int arr[5] = {5,6,7,8,9};
        std::list<int> list = {arr, arr+5};
        std::for_each(list.begin(), list.end(), [](int i){
            std::cout << i  << "   " ;
        });
        std::cout << std::endl;
        auto it = std::find(list.begin(), list.end(), 7);
        std::list<int> al;
        list.splice(it, al);
        
        list.reverse();
        std::for_each(list.begin(), list.end(), [](int i){
            std::cout << i  << "   " ;
        });
        std::cout << std::endl;
        
        std::for_each(al.begin(), al.end(), [](int i){
            std::cout << i  << "   " ;
        });
        std::cout << std::endl;
        
        
    }
    
    
    {
        std::queue<int> queue;
        queue.push(1);
        queue.push(2);
        queue.push(3);
        queue.push(4);
        
        queue.front();
        queue.pop();
    }
    
    {
        
        int a[9] = {5,8,9,6,7,4,3,2,1};
        std::vector<int> vec(a, a+9);
        
        auto func = [](int a, int b)->bool{
            return a > b;
        };
        
        std::make_heap(vec.begin(), vec.end(), func);
        
        std::for_each(vec.begin(), vec.end(), [](int i){
            std::cout << i <<"  ";
        });
        std::cout << std::endl;
        
        vec.push_back(10);
        
        std::push_heap(vec.begin(), vec.end(), func);
        
        std::for_each(vec.begin(), vec.end(), [](int i){
            std::cout << i <<"  ";
        });
        std::cout << std::endl;
        
        std::pop_heap(vec.begin(), vec.end(), func);
        vec.pop_back();
        std::for_each(vec.begin(), vec.end(), [](int i){
            std::cout << i <<"  ";
        });
        std::cout << std::endl;
        
    }
    
    {
        
        int a[9] = {5,8,9,6,7,4,3,2,1};
        std::make_heap(a, a+9);
        std::sort_heap(a, a+9);
        std::for_each(std::begin(a), std::end(a), [](int i){
            std::cout << i <<"  ";
        });
        std::cout << std::endl;
    }
    
    {
        int a[9] = {0,1,2,3,4,8,9,5,3};
        std::priority_queue<int> ipq(a, a+9);
//        ipq.push(100);
        
        while (!ipq.empty()) {
            std::cout << ipq.top() << "   ";
            ipq.pop();
        }
        
        std::cout << std::endl;
    }
    
//    {
//        //    std::vector<int, std::allocator<int>>
//        int a[5] = {0,1,2,3,4};
//        std::vector<int, STLStudy::STLAlloctor<int>> iv(a, a+5);
//        for (unsigned int i = 0; i < iv.size(); i++) {
//            std::cout << iv[i] << ' ';
//        }
//        std::cout << std::endl;
//    }
    
    {
        int a[9] = {1,3,5,7,9,2,4,6,8};
        int sum = 0;
        
        sum = std::accumulate(a, a+9, 100);
        std::cout << sum << std::endl;
        
        std::cout << std::inner_product(a, a+9, a, 0) << std::endl;
        
        sum = 0;
        std::for_each(std::begin(a), std::end(a), [&](int i){
            sum += i * i;
        });
        std::cout << sum << std::endl;
        
        
        std::cout << std::inner_product(a, a+9, a, 0, std::minus<int>(), std::plus<int>()) << std::endl;
        
        std::ostream_iterator<int> oite(std::cout, "  ");
        
        std::partial_sum(a, a+9, oite);
        std::cout << std::endl;
        
        std::partial_sum(a, a+9, oite, std::minus<int>());
        std::cout << std::endl;
        
        std::adjacent_difference(a, a+9, oite);
        std::cout << std::endl;
        
        std::adjacent_difference(a, a+9, oite, std::plus<int>());
        std::cout << std::endl;
        
        std::adjacent_difference(a, a+9, oite, std::minus<int>());
        std::cout << std::endl;
        
        std::for_each(std::begin(a), std::end(a), [](int i){
            std::cout << i << " ";
        });
        std::cout << std::endl;
    }
    
    {
        int a[] = {0,1,2,3,4,5,6,6,6,7,8};
        std::vector<int> vec(a, a+sizeof(a)/sizeof(int));
        std::cout << *std::adjacent_find(vec.begin(), vec.end()) << std::endl;
        
        std::cout << *std::adjacent_find(vec.begin(), vec.end(), std::equal_to<int>()) << std::endl;
        
        std::cout << std::count(vec.begin(), vec.end(), 6) << std::endl;
        std::cout << std::count_if(vec.begin(), vec.end(), std::bind2nd(std::less<int>(), 7)) << std::endl;
        
        std::cout << *std::find(vec.begin(), vec.end(), 4) << std::endl;
        
        std::cout << *std::find_if(vec.begin(), vec.end(), std::bind2nd(std::greater<int>(), 2)) << std::endl;
        
        std::vector<int> vc2(a+6, a+8);
        std::cout << *(std::find_end(vec.begin(), vec.end(), vc2.begin(), vc2.end()) + 3) << std::endl;
        std::cout << *(std::find_first_of(vec.begin(), vec.end(), vc2.begin(), vc2.end()) + 3) << std::endl;
        
        std::for_each(vec.begin(), vec.end(), display<int>());
        std::cout << std::endl;
        
        std::for_each(vc2.begin(), vc2.end(), display<int>());
        std::cout << std::endl;
        
        std::generate(vc2.begin(), vc2.end(), even_two());
        
        std::for_each(vc2.begin(), vc2.end(), display<int>());
        std::cout << std::endl;
        
        std::generate_n(vc2.begin(), 3, even_two());
        std::for_each(vc2.begin(), vc2.end(), display<int>());
        std::cout << std::endl;
        
        std::remove(vec.begin(), vec.end(), 6);
        std::for_each(vec.begin(), vec.end(), display<int>());
        std::cout << std::endl;
        
        std::replace(vec.begin(), vec.end(), 7, 9);
        std::replace(vec.begin(), vec.end(), 8, 9);
        std::for_each(vec.begin(), vec.end(), display<int>());
        std::cout << std::endl;
        
        
    }
    
    
    {
        std::cout << "================" << std::endl;
        int a[9] = {0,1,2,3,4,5,6,7,8};
        std::vector<int> iv1(a, a+5);
        std::vector<int> iv2(a, a+9);
        std::vector<int> iv3(a, a+9);
        
        auto it = std::mismatch(iv1.begin(), iv1.end(), iv2.begin());
        std::cout << *it.first << std::endl;
        std::cout << *it.second << std::endl;
        
        std::cout << std::equal(iv1.begin(), iv1.end(), iv2.begin()) << std::endl;
        std::cout << std::equal(iv1.begin(), iv1.end(), iv3.begin()) << std::endl;
        
        
        std::cout << std::equal(iv1.begin(), iv1.end(), &a[4], std::less<int>()) << std::endl;
        std::cout << std::equal(iv2.begin(), iv2.end(), &a[5], std::greater<int>()) << std::endl;
        
        
        std::fill(iv3.begin(), iv3.end(), 9);
        
        std::for_each(iv3.begin(), iv3.end(), display<int>());
        std::cout << std::endl;
        
        
        std::fill_n(iv3.begin(), 3, 6);
        std::for_each(iv3.begin(), iv3.end(), display<int>());
        std::cout << std::endl;
        
        std::fill_n(iv3.end() , 3, 6);
        std::for_each(iv3.begin(), iv3.end(), display<int>());
        std::cout << std::endl;
        
        std::vector<int>::iterator it1 = iv3.begin();
        std::vector<int>::iterator it2 = iv3.end() - 1;
        
        std::advance(it1, 2);
        
        
        
        std::iter_swap(it1, it2);
        
        std::cout << std::max(*it1, *it2) << std::endl;
        
        std::for_each(iv3.begin(), iv3.end(), display<int>());
        std::cout << std::endl;
        
    }
    
    {
        int a[] = {1,1,1,2,3,4,4,4,5,5};
        std::vector<int> vec(a, a+sizeof(a)/sizeof(int));
        
        
        
        auto restult = std::unique(std::begin(vec), std::end(vec));
        vec.resize(std::distance(vec.begin(), restult));
        
        std::for_each(vec.begin(), vec.end(), display<int>());
        std::cout << std::endl;
    }
    
    {
        int a[] = {1,1,7,8,9,6,2,3,4,5,1,2,3,4,4,4,5,5};
        std::vector<int> vec(a, a+sizeof(a)/sizeof(int));
        
        
        std::sort(vec.begin(), vec.end(), [](int a, int b)->bool{
            return a < b;
        });
        std::for_each(vec.begin(), vec.end(), display<int>());
        std::cout << std::endl;
        
        auto restult = std::unique(std::begin(vec), std::end(vec));
        
        std::vector<int>::difference_type type = std::distance(vec.begin(), restult);
        vec.resize(type);
        
        std::for_each(vec.begin(), vec.end(), display<int>());
        std::cout << std::endl;
        
        
    }
    
    {
        std::ostream_iterator<int> oi(std::cout, "  ");
        
        int a[] = {2,21,12,7,19,24};
        
        std::vector<int> vec(a, a + sizeof(a)/sizeof(int));
        
        std::for_each(vec.begin(), vec.end(), std::bind2nd(std::plus<int>(), 3));
        
        
    }
    return 0;
}
