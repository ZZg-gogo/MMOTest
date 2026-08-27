#include "ObjectGuid.h"




ObjectGuid ObjectGuid::Global(High16Guid hi, uint32_t counter)
{
    return ObjectGuid(hi, counter);
}


ObjectGuid ObjectGuid::MapSpecific(High16Guid hi, uint32_t entry, uint32_t counter)
{
    return ObjectGuid(hi, entry, counter);
}


ObjectGuid::ObjectGuid(High16Guid hi, uint32_t entry, uint32_t counter)
    : m_guid(counter?(static_cast<uint64_t>(hi)<<48 | static_cast<uint64_t>(entry)<<24 | counter) : 0 )
{
    
}
ObjectGuid::ObjectGuid(High16Guid hi, uint32_t counter)
    : m_guid(counter?(static_cast<uint64_t>(hi)<<48 | counter) : 0  )
{

}



bool ObjectGuid::hasEntry(High16Guid hi)
{
    switch (hi)
    {
        case High16Guid::Item:
        case High16Guid::Player:
        case High16Guid::DynamicObject:
        case High16Guid::Corpse:
        case High16Guid::Mo_Transport:
        case High16Guid::Instance:
        case High16Guid::Group:
            return false;
        case High16Guid::GameObject:
        case High16Guid::Transport:
        case High16Guid::Unit:
        case High16Guid::Pet:
        case High16Guid::Vehicle:
        default:
            return true;
    }
}