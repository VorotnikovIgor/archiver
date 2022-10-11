#include <algorithm>
#include "vector.h"

Vector::Iterator Vector::Begin() {
    return Iterator(&data_[0]);
}

Vector::Iterator Vector::End() {
    return Iterator(&data_[size_]);
}

Vector::Iterator Vector::begin() {
    return Begin();
}

Vector::Iterator Vector::end() {
    return End();
}

Vector::Iterator::Iterator(Vector::ValueType* pointer) : ptr_(pointer) {
}

Vector::Iterator::Iterator() : ptr_(nullptr) {
}

Vector::ValueType& Vector::Iterator::operator*() const {
    return *ptr_;
}

Vector::ValueType* Vector::Iterator::operator->() const {
    return ptr_;
}

Vector::Iterator& Vector::Iterator::operator=(Vector::Iterator other) {
    ptr_ = other.ptr_;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator++() {
    ptr_++;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator copy = Iterator(ptr_);
    ptr_++;
    return copy;
}

Vector::Iterator& Vector::Iterator::operator--() {
    ptr_--;
    return *this;
}

Vector::Iterator Vector::Iterator::operator--(int) {
    Iterator copy = Iterator(ptr_);
    ptr_--;
    return copy;
}

Vector::Iterator Vector::Iterator::operator+(DifferenceType shift) {
    return Iterator(ptr_ + shift);
}

Vector::DifferenceType Vector::Iterator::operator-(Vector::Iterator other) {
    return ptr_ - other.ptr_;
}

Vector::Iterator& Vector::Iterator::operator+=(DifferenceType shift) {
    ptr_ += shift;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator-=(DifferenceType shift) {
    ptr_ -= shift;
    return *this;
}

bool Vector::Iterator::operator==(const Vector::Iterator& other) const {
    return other.ptr_ == ptr_;
}

bool Vector::Iterator::operator!=(const Vector::Iterator& other) const {
    return other.ptr_ != ptr_;
}

std::strong_ordering Vector::Iterator::operator<=>(const Vector::Iterator& other) const {
    DifferenceType dif = ptr_ - other.ptr_;
    return (dif <=> 0);
}

Vector::Vector() : capacity_(0), size_(0), data_(nullptr) {
}

Vector::Vector(size_t size) {
    size_ = size;
    capacity_ = size;
    data_ = new ValueType[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = 0;
    }
}

Vector::Vector(std::initializer_list<Vector::ValueType> list) {
    size_ = list.size();
    capacity_ = list.size();
    data_ = new ValueType[capacity_];
    size_t i = 0;
    for (const auto& elem : list) {
        data_[i] = elem;
        ++i;
    }
}

Vector::Vector(const Vector& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new ValueType[capacity_];
    for (size_t i = 0; i < other.Size(); ++i) {
        data_[i] = other.data_[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new ValueType[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
    return *this;
}

Vector::~Vector() {
    delete[] data_;
}

Vector::SizeType Vector::Size() const {
    return size_;
}

Vector::SizeType Vector::Capacity() const {
    return capacity_;
}

const Vector::ValueType* Vector::Data() const {
    return data_;
}

Vector::ValueType& Vector::operator[](size_t position) {
    return data_[position];
}

Vector::ValueType Vector::operator[](size_t position) const {
    return data_[position];
}

bool Vector::operator==(const Vector& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& other) const {
    if (size_ != other.size_) {
        return true;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return true;
        }
    }
    return false;
}

std::strong_ordering Vector::operator<=>(const Vector& other) const {
    for (size_t i = 0; i < std::min(size_, other.size_); ++i) {
        if (data_[i] != other.data_[i]) {
            return (data_[i] <=> other.data_[i]);
        }
    }
    return size_ <=> other.size_;
}

void Vector::Reserve(Vector::SizeType new_capacity) {
    if (new_capacity > capacity_) {
        capacity_ = new_capacity;
        ValueType* data_new = new ValueType[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_new[i] = data_[i];
        }
        delete data_;
        data_ = data_new;
    }
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::PushBack(const ValueType& new_element) {
    if (size_ == capacity_) {
        capacity_ = std::max(static_cast<size_t>(1), static_cast<size_t>(2) * capacity_);
        ValueType* data_new = new ValueType[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_new[i] = data_[i];
        }
        delete data_;
        data_ = data_new;
    }
    size_ += 1;
    data_[size_ - 1] = new_element;
}

void Vector::PopBack() {
    size_ -= 1;
}

void Vector::Swap(Vector& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}