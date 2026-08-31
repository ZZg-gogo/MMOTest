#include <cassert>
#include <cmath>
#include <iostream>

#include <G3D/Vector3.h>

void testConstructor()
{
    Vector3 v;

    assert(v.m_x == 0.0f);
    assert(v.m_y == 0.0f);
    assert(v.m_z == 0.0f);

    Vector3 a(1.0f, 2.0f, 3.0f);

    assert(a.m_x == 1.0f);
    assert(a.m_y == 2.0f);
    assert(a.m_z == 3.0f);

    Vector3 b(a);

    assert(b == a);

    std::cout << "[PASS] Constructor\n";
}

void testAssignment()
{
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b;

    b = a;

    assert(b == a);

    std::cout << "[PASS] Assignment\n";
}

void testOperators()
{
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(4.0f, 5.0f, 6.0f);

    // +
    Vector3 c = a + b;
    assert(c == Vector3(5.0f, 7.0f, 9.0f));

    // -
    c = b - a;
    assert(c == Vector3(3.0f, 3.0f, 3.0f));

    // 向量 * 标量
    c = a * 2.0f;
    assert(c == Vector3(2.0f, 4.0f, 6.0f));

    // 向量 / 向量
    c = b / Vector3(2.0f, 5.0f, 3.0f);
    assert(c == Vector3(2.0f, 1.0f, 2.0f));

    // 向量逐分量乘
    c = a * b;
    assert(c == Vector3(4.0f, 10.0f, 18.0f));

    // 一元 -
    c = -a;
    assert(c == Vector3(-1.0f, -2.0f, -3.0f));

    std::cout << "[PASS] Operators\n";
}

void testCompoundOperators()
{
    Vector3 a(1.0f, 2.0f, 3.0f);

    a += Vector3(1.0f, 2.0f, 3.0f);
    assert(a == Vector3(2.0f, 4.0f, 6.0f));

    a -= Vector3(1.0f, 1.0f, 1.0f);
    assert(a == Vector3(1.0f, 3.0f, 5.0f));

    a *= 2.0f;
    assert(a == Vector3(2.0f, 6.0f, 10.0f));

    a *= Vector3(2.0f, 3.0f, 4.0f);
    assert(a == Vector3(4.0f, 18.0f, 40.0f));

    a /= Vector3(2.0f, 3.0f, 4.0f);
    assert(a == Vector3(2.0f, 6.0f, 10.0f));

    std::cout << "[PASS] Compound operators\n";
}

void testSubscript()
{
    Vector3 v(1.0f, 2.0f, 3.0f);

    assert(v[0] == 1.0f);
    assert(v[1] == 2.0f);
    assert(v[2] == 3.0f);

    v[0] = 10.0f;
    v[1] = 20.0f;
    v[2] = 30.0f;

    assert(v == Vector3(10.0f, 20.0f, 30.0f));

    std::cout << "[PASS] Subscript\n";
}

void testLength()
{
    Vector3 v(3.0f, 4.0f, 0.0f);

    assert(v.squaredLength() == 25.0f);
    assert(v.length() == 5.0f);

    std::cout << "[PASS] Length\n";
}

void testDirection()
{
    Vector3 v(3.0f, 4.0f, 0.0f);

    Vector3 dir = v.direction();

    assert(std::fabs(dir.m_x - 0.6f) < 0.00001f);
    assert(std::fabs(dir.m_y - 0.8f) < 0.00001f);
    assert(std::fabs(dir.m_z - 0.0f) < 0.00001f);

    // 归一化之后长度应该是 1
    assert(std::fabs(dir.length() - 1.0f) < 0.00001f);

    // isUnit 也应该成立
    assert(dir.isUnit());

    std::cout << "[PASS] Direction\n";
}

void testDot()
{
    Vector3 x(1.0f, 0.0f, 0.0f);
    Vector3 y(0.0f, 1.0f, 0.0f);

    // X 和 Y 垂直
    assert(x.dot(y) == 0.0f);

    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(4.0f, 5.0f, 6.0f);

    assert(a.dot(b) == 32.0f);

    // 同方向
    assert(x.dot(x) == 1.0f);

    // 反方向
    assert(x.dot(-x) == -1.0f);

    std::cout << "[PASS] Dot\n";
}

void testCross()
{
    Vector3 x(1.0f, 0.0f, 0.0f);
    Vector3 y(0.0f, 1.0f, 0.0f);
    Vector3 z(0.0f, 0.0f, 1.0f);

    // X × Y = Z
    assert(x.cross(y) == z);

    // Y × Z = X
    assert(y.cross(z) == x);

    // Z × X = Y
    assert(z.cross(x) == y);

    // 反过来方向相反
    assert(y.cross(x) == -z);

    // 平行向量叉乘应该是 0
    assert(x.cross(Vector3(2.0f, 0.0f, 0.0f)).isZero());

    std::cout << "[PASS] Cross\n";
}

void testFuzzy()
{
    Vector3 a(1.0f, 2.0f, 3.0f);

    Vector3 b(
        1.000001f,
        2.000001f,
        3.000001f
    );

    assert(a.fuzzyEq(b));
    assert(!a.fuzzyNotEq(b));

    Vector3 c(1.0f, 2.0f, 4.0f);

    assert(!a.fuzzyEq(c));
    assert(a.fuzzyNotEq(c));

    std::cout << "[PASS] Fuzzy comparison\n";
}

void testZero()
{
    assert(Vector3::Zero().isZero());

    assert(!Vector3(1.0f, 0.0f, 0.0f).isZero());

    std::cout << "[PASS] Zero\n";
}

void testFiniteAndNaN()
{
    Vector3 normal(1.0f, 2.0f, 3.0f);

    assert(normal.isFinite());
    assert(!normal.isNaN());

    Vector3 nanVector(
        NAN,
        2.0f,
        3.0f
    );

    assert(!nanVector.isFinite());
    assert(nanVector.isNaN());

    Vector3 infVector(
        INFINITY,
        2.0f,
        3.0f
    );

    assert(!infVector.isFinite());
    assert(!infVector.isNaN());

    std::cout << "[PASS] Finite / NaN\n";
}

void testMoveTowards()
{
    // 当前 (0,0,0)
    // 目标 (10,0,0)
    // 最多移动 3
    Vector3 current(0.0f, 0.0f, 0.0f);
    Vector3 goal(10.0f, 0.0f, 0.0f);

    current.moveTowards(goal, 3.0f);

    assert(current.fuzzyEq(Vector3(3.0f, 0.0f, 0.0f)));

    // 再移动 3
    current.moveTowards(goal, 3.0f);

    assert(current.fuzzyEq(Vector3(6.0f, 0.0f, 0.0f)));

    // 剩余 4，但是最多移动 10
    // 应该直接到目标
    current.moveTowards(goal, 10.0f);

    assert(current.fuzzyEq(goal));

    std::cout << "[PASS] MoveTowards\n";
}

void testStaticVectors()
{
    assert(Vector3::Zero() == Vector3(0.0f, 0.0f, 0.0f));
    assert(Vector3::One() == Vector3(1.0f, 1.0f, 1.0f));

    assert(Vector3::UnitX() == Vector3(1.0f, 0.0f, 0.0f));
    assert(Vector3::UnitY() == Vector3(0.0f, 1.0f, 0.0f));
    assert(Vector3::UnitZ() == Vector3(0.0f, 0.0f, 1.0f));

    std::cout << "[PASS] Static vectors\n";
}

int main()
{
    std::cout << "========== Vector3 Test ==========\n";

    testConstructor();
    testAssignment();
    testOperators();
    testCompoundOperators();
    testSubscript();

    testLength();
    testDirection();

    testDot();
    testCross();

    testFuzzy();
    testZero();

    testFiniteAndNaN();

    testMoveTowards();

    testStaticVectors();

    std::cout << "==================================\n";
    std::cout << "ALL TESTS PASSED!\n";

    return 0;
}
