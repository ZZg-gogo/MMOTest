#include "ObjectGuid.h"
#include <sstream>
#include <iomanip>
#include <Logger.h>

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
            return true;
        default:
            return true;
    }
}


TypeID ObjectGuid::GetTypeId(High16Guid hi)
{
    switch (hi)
    {
    case High16Guid::Item :
        return TypeID::TYPEID_ITEM;
    case High16Guid::Unit :
        return TypeID::TYPEID_UNIT;
    case High16Guid::Pet :
        return TypeID::TYPEID_UNIT;
    case High16Guid::Vehicle:       
        return TypeID::TYPEID_UNIT;
    case High16Guid::Player :
        return TypeID::TYPEID_PLAYER;
    case High16Guid::GameObject :
        return TypeID::TYPEID_GAMEOBJECT;
    case High16Guid::Mo_Transport:
        return TypeID::TYPEID_GAMEOBJECT;
    case High16Guid::DynamicObject :
        return TypeID::TYPEID_DYNAMICOBJECT;
    case High16Guid::Corpse :
        return TypeID::TYPEID_CORPSE;
    default:
        return TypeID::TYPEID_OBJECT;
    }

}



std::string_view ObjectGuid::GetHighGuidName(High16Guid hi)
{
    switch (hi)
    {
        case High16Guid::Item:         return "Item";
        case High16Guid::Player:       return "Player";
        case High16Guid::GameObject:   return "Gameobject";
        case High16Guid::Transport:    return "Transport";
        case High16Guid::Unit:         return "Creature";
        case High16Guid::Pet:          return "Pet";
        case High16Guid::Vehicle:      return "Vehicle";
        case High16Guid::DynamicObject: return "DynObject";
        case High16Guid::Corpse:       return "Corpse";
        case High16Guid::Mo_Transport: return "MoTransport";
        case High16Guid::Instance:     return "InstanceID";
        case High16Guid::Group:        return "Group";
        default:
            return "<unknown>";
    }

}

std::string ObjectGuid::toString() const
{
    std::ostringstream str;
    str << "GUID Full: 0x" << std::hex << std::setw(16) << std::setfill('0') << m_guid << std::dec;
    str << " Type: " << GetTypeName();
    if (hasEntry())
        str << (isPet() ? " Pet number: " : " Entry: ") << getEntry() << " ";

    str << " Low: " << getCounter();
    return str.str();
}



void ObjectGuidGeneratorBase::HandleCounterOverflow(High16Guid hi)
{
    LOGGER_ERROR("HandleCounterOverflow {}", ObjectGuid::GetHighGuidName(hi));
}