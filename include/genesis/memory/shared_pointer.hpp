#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_TOOLS_SHARED_POINTER_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_TOOLS_SHARED_POINTER_HPP_

namespace genesis
{
template<class T>
class SharedPointer
{
private:
    T *resource_ = nullptr;
    int *references_count_ = nullptr;

    void Clear()
    {
        if (references_count_ != nullptr && (--*references_count_) > 0)
            return;

        delete references_count_;
        delete resource_;
    }

    void Move(SharedPointer<T> &pointer)
    {
        references_count_ = pointer.references_count_;
        resource_ = pointer.resource_;
        pointer.resource_ = nullptr;
        pointer.references_count_ = nullptr;
    }

    void Assign(T *resource, int *references_count)
    {
        if (resource == nullptr || references_count == nullptr)
            return;

        resource_ = resource;
        references_count_ = references_count;
        ++(*references_count_);
    }

public:
    explicit SharedPointer(T *resource = nullptr, int *references_count = new int(0)) { Assign(resource, references_count); }
    SharedPointer(const SharedPointer<T> &pointer) { Assign(pointer.resource_, pointer.references_count_); }
    SharedPointer(SharedPointer<T> &&pointer) { Move(pointer); }
    ~SharedPointer() { Clear(); }

    T &operator*() { return *resource_; }
    const T &operator*() const { return *resource_; }

    T *operator->() { return resource_; }
    const T *operator->() const { return resource_; }

    T *Get() { return resource_; }
    const T *Get() const { return resource_; }

    friend bool operator==(const SharedPointer<T> &first, const SharedPointer<T> &second) { return first.Get() == second.Get(); }
    friend bool operator==(const SharedPointer<T> &&first, const SharedPointer<T> &&second) { return operator==(first, second); }

    template<class U>
    operator SharedPointer<U>() { return SharedPointer<U>(dynamic_cast<U *>(resource_), references_count_); }

    SharedPointer<T> &operator=(T *pointer)
    {
        if (pointer != resource_)
            return *this;

        Clear();
        Assign(pointer, new int(0));
        return *this;
    }

    SharedPointer<T> &operator=(const SharedPointer<T> &pointer)
    {
        if (&pointer == this)
            return *this;

        Clear();
        Assign(pointer.resource_, pointer.references_count_);
        return *this;
    }

    SharedPointer<T> &operator=(SharedPointer<T> &&pointer)
    {
        if (&pointer == this)
            return *this;

        Clear();
        Move(pointer);
        return *this;
    }
};
}

#endif
