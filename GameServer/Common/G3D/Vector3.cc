#include "Vector3.h"
#include "g3dmath.h"

Vector3::Vector3()
    : m_x(0.0f), m_y(0.0), m_z(0.0)
{

}
Vector3::Vector3(float x, float y, float z)
    : m_x(x), m_y(y), m_z(z)
{

}
Vector3::Vector3(const Vector3& vec3)
    : m_x(vec3.m_x), m_y(vec3.m_y), m_z(vec3.m_z)
{

}

const float& Vector3::operator[](int i) const
{
    if (0 == i)
    {
        return m_x;
    }
    else if (1 == i)
    {
        return m_y;
    }
    else
    {
        return m_z;
    }
}


float& Vector3::operator[](int i)
{
    if (0 == i)
    {
        return m_x;
    }
    else if (1 == i)
    {
        return m_y;
    }
    else
    {
        return m_z;
    } 
}



bool Vector3::operator== (const Vector3& other) const
{
    return (other.m_x == m_x) && (other.m_y == m_y) && (other.m_z == m_z);
}


bool Vector3::operator!= (const Vector3& other) const
{
    return !(*this == other);
}


//两个坐标是否大致相等 浮点数存在着误差
bool Vector3::fuzzyEq(const Vector3& other) const
{
    return ::fuzzyEq( (*this-other).squaredLength() , 0.0f);
}

bool Vector3::fuzzyNotEq(const Vector3& other) const
{
    return !fuzzyEq(other);
}



//是否是一个有限数
bool Vector3::isFinite() const
{
    return std::isfinite(m_x) && std::isfinite(m_y) && std::isfinite(m_z);
}

//是否不是一个数
bool Vector3::isNaN() const
{
    return std::isnan(m_x) || std::isnan(m_y) || std::isnan(m_z);
}
bool Vector3::isZero() const
{
    return ::fuzzyEq(std::fabsf(m_x) + std::fabsf(m_y) + std::fabsf(m_z), 0.0f);
}


//是否已经被归一化了
bool Vector3::isUnit() const
{
    return ::fuzzyEq(squaredLength(), 1.0f);
}


Vector3  Vector3::operator+ (const Vector3& v) const
{
    return Vector3(m_x+v.m_x, m_y+v.m_y, m_z+v.m_z);
}
Vector3  Vector3::operator- (const Vector3& v) const
{
    return Vector3(m_x-v.m_x, m_y-v.m_y, m_z-v.m_z);
}
Vector3  Vector3::operator* (float s) const
{
    return Vector3(m_x*s, m_y*s, m_z*s);
}
