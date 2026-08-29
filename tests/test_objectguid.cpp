#include <Object/ObjectGuid.h>
#include <iostream>
#include <assert.h>
#include <Logger.h>

int main()
{

    LOGGER_INFO("测试一下简单封装的logger {}", 10);

    ObjectGuid player1Guid =  ObjectGuid::Create<High16Guid::Player>(1);
    ObjectGuid player2Guid =  ObjectGuid::Create<High16Guid::Player>(2);
    
    assert(player1Guid.getHigh() == High16Guid::Player);
    assert(player1Guid.getEntry() == 0);
    assert(player1Guid.getCounter() == 1);


    std::cout<<"player1Guid = "<<player1Guid.toString()<<std::endl;
    std::cout<<"player2Guid = "<<player2Guid.toString()<<std::endl;
    
    if (High16Guid::Player == player1Guid.getHigh())
    {
        std::cout<<"player1Guid is a player"<<std::endl;
    }
    
    if (0 == player1Guid.getEntry())
    {
        std::cout<<"player1Guid dont have entry"<<std::endl;
    }

    std::cout<<"player1Guid getCounter="<<player1Guid.getCounter()<<std::endl;
    std::cout<<"player2Guid getCounter="<<player2Guid.getCounter()<<std::endl;
    std::cout<<"player1Guid getMaxCounter="<<player1Guid.getMaxCounter()<<std::endl;
    std::cout<<"player2Guid getMaxCounter="<<player2Guid.getMaxCounter()<<std::endl;


    if (player1Guid.isUnit())
    {
        std::cout<<"player1Guid isUnit"<<std::endl;
    }

    if (player1Guid.isPlayer())
    {
       std::cout<<"player1Guid isPlayer"<<std::endl;
    }
    
    

    ObjectGuid pet1Guid = ObjectGuid::Create<High16Guid::Pet>(1, 1);
    ObjectGuid pet2Guid = ObjectGuid::Create<High16Guid::Pet>(2, 2);
    std::cout<<"pet1Guid = "<<pet1Guid.toString()<<std::endl;
    std::cout<<"pet2Guid = "<<pet2Guid.toString()<<std::endl;
    


    LOGGER_INFO("开始测试生成counter");

    uint64_t time1s = 0xFFFFFF;
    uint64_t time2s = 0xFFFFFFFF;


    ObjectGuidGenerator<High16Guid::Pet> genPet(1);
    ObjectGuidGenerator<High16Guid::Player> genPlayer(1);

    for (std::size_t i = 1; i <= time1s; i++)
    {
        (void)genPet.Generator();
    }

    (void)genPet.Generator();
    

    for (std::size_t i = 1; i <= time2s; i++)
    {
        (void)genPlayer.Generator();
    }

    (void)genPlayer.Generator();

    return 0;
}