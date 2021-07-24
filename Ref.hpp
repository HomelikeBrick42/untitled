#pragma once

#include <type_traits>
#include <utility>

class IRef {
public:
    void IncRefCount() const {
        this->RefCount++;
    }

    void DecRefCount() const {
        this->RefCount--;
    }

    void ZeroRefCount() const {
        this->RefCount = 0;
    }

    u64 GetRefCount() const {
        return this->RefCount;
    }
private:
    mutable u64 RefCount = 0;
};

template<typename T>
class Ref {
    static_assert(std::is_base_of<IRef, T>::value, "Class is not ref counted!");
    template<class U>
    friend class Ref;
public:
    Ref()
        : Instance(nullptr) {}

    Ref(std::nullptr_t n)
        : Instance(nullptr) {}

    Ref(T* instance)
        : Instance(instance) {
        this->IncRef();
    }

    Ref(const Ref<T>& other)
        : Instance(other.Instance) {
        this->IncRef();
    }

    template<typename U>
    Ref(const Ref<U>& other)
        : Instance((T*)other.Instance) {
        this->IncRef();
    }

    template<typename U>
    Ref(Ref<U>&& other)
            : Instance((T*)other.Instance) {
        other.Instance = nullptr;
    }

    ~Ref() {
        this->DecRef();
    }

    Ref& operator=(std::nullptr_t)
    {
        this->DecRef();
        this->Instance = nullptr;
        return *this;
    }

    Ref& operator=(const Ref<T>& other)
    {
        other.IncRef();
        this->DecRef();

        this->Instance = other.Instance;
        return *this;
    }

    template<typename T2>
    Ref& operator=(const Ref<T2>& other)
    {
        other.IncRef();
        this->DecRef();

        this->Instance = other.Instance;
        return *this;
    }

    template<typename T2>
    Ref& operator=(Ref<T2>&& other)
    {
        this->DecRef();

        this->Instance = other.Instance;
        other.Instance = nullptr;
        return *this;
    }

    explicit operator bool() { return this->Instance != nullptr; }
    explicit operator bool() const { return this->Instance != nullptr; }

    T* operator->() { return this->Instance; }
    const T* operator->() const { return this->Instance; }

    T& operator*() { return *this->Instance; }
    const T& operator*() const { return *this->Instance; }

    T* Raw() { return this->Instance; }
    const T* Raw() const { return this->Instance; }

    void Release() {
        delete this->Instance;
        this->Instance->ZeroRefCount();
    }

    void Reset(T* instance = nullptr)
    {
        this->DecRef();
        this->Instance = instance;
    }

    template<typename... Args>
    static Ref<T> Create(Args&&... args)
    {
        return Ref<T>(new T(std::forward<Args>(args)...));
    }

    template<typename T2>
    Ref<T2> As() const
    {
        return Ref<T2>(*this);
    }
private:
    void IncRef() {
        if (this->Instance) {
            this->Instance->IncRefCount();
        }
    }

    void DecRef() {
        if (this->Instance) {
            this->Instance->DecRefCount();
            if (this->Instance->GetRefCount() == 0) {
                delete this->Instance;
                this->Instance = nullptr;
            }
        }
    }
private:
    T* Instance = nullptr;
};
