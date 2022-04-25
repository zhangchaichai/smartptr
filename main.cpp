#include <iostream>
#include "unique_ptr.h"
#include "shared_ptr.h"
class shape{
public:
    int x,y;
};
template<typename T>
void swap(unique_ptr<T> &lhs, unique_ptr<T> &rhs) {
    lhs.swap(rhs);
}

template<typename T>
void swap(shared_ptr<T> &lhs, shared_ptr<T> &rhs) noexcept {
    lhs.swap(rhs);
}
int main() {
    shape* a = new shape();
    shape c{};
    shape* b = new shape();
    unique_ptr<shape> ptr1{a};
//    unique_ptr<shape> ptr2{ptr1}; // error
    unique_ptr<shape> ptr2{std::move(ptr1)};    // ok

    unique_ptr<shape> ptr3{b};
//    ptr1 = ptr3;    // error
    ptr3 = std::move(ptr1); // ok
}