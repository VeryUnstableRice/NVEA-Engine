#include "CObjectPtr.h"
#include "Engine/CAbstractEngine.h"

CAbstractObjectPtr::CAbstractObjectPtr()
{
    CMemoryManager::GetInstance()->AddVariable(this);
}

CAbstractObjectPtr::~CAbstractObjectPtr()
{
    CMemoryManager::GetInstance()->RemoveVariable(this);
}

void ReferenceChanged(CAbstractObjectPtr* variable, CObject* OldObject, CObject* NewObject)
{
    CMemoryManager::GetInstance()->ReferenceChanged(variable, OldObject, NewObject);
}
