#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <utility>
// Your implementation here

template <typename T> class UniquePtr 
{
public:
    // Constructor - defaults to nullptr
    UniquePtr() : uPtr(nullptr) {}

    // Gets ownership of a given raw pointer
    UniquePtr(T* ptr) : uPtr(ptr) {}

    // Copying is disallowed since unique pointer needs to be unique
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator = (const UniquePtr&) = delete;

    // Move constructor
    UniquePtr(UniquePtr&& other){
        uPtr = other.uPtr;
        other.uPtr = nullptr;
    };

    // Move assignment
    UniquePtr& operator=(UniquePtr&& other){
        if (this != &other){
            reset(other.release());
        }
        return *this;
    };

    // Converting move constructor
    template <typename U>
    UniquePtr(UniquePtr<U>&& other) : uPtr(other.release()) {}

    // Destructor
    ~UniquePtr() {
        delete uPtr;
    }

    T& operator*() const { return *uPtr; }
    T* operator->() const { return uPtr; }
    T* get() const { return uPtr; }

    bool operator==(const UniquePtr<T>& other) const {
        return uPtr == other.uPtr;
    }

    T* release(){
        T *tempPtr = uPtr;
        uPtr = nullptr;
        return tempPtr;
    };

    void reset(T* newPtr = nullptr){
        T* oldPtr = uPtr;
        uPtr = newPtr;
        delete oldPtr;
    };

    void swap(UniquePtr& other){
        T *temp = uPtr;
        uPtr = other.uPtr;
        other.uPtr = temp;
    };

    operator bool() const {
        return uPtr != nullptr;
    }

private:
    T* uPtr;
};

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args)
{
    T *ptr = new T(std::forward<Args>(args)...);
    return UniquePtr<T>(ptr);
}

#endif
