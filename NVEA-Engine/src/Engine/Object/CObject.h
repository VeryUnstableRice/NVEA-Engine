#ifndef CObject_HEADER
#define CObject_HEADER
#include <string>

class CObject
{
    std::string m_objectName;
    bool m_pendingDestruction = false;
protected:
    void MarkForDestruction();
    
    friend class CMemoryManager;
    friend bool IsValid(CObject* object);

    virtual void CheckSubobjectsForGC(class CPointedObjectsGC* PointedObjects);
public:
    void SetObjectName(const std::string& ObjectName);
    const std::string& GetObjectName() const { return m_objectName; }
    
    CObject();
    virtual ~CObject();

    bool IsPendingDestruction();

    virtual void OnConstruct();
    virtual void OnDestroy();
};

inline bool IsValid(CObject* object)
{
    return object && !object->IsPendingDestruction();
}

#endif