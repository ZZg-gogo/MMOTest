#ifndef __TOWER_AOI_H__
#define __TOWER_AOI_H__








#include "Vec2.h"
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <string>

//任何一个对象 进入到地图里面都是作为一个被观察者
struct Marker
{
	u_int64_t _guid;	//这个单位的唯一id
	Vec2 _pos;				//这个单位的位置
	//这个格子里面的所有的单位 会被链表串连起来
	Marker* _nextNode;			
	Marker* _preNode;

	int _towerIndex;	//这个Marker所在的格子索引


	Marker(u_int64_t guid, const Vec2& pos, int towerIndex) :
		_guid(guid), _pos(pos), _nextNode(nullptr), _preNode(nullptr), _towerIndex(towerIndex) {
	}
};



typedef std::vector<int> TowerIndexList;

//当一个单位他具有视野的时候 他就会作为一个观察者
struct Watcher
{
	u_int64_t _guid;		//这个单位的唯一id
	Vec2 _pos;					//这个单位的位置
	u_int32_t _range;		//视野范围
	u_int32_t _rangeSq;		//视野范围的平方

	TowerIndexList _watchTowerIndexs;	//这个watcher对象正在观察的格子集合(也就是视野覆盖了哪些格子)

	std::set<u_int64_t> _visableMarkerSet;	//我当前这个watcher看到的Marker set
	

	void PrintInfo()
	{
		std::string info = "Visible: ";

		for (auto id : _visableMarkerSet)
		{
			info += std::to_string(id);
			info += " ";
		}

		std::cout << "Watcher guid=" << _guid << " _visableMarkerSet = " << info << "\n";
	}

	Watcher(u_int64_t guid, const Vec2& pos, u_int32_t range) :
		_guid(guid), _pos(pos), _range(range), _rangeSq(range* range) {
	}

	//插入一个可见目标
	void AddVisableMarker(Marker* marker)
	{
		_visableMarkerSet.insert(marker->_guid);
	}

	//移除一个可见目标
	void RemoveVisableMarker(Marker* marker)
	{
		_visableMarkerSet.erase(marker->_guid);
	}

	//是否已经有了这个目标
	bool HasVisableMarker(Marker* marker) const
	{
		return _visableMarkerSet.find(marker->_guid) != _visableMarkerSet.end();
	}

	//这个目标是否在我的视野范围之内
	bool IsMarkerVisible(Marker* marker) const
	{
		Vec2 dist = marker->_pos - _pos;

		return dist.lenSqr() <= _rangeSq;
	}
};


typedef std::map<u_int64_t, Marker*> MarkerMap;
typedef std::map<u_int64_t, Watcher*> WatcherMap;



//格子 记录着自己格子里面的Marker  还有正在观察这个格子的Watcher
class Tower
{
public:
	Tower(int towerIndex) : m_towerIndex(towerIndex), m_markers(nullptr) {}
	~Tower() {}

	bool AddMarker(Marker* marker);	//有单位进入这个格子
	bool RemoveMarker(Marker* marker);	//有单位离开这个格子

	bool AddWatcher(Watcher* watcher);	//有单位正在观察这个格子
	bool RemoveWathcer(Watcher* watcher);	//有单位不在观察这个格子

	Marker* GetMarkers() const { return m_markers; }
	const WatcherMap& GetWatchers() const { return m_watchers; }

private:
	int m_towerIndex;
	Marker* m_markers;
	WatcherMap m_watchers;
};





class TowerAoi
{

public:
	//地图的构造函数 地图id 地图宽度 地图高度 格子的宽度和高度
	TowerAoi(u_int32_t spaceId, double width, double height, double towerWidth, double towerHeight);
	~TowerAoi();


	//单位进入地图 单位id guid 位置 pos(这个是相对于地图中心点的偏移) 视野范围 range
	void OnObjectEnter(u_int64_t guid, const Vec2& pos, u_int32_t range);
	void OnObjectLeave(u_int64_t guid);
	//处理玩家的移动逻辑
	void OnObjectMove(u_int64_t guid, const Vec2& pos);

	void PrintWatchers() const
	{
		for (const auto& it : m_watchers)
		{
			it.second->PrintInfo();
		}
	}

	Watcher* GetWatcher(u_int64_t guid);
	Marker* GetMarker(u_int64_t guid);
private:
	void OnEnter(u_int64_t guid, const Vec2& pos, u_int32_t range);
	void OnLeave(u_int64_t guid);
	//把一个位置转化成为格子的索引
	bool ConvertToTowerIndex(const Vec2& pos, int& towerIndex) const;
	//根据单位的位置还有他的视野 计算出来他可以看到的格子
	bool ConvertToTowerIndexList(const Vec2& pos, u_int32_t range, TowerIndexList& towerIndexs) const;

	//单位进入到格子里面就是一个Marker
	bool AddMarker(u_int64_t guid, const Vec2& pos);

	//当一个Marker被添加到Tower里面的时候调用
	void OnMarkerAdd(Marker* marker, Tower* tower);

	//玩家进入地图 如果有视野的话 那么就调用这个函数
	bool AddWatcher(u_int64_t guid, const Vec2& pos, u_int32_t range);
	//当新添加一个Watcher的时候调用
	void OnWatcherAdd(Watcher* watcher, TowerIndexList& watchTower);

	//玩家移动了 然后更新自己的Marker
	bool UpdateMarker(u_int64_t guid, const Vec2& pos);
	void OnMarkerUpdate(Marker* marker, Tower* oldTower, Tower* newTower);


	//玩家移动了 更新自己的Watcher
	bool UpdateWatcher(u_int64_t guid, const Vec2& pos);
	void OnWatcherUpdate(Watcher* watcher, TowerIndexList& addTower, TowerIndexList& rmTower, TowerIndexList& updateTowner);
	//根据新旧TowerIndexList 计算出来新增/删除/更新的tower
	void TowerDifference(const TowerIndexList& oldTowerIndexs, const TowerIndexList& newTowerIndexs, TowerIndexList& addTower, TowerIndexList& rmTower, TowerIndexList& updateTowner);

	//移除一个Marker
	bool RemoveMarker(u_int64_t guid);
	void OnMarkerRemove(Marker* marker, Tower* tower);

	//移除一个Watcher
	bool RemoveWatcher(u_int64_t guid);
	void OnWatcherRemove(Watcher* watcher, TowerIndexList& watchTower);
private:
	u_int32_t m_spaceId;		//地图ID
	double m_width;			//地图宽度，以像素为单位
	double m_height;			//地图高度，以像素为单位

	double m_halfWidth;		//地图宽度的一半
	double m_halfHeight;		//地图高度的一半

	double  m_towerInverseWidth;	//格子宽度的倒数
	double  m_towerInverseHeight;	//格子高度的倒数


	int m_towerSizeX;		//X方向上有多少个格子
	int m_towerSizeY;		//Y方向上有多少个格子

	Tower** m_towers;		//格子集合

	MarkerMap m_markers;	//存储着这个地图上所有的makers
	WatcherMap m_watchers;	//存储着这个地图上所有的watcher

	//用来计算移动前后 watcher差异的临时变量
	TowerIndexList m_adTowers;     
	TowerIndexList m_rmTowers;     
	TowerIndexList m_upTowers;     

};





#endif