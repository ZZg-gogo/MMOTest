#include <Logger.h>


#include <cstdint>

#include <Buffer/ByteConverter.h>








int main()
{
    uint16_t num = 0x0100;
    LOGGER_INFO("numnumnumnumnum = {}", num);

    for (std::size_t i = 0; i < 2; i++)
    {
        uint8_t * p = reinterpret_cast<uint8_t*>(&num);
        p = p+i;

        LOGGER_INFO("ppppp num = {}", *p);
    }
    


    uint16_t num1 = 1;
    EndianConvert(num1);

    LOGGER_INFO("num1num1num1 = {}", num1);

    EndianConvertReverse(num1);
    LOGGER_INFO("num1num1num1 = {}", num1);


    //EndianConvert(&num1);
    EndianConvertPtr<uint16_t>(&num);
    LOGGER_INFO("numnumnumnumnum = {}", num);
    EndianConvertReversePtr<uint16_t>(&num);
    LOGGER_INFO("numnumnumnumnum = {}", num);
    return 0;
}







