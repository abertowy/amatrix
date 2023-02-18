// amatrix.h - Contains declarations of amatrix class
#pragma once

#include <cstring>
#include <algorithm>
#include <initializer_list>
#include <iostream>

namespace amatrix {
    template <class T>
    class AMatrix {
    public:
        AMatrix();
        AMatrix(std::size_t size1, std::size_t size2);
        AMatrix(std::size_t size1, std::size_t size2, T val);
        AMatrix(std::initializer_list <T> list, std::size_t size1 = 1);
        AMatrix(std::size_t size1, std::size_t size2, std::initializer_list <T> list);
        AMatrix(const AMatrix& other) noexcept;
        AMatrix& operator=(const AMatrix& other) noexcept;
        AMatrix(AMatrix&& other) noexcept;
        AMatrix& operator=(AMatrix&& other) noexcept;
        void swap(AMatrix& other);
        ~AMatrix();

        std::size_t size1() const;
        std::size_t size2() const;

        const T* data() const;
        T* data();

        const T& operator () (std::size_t i) const;
        T& operator () (std::size_t i);
        const T& operator () (std::size_t i, std::size_t j) const;
        T& operator () (std::size_t i, std::size_t j);

        inline AMatrix operator+(const AMatrix& other) const;
        inline AMatrix operator-(const AMatrix& other) const;
        inline AMatrix operator*(const AMatrix& other) const;
        //AMatrix operator/(const AMatrix& other) const;
        inline AMatrix& operator+=(const AMatrix& other);
        inline AMatrix& operator-=(const AMatrix& other);
        inline AMatrix& operator*=(const AMatrix& other);
        //AMatrix& operator/=(const AMatrix& other);

        inline AMatrix operator++(int);
        inline AMatrix& operator++();
        inline AMatrix operator--(int);
        inline AMatrix& operator--();

        inline AMatrix operator+(T&& val) const;
        inline AMatrix operator-(T&& val) const;
        inline AMatrix operator*(T&& val) const;

    private:
        std::size_t size1_{ 0 }; // rows
        std::size_t size2_{ 0 }; // columns
        T* data_{ nullptr };
    };

    template <typename T>
    AMatrix<T>::AMatrix() : size1_(0), size2_(0), data_(nullptr) {}

    template <typename T>
    AMatrix<T>::AMatrix(std::size_t size1, std::size_t size2): size1_(size1), size2_(size2), data_(new T[size1 * size2]{}) {}


    template <class T>
    AMatrix<T>::AMatrix(std::size_t size1, std::size_t size2, T val) : size1_(size1), size2_(size2), data_(new T[size1 * size2]{}) {
        for (std::size_t i = 0; i < size1_ * size2_; ++i) {
            data_[i] = val;
        }
    }

    template <class T>
    AMatrix<T>::AMatrix(std::initializer_list <T> list, std::size_t size1) : AMatrix(size1, list.size())
    {
        int count{ 0 };
        for (auto element : list) {
            for (size_t i = 0; i < size1_; ++i) {
                data_[count + i * size2_] = element;
            }
            ++count;
        }
    }
    template <class T>
    AMatrix<T>::AMatrix(std::size_t size1, std::size_t size2, std::initializer_list <T> list) : AMatrix()
    {
        if (size1 * size2 == list.size()) {
            size1_ = size1;
            size2_ = size2;
            data_ = new T[size1 * size2]{};
            int count{ 0 };
            for (auto& element : list) {
                data_[count++] = element;
            }
        }
    }
    template <class T>
    AMatrix<T>::AMatrix(const AMatrix& other) noexcept : size1_(other.size1_), size2_(other.size2_), data_(new T[other.size1_ * other.size2_])
    {
        std::copy_n(other.data_, other.size1_ * other.size2_, data_);
    }
    template <class T>
    AMatrix<T>& AMatrix<T>::operator=(const AMatrix& other) noexcept
    {
        if (this != &other) {
            delete[] data_;
            size1_ = other.size1_;
            size2_ = other.size2_;
            data_ = new T[other.size1_ * other.size2_];
            std::copy_n(other.data_, other.size1_ * other.size2_, data_);
        }
        return *this;
    }
    template <class T>
    AMatrix<T>::AMatrix(AMatrix&& other) noexcept : size1_(std::move(other.size1_)), size2_(std::move(other.size2_)), data_(std::move(other.data_))
    {
        std::cout << "MOVE CTOR\n";
        other.size1_ = 0;
        other.size2_ = 0;
        other.data_ = nullptr;
        //std::memcpy(static_cast<void*>(this), static_cast<void*>(&other), sizeof(AMatrix));
    }
    template <class T>
    AMatrix<T>& AMatrix<T>::operator=(AMatrix&& other) noexcept
    {
        std::cout << "MOVE OPERATOR\n";
        AMatrix::swap(other);
        other.size1_ = 0;
        other.size2_ = 0;
        other.data_ = nullptr;
        return *this;
        //std::memcpy(static_cast<void*>(this), static_cast<void*>(&other), sizeof(AMatrix)); return *this;
    }
    template <class T>
    void AMatrix<T>::swap(AMatrix& other)
    {
        std::swap(size1_, other.size1_);
        std::swap(size2_, other.size2_);
        std::swap(data_, other.data_);
    }
    template <class T>
    AMatrix<T>::~AMatrix()
    {
        delete[] data_;
    }
    template <class T>
    std::size_t AMatrix<T>::size1() const { return size1_; }
    template <class T>
    std::size_t AMatrix<T>::size2() const { return size2_; }
    template <class T>
    const T* AMatrix<T>::data() const { return data_; }
    template <class T>
    T* AMatrix<T>::data() { return data_; }
    template <class T>
    const T& AMatrix<T>::operator () (std::size_t i) const {
        if (i < size1_ * size2_)
            return data()[i];
        throw std::out_of_range("index is out of the range");
    }
    template <class T>
    T& AMatrix<T>::operator () (std::size_t i) { 
        if (i < size1_*size2_)
            return data()[i]; 
        throw std::out_of_range("index is out of the range");
    }
    template <class T>
    const T& AMatrix<T>::operator () (std::size_t i, std::size_t j) const {
        if (i < size1_ && j < size2_)
            return data_[i * size2_ + j];
        throw std::out_of_range("index is out of the range");
    }
    template <class T>
    T& AMatrix<T>::operator () (std::size_t i, size_t j) {
        if (i < size1_ && j < size2_)
            return data_[i * size2_ + j];
        throw std::out_of_range("index is out of the range");
    }
    template <class T>
    AMatrix<T> AMatrix<T>::operator+(const AMatrix& other) const {
        if (size1_*size2_ != other.size1_ * other.size2_)
            throw std::out_of_range("index is out of the range");
        AMatrix<T> res(*this);
        for (std::size_t i = 0; i < size1_ * size2_; ++i)
            res.data_[i] += other.data_[i];
        return res;
    }
    template <class T>
    AMatrix<T> AMatrix<T>::operator-(const AMatrix& other) const {
        if (size1_ * size2_ != other.size1_ * other.size2_)
            throw std::out_of_range("index is out of the range");
        AMatrix<T> res(*this);
        for (std::size_t i = 0; i < size1_ * size2_; ++i)
            res.data_[i] -= other.data_[i];
        return res;
    }
    template <class T>
    AMatrix<T> AMatrix<T>::operator*(const AMatrix& other) const {
        if (size1_ * size2_ != other.size1_ * other.size2_)
            throw std::out_of_range("index is out of the range");
        AMatrix<T> res(size1_, other.size2_, 0);
        for (std::size_t i = 0; i < size1_; ++i) {
            for (std::size_t k = 0; k < other.size2_; ++k) {
                for (std::size_t j = 0; j < other.size1_; ++j) {
                    res.data_[k + i*other.size2_] += data_[j + i*size2_] * other.data_[k + j*other.size2_];
                }
            }
        }
        return res;
    }
    template <class T>
    AMatrix<T>& AMatrix<T>::operator+=(const AMatrix& other) {
        if (size1_ * size2_ != other.size1_ * other.size2_)
            throw std::out_of_range("index is out of the range");
        for (std::size_t i = 0; i < size1_ * size2_; ++i)
            data_[i] += other.data_[i];
        return *this;
    }
    template <class T>
    AMatrix<T>& AMatrix<T>::operator-=(const AMatrix& other) {
        if (size1_ * size2_ != other.size1_ * other.size2_)
            throw std::out_of_range("index is out of the range");
        for (std::size_t i = 0; i < size1_ * size2_; ++i)
            data_[i] -= other.data_[i];
        return *this;
    }
    template <class T>
    AMatrix<T>& AMatrix<T>::operator*=(const AMatrix& other) {
        // TODO: Rewrite this!
        /*if (size1_ * size2_ != other.size1_ * other.size2_)
            throw std::out_of_range("index is out of the range");
        AMatrix<T> res(size1_, other.size2_, 0);
        for (std::size_t i = 0; i < size1_; ++i) {
            for (std::size_t k = 0; k < other.size2_; ++k) {
                for (std::size_t j = 0; j < other.size1_; ++j) {
                    res.data_[k + i * other.size2_] += data_[j + i * size2_] * other.data_[k + j * other.size2_];
                }
            }
        }
        return res;*/ 
        return nullptr;
    }

    template <class T>
    AMatrix<T> AMatrix<T>::operator++(int) {
        AMatrix<T> res(*this);
        ++*this;
        return res;
    }
    template <class T>
    AMatrix<T>& AMatrix<T>::operator++() {
        for (std::size_t i = 0; i < size1_ * size2_; ++i) {
            data_[i] += 1;
        }
        return *this;
    }
    template <class T>
    AMatrix<T> AMatrix<T>::operator--(int) {
        AMatrix<T> res(*this);
        --*this;
        return res;
    }
    template <class T>
    AMatrix<T>& AMatrix<T>::operator--() {
        for (std::size_t i = 0; i < size1_ * size2_; ++i) {
            data_[i] -= 1;
        }
        return *this;
    }

    template <class T>
    AMatrix<T> AMatrix<T>::operator+(T&& val) const {
        AMatrix<T> res(*this);
        for (std::size_t i = 0; i < size1_ * size2_; ++i)
            res.data_[i] += val;
        return res;
    }
    template <class T>
    AMatrix<T> AMatrix<T>::operator-(T&& val) const {
        AMatrix<T> res(*this);
        for (std::size_t i = 0; i < size1_ * size2_; ++i)
            res.data_[i] -= val;
        return res;
    }
    template <class T>
    AMatrix<T> AMatrix<T>::operator*(T&& val) const {
        AMatrix<T> res(*this);
        res.data_[i] *= val;
        return res;
    }
}
