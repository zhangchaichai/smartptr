//
// Created by zyz on 2022/4/25.
//

#ifndef SMARTPTR_SHARED_PTR_H
#define SMARTPTR_SHARED_PTR_H

class shared_count {
public:
    shared_count() : count_(1) {}
    // 增加计数
    void add_count() {
        ++count_;
    }
    // 减少计数
    long reduce_count() {
        return --count_;
    }
    // 获取当前计数
    long get_count() const {
        return count_;
    }
private:
    long count_;
};
template<typename T>
class shared_ptr {
public:
    template<typename U>
    friend class shared_ptr;
    explicit shared_ptr(T *ptr = nullptr) noexcept: ptr_(ptr) {
        if (ptr) {
            shared_count_ = new shared_count();
        }
    }
    ~shared_ptr() noexcept {
        // 最后一个shared_ptr再去删除对象与共享计数
        // ptr_不为空且此时共享计数减为0的时候,再去删除
        if(ptr_&&!shared_count_->reduce_count()) {
            delete ptr_;
            delete shared_count_;
        }
    }
    void swap(shared_ptr &rhs) noexcept {
        using std::swap;
        swap(ptr_, rhs.ptr_);
        swap(shared_count_,rhs.shared_count_);
    }
    shared_ptr &operator=(shared_ptr rhs) noexcept {
        rhs.swap(*this);
        return *this;
    }
    template<typename U>
    shared_ptr(const shared_ptr<U> &other) noexcept {
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }
    template<typename U>
    shared_ptr(shared_ptr<U> &&other) noexcept {
        ptr_ = other.ptr_;
        if (ptr_) {
            shared_count_ = other.shared_count_;
            other.shared_count_ = nullptr;
        }
    }
    long use_count() const noexcept {
        if (ptr_) {
            return shared_count_->get_count();
        } else {
            return 0;
        }
    }
private:
    T *ptr_;
    shared_count *shared_count_;
};
#endif //SMARTPTR_SHARED_PTR_H
