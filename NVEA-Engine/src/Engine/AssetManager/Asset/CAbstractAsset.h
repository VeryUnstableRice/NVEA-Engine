#ifndef CAsset_Header
#define CAsset_Header
#include <string>

#include "Engine/MemoryManager/CObjectPtr.h"
#include "Engine/Object/CObject.h"

class CAbstractAsset : public CObject
{
public:
    virtual bool ShouldBeInit() const { return true; } 
    virtual void Initialiaze(const std::string& path) = 0;
};

template<typename  T>
class CTemplateAsset : public CAbstractAsset
{
    CObjectPtr<T> Asset = nullptr;
protected:
    void    SetAsset(T* asset) { Asset = asset; }
public:
    T*      GetAsset() { return Asset; }
};

#endif