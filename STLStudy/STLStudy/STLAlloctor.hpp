//
//  STLAlloctor.hpp
//  STLStudy
//
//  Created by AlexiChen on 2018/1/18.
//  Copyright © 2018年 AlexiChen. All rights reserved.
//

#ifndef STLAlloctor_hpp
#define STLAlloctor_hpp

#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

namespace STLStudy {
    
    template<class T>
    inline T* _allocate(ptrdiff_t size, T*)
    {
        std::set_new_handler(0);
        T *temp = (T *)(::operator new((size_t)(sizeof(T) * size)));
        if (temp == nullptr)
        {
            std::cerr << "out of memory" << std::endl;
            exit(1);
        }
        
        return temp;
    }
    
    template<class T>
    inline void _deallocate(T *buffer)
    {
        ::operator delete(buffer);
    }
    
    template<class T>
    inline void _construct(T *p, const T& value)
    {
        new(p) T(value);
    }
    
    template<class T>
    inline void _destory(T *ptr)
    {
        ptr->~T();
    }
    
    template<class T>
    class STLAlloctor
    {
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;
        
        template<class U>
        struct rebind
        {
            typedef STLAlloctor<U> other;
        };
        
        
        pointer allocate(size_type n, const void *hint = 0)
        {
            return _allocate((difference_type)n, (pointer)hint);
        }
        
        
        void deallocate(pointer p, size_type n)
        {
            _deallocate(p);
        }
        
        
        void destory(pointer p)
        {
            _destory(p);
        }
        
        pointer address(reference x)
        {
            return (pointer)&x;
        }
        
        const_pointer const_address(const_reference x)
        {
            return (const_pointer)&x;
        }
        
        size_type max_size() const
        {
            return size_type(UINT_MAX/sizeof(T));
        }
        
    };
    
}


#endif /* STLAlloctor_hpp */
