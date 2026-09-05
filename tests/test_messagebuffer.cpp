#include <Buffer/MessageBuffer.h>

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

void testWriteAndRead()
{
    std::cout << "========== Write / Read ==========\n";

    MessageBuffer buffer(16);

    const char* msg = "hello";

    buffer.write(msg, 5);

    assert(buffer.getActiveSize() == 5);
    assert(buffer.getRemainSize() == 11);

    assert(std::memcmp(buffer.getReadPoint(), "hello", 5) == 0);

    buffer.readCompleted(5);

    assert(buffer.getActiveSize() == 0);

    std::cout << "[PASS] Write / Read\n";
}

void testNormalize()
{
    std::cout << "========== Normalize ==========\n";

    MessageBuffer buffer(16);

    buffer.write("abcdef", 6);

    // 读掉前 3 个字节
    buffer.readCompleted(3);

    assert(buffer.getActiveSize() == 3);
    assert(std::memcmp(buffer.getReadPoint(), "def", 3) == 0);

    // 整理
    buffer.normalize();

    assert(buffer.getActiveSize() == 3);
    assert(buffer.getReadPoint() == buffer.getBasePoint());

    assert(std::memcmp(buffer.getReadPoint(), "def", 3) == 0);

    std::cout << "[PASS] Normalize\n";
}

void testReset()
{
    std::cout << "========== Reset ==========\n";

    MessageBuffer buffer(16);

    buffer.write("hello", 5);
    assert(buffer.getActiveSize() == 5);

    buffer.reset();

    assert(buffer.getActiveSize() == 0);
    assert(buffer.getRemainSize() == 16);

    std::cout << "[PASS] Reset\n";
}

void testResize()
{
    std::cout << "========== Resize ==========\n";

    MessageBuffer buffer(4);

    const char* msg = "0123456789";

    buffer.write(msg, 10);

    assert(buffer.getActiveSize() == 10);
    assert(buffer.getBufferSize() >= 10);

    assert(std::memcmp(buffer.getReadPoint(), msg, 10) == 0);

    std::cout << "[PASS] Resize\n";
}

void testCopyConstructor()
{
    std::cout << "========== Copy Constructor ==========\n";

    MessageBuffer buffer(16);

    buffer.write("hello", 5);

    MessageBuffer copy(buffer);

    assert(copy.getActiveSize() == 5);
    assert(std::memcmp(copy.getReadPoint(), "hello", 5) == 0);

    // 修改原来的 buffer
    buffer.reset();
    buffer.write("world", 5);

    // copy 不应该受到影响
    assert(copy.getActiveSize() == 5);
    assert(std::memcmp(copy.getReadPoint(), "hello", 5) == 0);

    std::cout << "[PASS] Copy Constructor\n";
}

void testCopyAssignment()
{
    std::cout << "========== Copy Assignment ==========\n";

    MessageBuffer buffer(16);
    buffer.write("hello", 5);

    MessageBuffer copy(32);
    copy = buffer;

    assert(copy.getActiveSize() == 5);
    assert(std::memcmp(copy.getReadPoint(), "hello", 5) == 0);

    std::cout << "[PASS] Copy Assignment\n";
}

void testMoveConstructor()
{
    std::cout << "========== Move Constructor ==========\n";

    MessageBuffer buffer(16);

    buffer.write("hello", 5);

    MessageBuffer moved(std::move(buffer));

    assert(moved.getActiveSize() == 5);
    assert(std::memcmp(moved.getReadPoint(), "hello", 5) == 0);

    // 你的 move() 会把原对象的位置清零
    assert(buffer.getActiveSize() == 0);
    assert(buffer.getReadPoint() == buffer.getBasePoint());

    std::cout << "[PASS] Move Constructor\n";
}

void testMoveAssignment()
{
    std::cout << "========== Move Assignment ==========\n";

    MessageBuffer buffer(16);

    buffer.write("hello", 5);

    MessageBuffer moved(32);

    moved = std::move(buffer);

    assert(moved.getActiveSize() == 5);
    assert(std::memcmp(moved.getReadPoint(), "hello", 5) == 0);

    assert(buffer.getActiveSize() == 0);

    std::cout << "[PASS] Move Assignment\n";
}

void testReadWritePosition()
{
    std::cout << "========== Read / Write Position ==========\n";

    MessageBuffer buffer(16);

    buffer.write("abcdef", 6);

    // 当前：
    //
    // [abcdef..........]
    //  ↑      ↑
    // rpos   wpos

    assert(buffer.getActiveSize() == 6);
    assert(buffer.getRemainSize() == 10);

    buffer.readCompleted(2);

    // 当前：
    //
    // [ab cdef..........]
    //    ↑   ↑
    //   rpos wpos

    assert(buffer.getActiveSize() == 4);
    assert(std::memcmp(buffer.getReadPoint(), "cdef", 4) == 0);

    buffer.normalize();

    // 当前：
    //
    // [cdef............]
    //  ↑   ↑
    // rpos wpos

    assert(buffer.getActiveSize() == 4);
    assert(buffer.getReadPoint() == buffer.getBasePoint());
    assert(std::memcmp(buffer.getReadPoint(), "cdef", 4) == 0);

    std::cout << "[PASS] Read / Write Position\n";
}

int main()
{
    std::cout << "========== MessageBuffer Test ==========\n\n";

    testWriteAndRead();
    testNormalize();
    testReset();
    testResize();
    testCopyConstructor();
    testCopyAssignment();
    testMoveConstructor();
    testMoveAssignment();
    testReadWritePosition();

    std::cout << "\n========== ALL TESTS PASSED ==========\n";

    return 0;
}