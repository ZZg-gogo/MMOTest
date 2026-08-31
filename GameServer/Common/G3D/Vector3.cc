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

Vector3& Vector3::operator=(const Vector3& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;

    return *this;
}


void Vector3::moveTowards(const Vector3& goal, float maxTranslation)
{
    Vector3 dx = goal - *this;
    float len = dx.length();
    if ((len < 0.00001f) || len <= maxTranslation)
    {
        *this = goal;
    }
    else
    {
        *this += dx * std::min(1.0f, maxTranslation/len);
    }
    
}

Vector3 Vector3::movedTowards(const Vector3& goal, float maxTranslation) const
{
    Vector3 temp {*this};
    temp.moveTowards(goal, maxTranslation);
    return temp;
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


Vector3 Vector3::operator* (const Vector3& v) const
{
    return Vector3{m_x*v.m_x, m_y*v.m_y, m_z*v.m_z};
}
Vector3 Vector3::operator/ (const Vector3& v) const
{
    return Vector3{m_x/v.m_x, m_y/v.m_y, m_z/v.m_z};
}
Vector3 Vector3::operator- () const
{
    return Vector3{-m_x, -m_y, -m_z};
}

Vector3&  Vector3::operator+= (const Vector3& v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
    return *this;
}
Vector3&  Vector3::operator-= (const Vector3& v)
{
    m_x -= v.m_x;
    m_y -= v.m_y;
    m_z -= v.m_z;
    return *this;
}
Vector3&  Vector3::operator*= (float s)
{
    m_x *= s;
    m_y *= s;
    m_z *= s;
    return *this;
}



Vector3&  Vector3::operator*= (const Vector3& v)
{
    m_x *= v.m_x;
    m_y *= v.m_y;
    m_z *= v.m_z;
    return *this;
}
Vector3&  Vector3::operator/= (const Vector3& v)
{
    m_x /= v.m_x;
    m_y /= v.m_y;
    m_z /= v.m_z;
    return *this;
}



float Vector3::length() const
{
    return std::sqrtf(squaredLength());
}


//得到单位方向向量
Vector3 Vector3::direction() const
{
    const float len = length();
    const float invLen = 1.0f/len;
    return Vector3{m_x*invLen, m_y*invLen, m_z*invLen};
}


//返回向量长度的平方
float Vector3::squaredLength() const
{
    return m_x*m_x+m_y*m_y+m_z*m_z;
}


float Vector3::dot(const Vector3& other) const
{
    return m_x*other.m_x+m_y*other.m_y+m_z*other.m_z;
}



Vector3 Vector3::cross(const Vector3& other) const
{
    return Vector3{m_y*other.m_z - m_z*other.m_y, m_z*other.m_x - m_x*other.m_z, m_x*other.m_y - m_y*other.m_x};
}


Vector3 Vector3::unitCross(const Vector3& other) const
{
    Vector3 kCross = cross(other);
    return kCross.unit();
}


const Vector3& Vector3::Zero()
{
    static const Vector3 v(0, 0, 0); 
    return v;
}
const Vector3& Vector3::One()
{
    static const Vector3 v(1, 1, 1); 
    return v; 
}
const Vector3& Vector3::UnitX()
{
    static const Vector3 v(1, 0, 0); 
    return v; 
}
const Vector3& Vector3::UnitY()
{
    static const Vector3 v(0, 1, 0); 
    return v;
}
const Vector3& Vector3::UnitZ()
{
    static const Vector3 v(0, 0, 1);
    return v;
}