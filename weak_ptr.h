//
// Created by zyz on 2022/4/25.
//

#ifndef SMARTPTR_WEAK_PTR_H
#define SMARTPTR_WEAK_PTR_H
#include "shared_ptr.h"
template<typename T>
class WeakPtr
{
public:
    WeakPtr() {};
    WeakPtr(const shared_ptr<T> &p) : ptr(p.get()){}
    ~WeakPtr(){}
    WeakPtr<T>& operator=(const WeakPtr &p){
        ptr = p.ptr;
        return *this;
    }
    T& operator*(){return *ptr;}
    T* operator->(){return ptr;}
    operator bool() {return ptr != nullptr;}
private:
    // weak point 只引用，不计数
    T *ptr;
};
#endif //SMARTPTR_WEAK_PTR_H
