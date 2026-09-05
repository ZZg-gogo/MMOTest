#ifndef __BYTE_CONVERTER_H__
#define __BYTE_CONVERTER_H__


#include <algorithm>
#include <cstdint>


#define BIGENDIAN 0
#define SMALLENDIAN 1

//目前我这个系统的字节序是小端
#define MY_ENDIAN 1


namespace ByteConverter
{
//对c这个字符 以及他对称的那个字符做交换
template <std::size_t size>
void converter(char* c)
{
    std::swap(*c, *(c+(size-1)));
    converter<size-2>(c+1);
}

template<>
inline void converter<0>(char *)
{}
template<>
inline void converter<1>(char *)
{}

//对数字进行大小端的转化
template<typename T> inline void apply(void* val)
{
    converter<sizeof(T)>((char*)(val));
}



}


#if MY_ENDIAN == SMALLENDIAN
//转化成小端
template <typename T> inline void EndianConvert(T& val) {}
template <typename T> inline void EndianConvertReverse(T& val) { ByteConverter::apply<T>(&val);}
template <typename T> inline void EndianConvertPtr(void* val) {}
template <typename T> inline void EndianConvertReversePtr(void* val) { ByteConverter::apply<T>(val);}
#else
template <typename T> inline void EndianConvert(T& val) {ByteConverter::apply<T>(&val);}
template <typename T> inline void EndianConvertReverse(T& val) { }
template <typename T> inline void EndianConvertPtr(void* val) {ByteConverter::apply<T>(val);}
template <typename T> inline void EndianConvertReversePtr(void* val) { }

#endif

template <typename T> inline void EndianConvert(T*);
template <typename T> inline void EndianConvertReverse(T* val);

inline void EndianConvert(uint8_t&) { }
inline void EndianConvert( int8_t &) { }
inline void EndianConvertReverse(uint8_t&) { }
inline void EndianConvertReverse( int8_t&) { }

#endif