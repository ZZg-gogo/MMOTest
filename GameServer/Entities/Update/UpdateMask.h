#ifndef __UPDATE_MASK_H__
#define __UPDATE_MASK_H__

#include <cstdint>
#include <cstring>


//一个属性字段 占据一个byte 当byte=1的时候代表这个字段需要更新
class UpdateMask
{
public:
    using ClientUpdateMaskType = uint32_t;

    enum class UpdateMaskCount : uint32_t
    {
        //以32位为一块 将多块标记进行打包发送给客户端
        CLIENT_UPDATE_MASK_BITS = sizeof(ClientUpdateMaskType) * 8,
    };


public:
    UpdateMask() = default;
    ~UpdateMask()
    {
        delete [] m_bits;
        m_bits = nullptr;
    }

    UpdateMask(const UpdateMask& other)
    {
        setCount(other.m_fieldCount);
        std::memcpy(m_bits, other.m_bits, m_blockCount  * static_cast<uint32_t>(UpdateMaskCount::CLIENT_UPDATE_MASK_BITS));
    }

    UpdateMask& operator=(const UpdateMask& other)
    {
        if (this == &other)
        {
            return *this;
        }
        
        setCount(other.m_fieldCount);
        std::memcpy(m_bits, other.m_bits, m_blockCount  * static_cast<uint32_t>(UpdateMaskCount::CLIENT_UPDATE_MASK_BITS));
        return *this; 
    }

    UpdateMask& operator&=(const UpdateMask& other)
    {
        //二者必须count相等
        for (std::size_t i = 0; i < m_fieldCount; i++)
        {
            m_bits[i] &= other.m_bits[i];
        }
        
        return *this;
    }

    UpdateMask& operator|=(const UpdateMask& other)
    {
        //二者必须count相等
        for (std::size_t i = 0; i < m_fieldCount; i++)
        {
            m_bits[i] |= other.m_bits[i];
        }
        
        return *this;
    }

    UpdateMask operator|(UpdateMask const& right)
    {
        UpdateMask ret(*this);
        ret |= right;
        return ret;
    }


    //设置属性字段的个数
    void setCount(uint32_t count)
    {
        delete [] m_bits;

        m_fieldCount = count;
        //一个块里面记录32个属性字段的变化标记
        m_blockCount = (count + static_cast<uint32_t>(UpdateMaskCount::CLIENT_UPDATE_MASK_BITS)-1) 
            / static_cast<uint32_t>(UpdateMaskCount::CLIENT_UPDATE_MASK_BITS);


        m_bits = new uint8_t[m_blockCount * static_cast<uint32_t>(UpdateMaskCount::CLIENT_UPDATE_MASK_BITS)]{};
    }


    void setBit(uint32_t index) {m_bits[index] = 1;}
    void unSetBit(uint32_t index) {m_bits[index] = 0;}
    [[nodiscard]] bool getBit(uint32_t index) const { return m_bits[index] != 0; }
    [[nodiscard]] uint32_t getBlockCount() const {return m_blockCount;}
    [[nodiscard]] uint32_t getFieldCount() const {return m_fieldCount;}


    void clear()
    {
        if (m_bits)
        {
            std::memset(m_bits, 0, m_blockCount  * static_cast<uint32_t>(UpdateMaskCount::CLIENT_UPDATE_MASK_BITS));
        }
        
    }
private:
    uint32_t m_fieldCount{0};   //总共有多少个属性字段
    uint32_t m_blockCount{0};   //把属性字段 按照ClientUpdateMaskType为一块 m_blockCount是总块数
    uint8_t* m_bits{nullptr};
};










#endif