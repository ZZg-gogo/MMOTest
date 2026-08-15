#ifndef  __VEC2_H__
#define __VEC2_H__




class Vec2
{
public:
	Vec2() : m_x(0), m_y(0) {}
	Vec2(double x, double y) : m_x(x), m_y(y) {}

public:
	Vec2& operator +=(const Vec2& v);
	Vec2& operator -=(const Vec2& v);
	Vec2& operator *=(const Vec2& v);
	Vec2& operator /=(const Vec2& v);

	bool operator < (const Vec2& rhs) const;
	bool operator <= (const Vec2& rhs) const;
	bool operator > (const Vec2& rhs) const;
	bool operator >= (const Vec2& rhs) const;

	void PrintVec() const;

public:
	double dot(const Vec2& rhs) const;
	double cross(const Vec2& rhs) const;
	double len() const;
	double lenSqr()const;

	Vec2 half() const;
	Vec2 midPoint(const Vec2& rhs) const;

	void set(double x, double y);
	void zero();
	void one();
	void inverse();

	void normalize();

public:

	static double Dot(const Vec2& a, const Vec2& b);
	static double Cross(const Vec2& a, const Vec2& b);

	static Vec2	Inverse(const Vec2& a);
	static Vec2	Normalize(const Vec2& a);
public:
	double m_x, m_y;
};


inline Vec2 operator+(const Vec2& a, const Vec2& b)
{
	return Vec2(a.m_x + b.m_x, a.m_y + b.m_y);
}

inline Vec2 operator-(const Vec2& a, const Vec2& b)
{
	return Vec2(a.m_x - b.m_x, a.m_y - b.m_y);
}

inline Vec2 operator*(const Vec2& a, const Vec2& b)
{
	return Vec2(a.m_x * b.m_x, a.m_y * b.m_y);
}

inline Vec2 operator/(const Vec2& a, const Vec2& b)
{
	return Vec2(a.m_x / b.m_x, a.m_y / b.m_y);
}







#endif // ! __VEC2_H__

