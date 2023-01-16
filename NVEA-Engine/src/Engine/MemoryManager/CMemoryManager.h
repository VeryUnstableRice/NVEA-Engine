#ifndef CMemoryManager_Header
#define CMemoryManager_Header
#include <algorithm>
#include <unordered_map>
#include <vector>

#include "Engine/Object/CObject.h"

class CMemoryManager : public CObject
{
    using VariableVector = std::vector<class CAbstractObjectPtr*>;
    using ReferenceMap = std::unordered_map<CObject*, VariableVector>;
    using ObjectVector = std::vector<CObject*>;
    
    VariableVector m_variables;
    ReferenceMap m_objects;
    ObjectVector m_objectVector;
    ObjectVector m_deleteLast;      // will be deleted after everything, such as the engine
    ObjectVector m_neverDelete;      // will simply never be deleted

    static CMemoryManager* m_instance;
    
    friend class CAbstractObjectPtr;
    void AddVariable(CAbstractObjectPtr* Pointer);
    void RemoveVariable(CAbstractObjectPtr* Pointer);

    double TimePassed;
    double GarbageCollectionInterval;

    bool HasNonWeakPtr(ReferenceMap::iterator object) const;
    VariableVector* GetVectorFor(CObject* Object);
    void PrintDebug();
    void DeleteObjectsFromList(const ObjectVector& PendingDeletion);
    void GarbageCollect(bool delete_everything = false);

    friend class ObjectIterator;
public:
    CMemoryManager();
    virtual ~CMemoryManager();
    void Initialize();
    void Tick(double DeltaTime);

    void ReferenceChanged(CAbstractObjectPtr* variable, CObject* OldObject, CObject* NewObject);
    void AddToDeleteLast(CObject* DeleteLast);
    void AddToNeverDelete(CObject* NeverDelete);

    static CMemoryManager* GetInstance();

    const ObjectVector& GetObjectVector() const
    {
        return m_objectVector;
    }
    
    template<typename T = CObject>
    T* CreateObject(bool CallCtor)
    {
        T* object = new T();
        if(CallCtor)
            object->OnConstruct();
        object->SetObjectName(typeid(T).name());
        m_objects.insert(m_objects.begin(), {object, VariableVector{}});
        m_objectVector.push_back(object);
        return object;
    }
};

class ObjectIterator 
{
public:
    ObjectIterator() : m_vector(&CMemoryManager::GetInstance()->GetObjectVector())
    {
        
    }
    
    CObject& operator*() const { return *(*m_vector)[m_index]; }
    CObject* operator->() const { return (*m_vector)[m_index]; }
    operator bool() const
    {
        return m_index < m_vector->size();
    }

    ObjectIterator& operator++()
    {
        ++m_index;
        return *this;
    }  

    ObjectIterator operator++(int)
    {
        ObjectIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator== (const ObjectIterator& a, const ObjectIterator& b) { return a.m_index == b.m_index; }
    friend bool operator!= (const ObjectIterator& a, const ObjectIterator& b) { return a.m_index != b.m_index; }     

private:
    int m_index = 0;
    const CMemoryManager::ObjectVector* m_vector;
};

#endif
