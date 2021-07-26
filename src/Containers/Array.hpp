#pragma once

#include "Core/Defines.hpp"
#include "Core/Ref.hpp"

#include <new>
#include <utility>

template<typename T>
class Array final: public IRef {
public:
    Array() : Data(nullptr), Length(0), Capacity(0) {}

    Array(const Array& other) : Data(nullptr), Length(other.Length), Capacity(other.Length) {
        this->Data = static_cast<T*>(::operator new(this->Capacity * sizeof(T)));
        for (u64 i = 0; i < other.Length; i++) {
            new (&this->Data[i]) T(other.Data[i]);
        }
    }

    Array(Array&& other) : Data(other.Data), Length(other.Length), Capacity(other.Capacity) {}

    ~Array() {
        this->Clear();
        ::operator delete(this->Data, this->Capacity * sizeof(T));
    }
public:
    T& operator[](u64 index) {
        // TODO: Bounds check
        return this->Data[index];
    }

    const T& operator[](u64 index) const {
        // TODO: Bounds check
        return this->Data[index];
    }
public:
    T& Add(const T& value) {
        this->GrowIfNecessary();
        new (&this->Data[this->Length]) T(value);
        this->Length++;
        return this->Data[this->Length - 1];
    }

    T& Add(T&& value) {
        this->GrowIfNecessary();
        new (&this->Data[this->Length]) T(std::move(value));
        this->Length++;
        return this->Data[this->Length - 1];
    }

    template<typename ...Args>
    T& Emplace(Args&&... args) {
        this->GrowIfNecessary();
        new (&this->Data[this->Length]) T(std::forward<Args>(args)...);
        this->Length++;
        return this->Data[this->Length - 1];
    }

    void Clear() {
        for (u64 i = 0; i < this->Length; i++) {
            this->Data[i].~T();
        }
        this->Length = 0;
    }
private:
    void GrowIfNecessary() {
        if (this->Length >= this->Capacity) {
            u64 newCapacity = this->Capacity == 0 ? 1 : this->Capacity * 2;
            T* newData      = static_cast<T*>(::operator new(newCapacity * sizeof(T)));

            for (u64 i = 0; i < this->Length; i++) {
                new (&newData[i]) T(std::move(this->Data[i]));
            }

            ::operator delete(this->Data, this->Capacity * sizeof(T));
            this->Data     = newData;
            this->Capacity = newCapacity;
        }
    }
public: // TODO: Do I make this private?
    T* Data;
    u64 Length;
    u64 Capacity;
};
