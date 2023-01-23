#include "CObject.h"

#include <iostream>

#include "Engine/MemoryManager/CPointedObjectsGC.h"

void CObject::MarkForDestruction()
{
    m_pendingDestruction = true;
}

void CObject::CheckSubobjectsForGC(CPointedObjectsGC* PointedObjects)
{
    PointedObjects->MarkAsPointed(this);
}

void CObject::SetObjectName(const std::string& ObjectName)
{
    m_objectName = ObjectName;
}

CObject::CObject()
{
}

CObject::~CObject()
{
}

bool CObject::IsPendingDestruction()
{
    return m_pendingDestruction;
}

void CObject::OnConstruct()
{
}

void CObject::OnDestroy()
{
    MarkForDestruction();
}
