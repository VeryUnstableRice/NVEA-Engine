#ifndef CObjectsPointedAt_Header
#define CObjectsPointedAt_Header
#include <algorithm>
#include <vector>

class CPointedObjectsGC
{
    std::vector<class CObject*> m_objects;
public:
    void MarkAsPointed(CObject* object)
    {
        if(IsObjectPointAt(object)) return;
        m_objects.push_back(object);
    }
    
    bool IsObjectPointAt(CObject* object)
    {
        return std::ranges::count(m_objects, object) >= 1;
    }
};

#endif