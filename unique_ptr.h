//
// Created by zyz on 2022/4/25.
//

#ifndef SMARTPTR_UNIQUE_PTR_H
#define SMARTPTR_UNIQUE_PTR_H

#include <algorithm>

template<typename T>
class unique_ptr {
public:
    explicit unique_ptr(T *ptr = nullptr) noexcept: ptr_(ptr) {}
    ~unique_ptr() noexcept {
        delete ptr_;
    }

    T &operator*() const noexcept { return *ptr_; }

    T *operator->() const noexcept { return ptr_; }

    operator bool() const noexcept { return ptr_; }

    T *get() const noexcept { return ptr_; }

    unique_ptr(unique_ptr &&other) noexcept {
        ptr_ = other.release();
    }

    // copy and swap  始终只有一个对象有管理这块空间的权限
    unique_ptr &operator=(unique_ptr rhs) noexcept {
        rhs.swap(*this);
        return *this;
    }

    // 原来的指针释放所有权
    T *release() noexcept {
        T *ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    void swap(unique_ptr &rhs) noexcept {
        using std::swap;
        swap(ptr_, rhs.ptr_);    // 转移指针所有权
    }

private:
    T *ptr_;
};
#endif //SMARTPTR_UNIQUE_PTR_H
