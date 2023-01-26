#include "CMemoryManager.h"

#include <iostream>
#include <ostream>

#include "CObjectPtr.h"
#include "CPointedObjectsGC.h"
#include "Engine/CAbstractEngine.h"

CMemoryManager* CMemoryManager::m_instance = nullptr;

CMemoryManager::CMemoryManager()
{
    TimePassed = 0;
    GarbageCollectionInterval = 30;
    m_instance = this;
    //CEngine::Engine->PrintLog("Memory manager initialized", GARBAGE_COLLECTOR);
}

CMemoryManager::~CMemoryManager()
{
    GarbageCollect(true);
    CAbstractEngine::Engine->PrintLog("Memory manager is being destroyed", GARBAGE_COLLECTOR);
}

void CMemoryManager::Initialize()
{
    CAbstractEngine::Engine->PrintLog("Memory manager initialized", GARBAGE_COLLECTOR);
}

void CMemoryManager::AddVariable(CAbstractObjectPtr* Pointer)
{
    m_variables.push_back(Pointer);
}

void CMemoryManager::RemoveVariable(CAbstractObjectPtr* Pointer)
{
    std::erase(m_variables, Pointer);
}

bool CMemoryManager::HasNonWeakPtr(ReferenceMap::iterator object) const
{
    for(CAbstractObjectPtr* Ptr : object->second)
        if(!Ptr->IsWeak())
            return true;
    return false;
}

CMemoryManager::VariableVector* CMemoryManager::GetVectorFor(CObject* Object)
{
    if(!Object) return nullptr;
    for(ReferenceMap::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
    {
        if(it->first != Object) continue;
        return &it->second;
    }
    return nullptr;
}

void CMemoryManager::PrintDebug()
{
    int amount = 0;
    std::string temp = "";
    for(ReferenceMap::iterator it = m_objects.begin(); it != m_objects.end();++it)
    {
        CObject* unusedObject = it->first;
        temp += unusedObject->GetObjectName() + " " + std::to_string((std::uintptr_t)unusedObject)+'\n';
        ++amount;
    }
    CAbstractEngine::Engine->PrintLog(temp, NORMAL);
}

void CMemoryManager::DeleteObjectsFromList(const ObjectVector& PendingDeletion)
{
    for(int i = 0; i < PendingDeletion.size(); ++i)
    {
        CObject* current_object = PendingDeletion[i];
        //has only weak pointers or nothing at all
        for (CAbstractObjectPtr* pointer : m_objects[current_object])
            pointer->Reset();

        //delete it once its not used
        CAbstractEngine::Engine->PrintLog("Freeing: " + current_object->GetObjectName() + " " + std::to_string(reinterpret_cast<std::uintptr_t>(current_object)), GARBAGE_COLLECTOR);
        std::erase(m_objectVector, current_object);
        delete current_object;
    }
}

void CMemoryManager::GarbageCollect(bool delete_everything)
{
    CAbstractEngine::Engine->PrintLog("Collecting Garbage", GARBAGE_COLLECTOR);

    /*CPointedObjectsGC PointedObjects;
    for(ReferenceMap::iterator it = m_objects.begin(); it != m_objects.end();)
    {
        CObject* current_object = it->first;
        current_object->CheckSubobjectsForGC(&PointedObjects);
    }*/
    
    
    ObjectVector PendingDeletion{};
    //iterating through all objects
    for(ReferenceMap::iterator it = m_objects.begin(); it != m_objects.end();)
    {
        CObject* current_object = it->first;
        //check if the object should be deleted
        if(std::ranges::count(m_deleteLast, current_object) >= 1 || !delete_everything && HasNonWeakPtr(it) || std::ranges::count(m_neverDelete, current_object) >= 1)
        {
            ++it;
            continue;
        }
        //call OnDestroy, at this point the object is destroyed, just not freed 
        current_object->OnDestroy();
        it = m_objects.erase(it);

        //adding to a list to be freed later
        PendingDeletion.push_back(current_object);
    }

    //free objects
    DeleteObjectsFromList(PendingDeletion);
    if(delete_everything) DeleteObjectsFromList(m_deleteLast);
    
    CAbstractEngine::Engine->PrintLog("Garbage collected: " + std::to_string(PendingDeletion.size()), GARBAGE_COLLECTOR);
}

void CMemoryManager::ReferenceChanged(CAbstractObjectPtr* variable, CObject* OldObject, CObject* NewObject)
{
    if(VariableVector* vector = GetVectorFor(OldObject))
        std::erase(*vector, variable);
    if(VariableVector* vector = GetVectorFor(NewObject))
        vector->emplace_back(variable);
}

void CMemoryManager::AddToDeleteLast(CObject* DeleteLast)
{
    return m_deleteLast.push_back(DeleteLast);
}

void CMemoryManager::AddToNeverDelete(CObject* NeverDelete)
{
    m_neverDelete.push_back(NeverDelete);
}

CMemoryManager* CMemoryManager::GetInstance()
{
    return m_instance;
}

void CMemoryManager::Tick(double DeltaTime)
{
    TimePassed += DeltaTime;
    if(TimePassed >= GarbageCollectionInterval)
    {
        GarbageCollect();
        TimePassed = 0;
    }
}
