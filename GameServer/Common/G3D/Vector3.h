#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include "g3dmath.h"

class Vector3
{

public:
    float m_x, m_y, m_z;

public:
    Vector3();  
    Vector3(float x, float y, float z);
    Vector3(const Vector3& vec3);
    Vector3& operator=(const Vector3& other);

    const float& operator[](int i) const;
    float& operator[](int i);

    bool nonZero() const 
    {
        return (0 != m_x) && (0 != m_y) && (0 != m_z);
    }


    bool operator== (const Vector3& other) const;
    bool operator!= (const Vector3& other) const;

    //两个坐标是否大致相等 浮点数存在着误差
    bool fuzzyEq(const Vector3& other) const;
    bool fuzzyNotEq(const Vector3& other) const;
    //是否是一个有限数
    bool isFinite() const;

    bool isNaN() const;
    bool isZero() const;
    //是否已经被归一化了
    bool isUnit() const;

    
    //向着目标点最多移动maxTranslation的距离
    Vector3 movedTowards(const Vector3& goal, float maxTranslation) const;
    void moveTowards(const Vector3& goal, float maxTranslation);

    Vector3  operator+ (const Vector3& v) const;
    Vector3  operator- (const Vector3& v) const;
    Vector3  operator* (float s) const;

    inline Vector3 operator/ (float s) const 
    {
        return *this * (1.0f / s);
    }

    Vector3 operator* (const Vector3& v) const;
    Vector3 operator/ (const Vector3& v) const;
    Vector3 operator- () const;

    Vector3&  operator+= (const Vector3& v);
    Vector3&  operator-= (const Vector3& v);
    Vector3&  operator*= (float s);
    inline Vector3&  operator/= (float s) {
        return (*this *= (1.0f / s));
    }
    Vector3&  operator*= (const Vector3& v);
    Vector3&  operator/= (const Vector3& v);

    //向量的模长
    float length() const;

    Vector3 pow(float p) const 
    {
        return Vector3(powf(m_x, p), powf(m_y, p), powf(m_z, p));
    }
    //得到单位方向向量
    Vector3 direction() const;

    //单位方向向量
    inline Vector3 directionOrZero() const 
    {
        float len = length();    //得到长度
        if (len < 0.0000001f)
        {
            return Vector3::Zero();
        }
        else if (len < 1.00001f && len > 0.99999f)
        {
            return *this;
        }
        else
        {
            return *this * (1.0f / len);
        }
    }
    //单位向量
    inline Vector3 unit() const
    {
        return direction();
    }

    //返回向量长度的平方
    float squaredLength() const;
    /**
     * 点乘：反映两个向量方向的一致程度
     *
     * dot > 0 → 夹角小于 90°，方向大致相同
     * dot = 0 → 两个向量垂直
     * dot < 0 → 夹角大于 90°，方向大致相反
     *
     * 如果两个向量都是单位向量：
     * dot = cos(θ)
     */
    float dot(const Vector3& other) const;

    /**
     * 叉乘：返回一个同时垂直于 this 和 other 的向量。
     *
     * 方向遵循右手定则：
     * 右手四指从 this 旋转到 other，
     * 大拇指所指的方向就是 this × other 的方向。
     *
     * 如果 this 和 other 位于同一个平面，
     * 叉乘结果会垂直于这个平面。
     *
     * MMO 常见情况：
     * XZ 为地面平面，Y 为高度轴，
     * 因此可以通过 crossResult.y 的正负判断左右：
     *
     * crossResult.y > 0 → other 在 this 的一侧
     * crossResult.y < 0 → other 在 this 的另一侧
     * crossResult.y = 0 → other 与 this 共线
     *
     * 注意：具体哪一侧对应“左/右”，
     * 取决于项目的坐标系和前进方向定义。
     */
    Vector3 cross(const Vector3& other) const;
    Vector3 unitCross(const Vector3& other) const;


public:
    static const Vector3& Zero();
    static const Vector3& One();
    static const Vector3& UnitX();
    static const Vector3& UnitY();
    static const Vector3& UnitZ();
};





#endif //namespace  __VECTOR3_H__