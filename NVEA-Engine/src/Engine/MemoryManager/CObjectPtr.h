#ifndef CObjectPtr_Header
#define CObjectPtr_Header
#include "Engine/Object/CObject.h"

class CAbstractObjectPtr
{
    friend class CMemoryManager;
    virtual bool IsWeak() const = 0;
public:
    CAbstractObjectPtr();
    virtual ~CAbstractObjectPtr();

    virtual void Reset() = 0;
    virtual CObject* GetObject() const = 0;
    virtual void SetObject(CObject* Object) = 0;
};


void ReferenceChanged(CAbstractObjectPtr* variable, CObject* OldObject, CObject* NewObject);

template<typename T = CObject, bool weak = false>
class CObjectPtr : public CAbstractObjectPtr
{
protected:
    T* Pointer = nullptr;
    bool IsWeak() const override
    {
        return weak;
    }
public:
    CObjectPtr(const CObjectPtr<T>& object) : CAbstractObjectPtr()
    {
        Pointer = object.Pointer;
        ReferenceChanged(this, nullptr, (CObject*)Pointer);
    }

    CObjectPtr(CObjectPtr<T>&& object) : CAbstractObjectPtr()
    {
        Pointer = object.Pointer;
        ReferenceChanged(this, nullptr, (CObject*)Pointer);
    }
    
    CObjectPtr(T* Obj) : CAbstractObjectPtr()
    {
        Pointer = Obj;
        ReferenceChanged(this, nullptr, (CObject*)Pointer);
    }

    CObjectPtr(const T* &Obj) : CAbstractObjectPtr()
    {
        Pointer = Obj;
        ReferenceChanged(this, nullptr, (CObject*)Pointer);
    }
    
    CObjectPtr() : CAbstractObjectPtr()
    {
        
    }
    
    virtual ~CObjectPtr()
    {
        CObjectPtr<T, weak>::Reset();
    }

    void Reset() override
    {
        ReferenceChanged(this, (CObject*)Pointer, nullptr);
        Pointer = nullptr;
    }
    
    CObject* GetObject() const override
    {
        return (CObject*)Pointer;
    }
    
    void SetObject(CObject* Object) override
    {
        Pointer = (T*)Object;
    }

    T* get() const
    {
        return Pointer;
    }

    CObjectPtr<T, weak>& operator=(T* object)
    {
        ReferenceChanged(this, (CObject*)Pointer, (CObject*)object);
        Pointer = object;
        return *this;
    }
    
    CObjectPtr<T, weak>& operator=(const CObjectPtr<T>& object)
    {
        return this->operator=(object.GetObject());
    }

    CObjectPtr<T, weak>& operator=(CObjectPtr<T>&& object)
    {
        ReferenceChanged(this, (CObject*)Pointer, (CObject*)object.get());
        Pointer=object.get();
        return *this;
    }

    T& operator*() const
    {
        return *Pointer;
    }
    
    T* operator->() const
    {
        return Pointer;
    }

    operator T*()
    {
        return Pointer;
    }

    operator bool()
    {
        return Pointer != nullptr;
    }
};


template<typename T>
using CWeakObjectPtr = CObjectPtr<T, true>;


#endif
