#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__


#include <cstdint>
#include <map>
#include <memory>

class Scene;

class SceneManager
{
public:
    using SceneMap = std::map<uint64_t, std::shared_ptr<Scene>>;    //唯一房间号映射到场景 


public:
    SceneManager();
    ~SceneManager();    //对所有运行的实例进行释放

    bool Init(bool mainLand);
    bool Uninit();

public:
    bool CreateScene(uint32_t mapId, uint64_t roomId);

private:
    uint64_t m_baseRoomId;   //唯一房间号
};






#endif 