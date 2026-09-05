#ifndef __MESSAGE_BUFFER_H__
#define __MESSAGE_BUFFER_H__


#include <cstdint>
#include <vector>
#include <cstring>



class MessageBuffer
{
public:
    MessageBuffer() : m_buffer(4096)
    {}

    explicit MessageBuffer(std::size_t initSize)
        : m_buffer(initSize)
    {}

    MessageBuffer(const MessageBuffer& other)
        : m_wpos(other.m_wpos), m_rpos(other.m_rpos), m_buffer{other.m_buffer}
    {}

    MessageBuffer(MessageBuffer&& other)
        : m_wpos(other.m_wpos), m_rpos(other.m_rpos), m_buffer{other.move()}
    {}

public:
    void reset()
    {
        m_wpos = 0;
        m_rpos = 0;
    }

    uint8_t* getBasePoint()
    {
        return m_buffer.data();
    }

    uint8_t* getReadPoint()
    {
        return m_buffer.data()+m_rpos;
    }

    uint8_t* getWeadPoint()
    {
        return m_buffer.data()+m_wpos;
    }

    void readCompleted(std::size_t len)
    {
        m_rpos += len;
    }

    void writeCompleter(std::size_t len)
    {
        m_wpos += len;
    }

    [[nodiscard]] std::size_t getActiveSize() const 
    {
        return m_wpos - m_rpos;
    }


    [[nodiscard]] std::size_t getRemainSize() const 
    {
        
        return m_buffer.size() - m_wpos;
    }

    [[nodiscard]] std::size_t getBufferSize() const
    {
        return m_buffer.size();
    }

    std::vector<uint8_t>&& move()
    {
        m_wpos = 0;
        m_rpos = 0;
        return std::move(m_buffer);
    }

    //回收buff前面已经使用的空间
    void normalize()
    {
        if (m_rpos)
        {
            if (m_rpos != m_wpos)
            {
                std::memmove(getBasePoint(), getReadPoint(), getActiveSize());
            }
            
            m_wpos -= m_rpos;
            m_rpos = 0;
        }
    }

    void ensureFreeSpace(std::size_t len)
    {
        if (getRemainSize() >= len)
            return;

        std::size_t newSize = getBufferSize() * 3 / 2;

        // 1.5 倍扩容后如果还是装不下这次数据
        if (newSize < m_wpos + len)
            newSize = m_wpos + len;

        m_buffer.resize(newSize);
    }


    void write(const void* data, std::size_t len)
    {
        if (len)
        {
            ensureFreeSpace(len);
            std::memcpy(getWeadPoint(), data, len);
            writeCompleter(len);
        }
    }


    MessageBuffer& operator=(const MessageBuffer&  right)
    {
        if (this != &right)
        {
            m_buffer = right.m_buffer;
            m_wpos = right.m_wpos;
            m_rpos = right.m_rpos;
        }
        return *this;
    }

        MessageBuffer& operator=(MessageBuffer&& right) noexcept
    {
        if (this != &right)
        {
            m_wpos = right.m_wpos;
            m_rpos = right.m_rpos;
            m_buffer = right.move();
        }

        return *this;
    }
private:
    std::size_t m_wpos{0};
    std::size_t m_rpos{0};
    std::vector<uint8_t> m_buffer;
};



#endif 