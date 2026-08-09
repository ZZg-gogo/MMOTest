#include "Vec2.h"
#include <iostream>
#include <cassert>
#include <cmath>


Vec2& Vec2::operator+=(const Vec2& v)
{
	m_x += v.m_x;
	m_y += v.m_y;

	return *this;
}


Vec2 & Vec2::operator-=(const Vec2& v)
{
	m_x -= v.m_x;
	m_y -= v.m_y;

	return *this;
}

Vec2& Vec2::operator/=(const Vec2& v)
{
	m_x /= v.m_x;
	m_y /= v.m_y;

	return *this;
}


Vec2& Vec2::operator*=(const Vec2& v)
{
	m_x *= v.m_x;
	m_y *= v.m_y;

	return *this;
}


bool Vec2::operator < (const Vec2& rhs) const
{
	if (m_x != rhs.m_x)
		return m_x < rhs.m_x;
	return m_y < rhs.m_y;
}


bool Vec2::operator <= (const Vec2& rhs) const
{
	// 利用已经写好的 operator<，逻辑就是“不大于” 
	return !(rhs < *this);
}


bool Vec2::operator > (const Vec2& rhs) const
{
	// 利用已经写好的 operator<，逻辑就是“小于的反向”
	return rhs < *this;
}

bool Vec2::operator>= (const Vec2& rhs) const
{
	// 逻辑就是“不小于”
	return !(*this < rhs);
}




double Vec2::dot(const Vec2& rhs) const
{
	return (m_x * rhs.m_x + m_y * rhs.m_y);
}
double Vec2::cross(const Vec2& rhs) const
{
	return (m_x * rhs.m_y - m_y * rhs.m_x);
}
double Vec2::len() const
{
	return std::sqrt(m_x * m_x + m_y * m_y);
}
double Vec2::lenSqr()const
{
	return (m_x * m_x + m_y * m_y);
}

Vec2 Vec2::half() const
{
	return Vec2(m_x / 2, m_y / 2);
}

Vec2 Vec2::midPoint(const Vec2& rhs) const
{
	return Vec2((m_x + rhs.m_x) * 0.5f, (m_y + rhs.m_y) * 0.5f);
}

void Vec2::set(double x, double y)
{
	m_x = x;
	m_y = y;
}
void Vec2::zero()
{
	m_x = 0;
	m_y = 0;
}
void Vec2::one()
{
	m_x = 1;
	m_y = 1;
}

void Vec2::inverse()
{
	// Debug 模式下：只要 x 或 y 是 0，程序直接弹框报错，让你意识到传入了非法向量
	assert(m_x != 0.0 && m_y != 0.0);

	// Release 模式下（如果 assert 被宏禁用了），依然做保护
	if (m_x != 0.0 && m_y != 0.0)
	{
		m_x = 1.0 / m_x;
		m_y = 1.0 / m_y;
	}
	else
	{
		// 可以视业务需求置为 0，或者保留原值，这里置为 0 表示“无穷大变回无效”
		m_x = 0.0;
		m_y = 0.0;
	}
}


void Vec2::normalize()
{
	double l = len();
	// 1e-12 是一个极小的数，足以过滤掉 0 或接近 0 的向量
	if (l > 1e-12)
	{
		m_x /= l;
		m_y /= l;
	}
	else
	{
		// 无法归一化时，置为零向量（也可以置为 (1,0)，取决于你的游戏逻辑）
		m_x = 0.0;
		m_y = 0.0;
	}
}



double Vec2::Dot(const Vec2& a, const Vec2& b)
{
	return (a.m_x * b.m_x + a.m_y * b.m_y);
}

double Vec2::Cross(const Vec2& a, const Vec2& b)
{

	return a.m_x * b.m_y - a.m_y * b.m_x;
}

Vec2 Vec2::Inverse(const Vec2& a)
{
	Vec2 out = a;
	out.inverse();

	return out;
}


Vec2 Vec2::Normalize(const Vec2& a)
{
	Vec2 out = a;
	out.normalize();

	return out;
}


void Vec2::PrintVec() const
{
	std::cout << "PrintVec this = "<< this<<" x = " << m_x << " y = " << m_y << "\n";
}
