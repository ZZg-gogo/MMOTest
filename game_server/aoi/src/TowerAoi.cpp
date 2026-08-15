#include "TowerAoi.h"

#include <cassert>
#include <cmath>


//有单位进入这个格子
bool Tower::AddMarker(Marker* marker)
{
	assert(marker->_nextNode == nullptr);
	assert(marker->_preNode == nullptr);

	if (!m_markers)
	{
		m_markers = marker;
	}
	else
	{
		m_markers->_preNode = marker;
		marker->_nextNode = m_markers;
		m_markers = marker;
	}

	return true;
}

//有单位离开这个格子
bool Tower::RemoveMarker(Marker* marker)
{
	if (!marker)
		return false;

	// 不是当前 Tower 的节点

	if (marker->_preNode)
	{
		marker->_preNode->_nextNode = marker->_nextNode;
	}
	else
	{
		// marker 是头节点
		assert(m_markers == marker);
		m_markers = marker->_nextNode;
	}

	if (marker->_nextNode)
	{
		marker->_nextNode->_preNode = marker->_preNode;
	}

	marker->_nextNode = nullptr;
	marker->_preNode = nullptr;

	return true;
}

//有单位要观察这个格子了
bool Tower::AddWatcher(Watcher* watcher)
{
	auto result = m_watchers.insert({ watcher->_guid, watcher });
	return result.second;
}

//有单位不在观察这个格子
bool Tower::RemoveWathcer(Watcher* watcher)
{
	auto resutlt = m_watchers.erase(watcher->_guid);
	return resutlt > 0;
}





//地图的构造函数
TowerAoi::TowerAoi(u_int32_t spaceId, double width, double height, double towerWidth, double towerHeight) :
	m_spaceId(spaceId), m_width(width), m_height(height), 
	m_halfWidth(width *0.5 ), m_halfHeight(height * 0.5),
	m_towerInverseWidth(1.0 / towerWidth), m_towerInverseHeight(1.0 / towerHeight)
{
	//算出X和Y方向上需要多少个格子
	m_towerSizeX = std::ceil(m_width * m_towerInverseWidth);
	m_towerSizeY = std::ceil(m_height * m_towerInverseHeight);
	int towerCount = m_towerSizeX * m_towerSizeY;

	m_towers = new Tower * [towerCount];

	for (int i = 0; i < towerCount; i++)
	{
		m_towers[i] = new Tower{i};
	}
}

TowerAoi::~TowerAoi()
{
	if (m_towers)
	{
		int towerCount = m_towerSizeX * m_towerSizeY;
		for (int i = 0; i < towerCount; i++)
		{
			delete m_towers[i];
		}

		delete[] m_towers;
		m_towers = nullptr;

	}
}


//单位进入地图 单位id guid 位置 pos 视野范围 range
void TowerAoi::OnObjectEnter(u_int64_t guid, const Vec2& pos, u_int32_t range)
{
	OnEnter(guid, pos, range);
}


void TowerAoi::OnEnter(u_int64_t guid, const Vec2& pos, u_int32_t range)
{
	//一个单位 就是一个marker
	AddMarker(guid, pos);

	if (range >= 1) AddWatcher(guid, pos, range);
}


//玩家进入地图 如果有视野的话 那么就调用这个函数
bool TowerAoi::AddWatcher(u_int64_t guid, const Vec2& pos, u_int32_t range)
{
	if (m_watchers.find(guid) != m_watchers.end())
	{
		std::cout << "TowerAoi::AddWatcher already Add guid = " << guid << "\n";
		return false;
	}



	TowerIndexList towerIndexs;
	Watcher* watcher = new Watcher{ guid , pos, range };
	//计算这个视野范围能覆盖哪些格子的索引数组
	if (!ConvertToTowerIndexList(pos, range, watcher->_watchTowerIndexs))
	{
		std::cout << "TowerAoi::AddWatcher ConvertToTowerIndexList fail  guid = " << guid << " range="<< range << "\n";
		delete watcher;
		return false;
	}

	

	m_watchers[guid] = watcher;

	//遍历那些自己视野范围内的格子 把自己注册到这些格子的watcher里面去
	//遍历那些格子的marker对象，判断这些marker对象是否在自己的视野范围内，如果在，就把这些marker对象的guid添加到自己的可见集合里面去
	OnWatcherAdd(watcher, watcher->_watchTowerIndexs);

	return true;
}


//当新添加一个Watcher的时候调用
void TowerAoi::OnWatcherAdd(Watcher* watcher, TowerIndexList& watchTower)
{
	for (auto towerIndex : watchTower)
	{
		Tower* tower = m_towers[towerIndex];
		tower->AddWatcher(watcher);	//这个watcher可以观察到这个格子
		//搜集这些格子里面 我能看到的单位
		Marker* marker = tower->GetMarkers();

		for (; nullptr != marker; marker = marker->_nextNode)
		{
			if (marker->_guid != watcher->_guid && watcher->IsMarkerVisible(marker))
			{
				watcher->AddVisableMarker(marker);
			}
		}
	}
}


//根据单位的位置还有他的视野 计算出来他可以看到的格子
bool TowerAoi::ConvertToTowerIndexList(const Vec2& pos, u_int32_t range, TowerIndexList& towerIndexs) const
{
	if (range < 1)
	{
		return false;
	}

	//玩家传入的位置是世界坐标
	double fx = pos.m_x + m_halfWidth;
	double fy = pos.m_y + m_halfHeight;

	if (fx < 0 || fy < 0 || fx >= m_width || fy >= m_height)
	{
		return false;
	}

	int tx = std::floor(fx * m_towerInverseWidth);
	int ty = std::floor(fy * m_towerInverseHeight);

	//计算自己的视野可以覆盖格子的大小
	int rx  = std::ceil(range * m_towerInverseWidth);
	int ry = std::ceil(range * m_towerInverseHeight);

	//如果视野范围大于了当前格子的横坐标 那么肯定是x是0的格子都可以看到
	int sx = rx > tx ? 0 : tx - rx;
	int sy = ry > ty ? 0 : ty - ry;

	int ex = rx + tx;
	int ey = ry + ty;

	if (ex >= m_towerSizeX) ex = m_towerSizeX - 1;
	if (ey >= m_towerSizeY) ey = m_towerSizeY - 1;
	//上面就是计算出来循环的起始

	for (int y = sy; y <= ey; y++)
	{
		for (int x = sx; x <= ex; x++)
		{
			towerIndexs.push_back(x + y * m_towerSizeX);
		}
	}

	return true;
}

//把一个位置转化成为格子的索引
bool TowerAoi::ConvertToTowerIndex(const Vec2& pos, int& towerIndex) const
{
	double fx = pos.m_x + m_halfWidth;
	double fy = pos.m_y + m_halfHeight;

	if (fx < 0 || fy < 0 || fx >= m_width || fy >= m_height) 
	{
		return false;
	}

	int tx = std::floor(fx * m_towerInverseWidth);
	int ty = std::floor(fy * m_towerInverseHeight);

	towerIndex = ty * m_towerSizeX + tx;
	return true;
}

//添加一个被观察对象
bool TowerAoi::AddMarker(u_int64_t guid, const Vec2& pos)
{
	int towerIndex = -1;
	if (!ConvertToTowerIndex(pos, towerIndex))
	{
		assert(false);
		return false;
	}

	if (m_markers.find(guid) != m_markers.end())
	{
		std::cout << " TowerAoi::AddMarker already Add Guid = " << guid << "\n";
		return false;
	}

	Marker* marker = new Marker{ guid, pos, towerIndex };
	m_markers[guid] = marker;

	//把这个marker对象添加到对应的格子里面去
	Tower* tower = m_towers[towerIndex];

	tower->AddMarker(marker);

	OnMarkerAdd(marker, tower);

	return true;
}


//当一个Marker被添加到Tower里面的时候调用
void TowerAoi::OnMarkerAdd(Marker* marker, Tower* tower)
{
	//遍历能看到这个格子的所有Watcher对象
	//如果某个Watcher对象的视野能看到这个Marker 就添加进去
	for (auto it : tower->GetWatchers())
	{
		Watcher* watcher = it.second;

		if (watcher->_guid != marker->_guid && watcher->IsMarkerVisible(marker))
		{
			watcher->AddVisableMarker(marker);
		}
	}

}


// 处理对象移动
void TowerAoi::OnObjectMove(u_int64_t guid, const Vec2& pos)
{
	// 更新 Marker：
	// “我移动了”，影响其他 Watcher 是否还能看到我
	// 解决：别人怎么看我
	UpdateMarker(guid, pos);

	// 更新 Watcher：
	// “我的观察位置移动了”，影响我现在能看到哪些 Marker
	// 解决：我怎么看别人
	UpdateWatcher(guid, pos);
}



bool TowerAoi::UpdateMarker(u_int64_t guid, const Vec2& pos)
{
	if (m_markers.find(guid) == m_markers.end())
	{
		return false;
	}

	Marker* marker = m_markers[guid];
	//旧的宫格索引
	int oldTowerIndex = marker->_towerIndex;

	int newTowerIndex = -1;
	if (!ConvertToTowerIndex(pos, newTowerIndex))
	{
		std::cout << "TowerAoi::UpdateMarker cant ConvertToTowerIndex guid=" << guid << "\n";
		return false;
	}

	//更新位置更新宫格索引
	marker->_towerIndex = newTowerIndex;
	marker->_pos = pos;

	Tower* oldTower = m_towers[oldTowerIndex];
	Tower* newTower = m_towers[newTowerIndex];

	//发生了宫格的跃迁的话 那么就需要更新Tower的Marker
	if (oldTowerIndex != newTowerIndex)
	{
		oldTower->RemoveMarker(marker);
		newTower->AddMarker(marker);
	}

	OnMarkerUpdate(marker, oldTower, newTower);

	return true;
}



void TowerAoi::OnMarkerUpdate(Marker* marker, Tower* oldTower, Tower* newTower)
{
	const WatcherMap& oldWatchMap = oldTower->GetWatchers();
	const WatcherMap& newWatchMap = newTower->GetWatchers();

	auto oldIndex = oldWatchMap.begin();
	auto oldIndexEnd = oldWatchMap.end();

	auto newIndex = newWatchMap.begin();
	auto newIndexEnd = newWatchMap.end();

	// 两个 map 都还没有遍历结束
	while (oldIndex != oldIndexEnd && newIndex != newIndexEnd)
	{
		if (oldIndex->first < newIndex->first)
		{
			// 这个 Watcher 只观察旧 Tower
			// Marker 已经移动到它无法观察的新 Tower
			// 如果之前能看到 Marker，现在需要移除
			Watcher* watcher = oldIndex->second;

			if (watcher->HasVisableMarker(marker))
			{
				watcher->RemoveVisableMarker(marker);
			}

			++oldIndex;
		}
		else if (oldIndex->first > newIndex->first)
		{
			// 这个 Watcher 只观察新 Tower
			// Marker 新进入它观察范围内
			Watcher* watcher = newIndex->second;

			if (watcher->_guid != marker->_guid &&
				watcher->IsMarkerVisible(marker))
			{
				watcher->AddVisableMarker(marker);
			}

			++newIndex;
		}
		else
		{
			// 这个 Watcher 同时观察旧 Tower 和新 Tower
			// Marker 移动后需要重新判断精确距离
			Watcher* watcher = oldIndex->second;

			if (watcher->_guid != marker->_guid)
			{
				bool oldVisible = watcher->HasVisableMarker(marker);
				bool newVisible = watcher->IsMarkerVisible(marker);

				if (oldVisible && !newVisible)
				{
					watcher->RemoveVisableMarker(marker);
				}
				else if (!oldVisible && newVisible)
				{
					watcher->AddVisableMarker(marker);
				}
			}

			++oldIndex;
			++newIndex;
		}
	}

	// 剩余 OldTower Watcher
	while (oldIndex != oldIndexEnd)
	{
		Watcher* watcher = oldIndex->second;

		if (watcher->HasVisableMarker(marker))
		{
			watcher->RemoveVisableMarker(marker);
		}

		++oldIndex;
	}

	// 剩余 NewTower Watcher
	while (newIndex != newIndexEnd)
	{
		Watcher* watcher = newIndex->second;

		if (watcher->_guid != marker->_guid &&
			watcher->IsMarkerVisible(marker))
		{
			watcher->AddVisableMarker(marker);
		}

		++newIndex;
	}
}



//玩家移动了 更新自己的Watcher
bool TowerAoi::UpdateWatcher(u_int64_t guid, const Vec2& pos)
{
	if (m_watchers.find(guid) == m_watchers.end())
	{
		return false;
	}

	Watcher* watcher = m_watchers[guid];

	TowerIndexList newTowerIndexList;	//新的可见宫格的计算
	if (!ConvertToTowerIndexList(pos, watcher->_range, newTowerIndexList))
	{
		return false;
	}
	//根据新旧TowerIndexList 计算出来新增/删除/更新的tower
	TowerDifference(watcher->_watchTowerIndexs, newTowerIndexList, m_adTowers, m_rmTowers, m_upTowers);

	watcher->_watchTowerIndexs = std::move(newTowerIndexList);
	watcher->_pos = pos;

	OnWatcherUpdate(watcher, m_adTowers, m_rmTowers, m_upTowers);

	return true;
}

void TowerAoi::OnWatcherUpdate(
	Watcher* watcher,
	TowerIndexList& addTower,
	TowerIndexList& rmTower,
	TowerIndexList& updateTowner)
{
	// 1. 新增观察的 Tower
	for (auto index : addTower)
	{
		Tower* tower = m_towers[index];

		// 我开始观察这个 Tower
		tower->AddWatcher(watcher);

		// 检查这个 Tower 里面的所有 Marker
		Marker* marker = tower->GetMarkers();

		for (; marker != nullptr; marker = marker->_nextNode)
		{
			if (watcher->_guid != marker->_guid &&
				watcher->IsMarkerVisible(marker))
			{
				watcher->AddVisableMarker(marker);
			}
		}
	}


	// 2. 删除观察的 Tower
	for (auto index : rmTower)
	{
		Tower* tower = m_towers[index];

		// 我不再观察这个 Tower
		tower->RemoveWathcer(watcher);

		// 这个 Tower 里的 Marker 都不再是我的观察候选
		Marker* marker = tower->GetMarkers();

		for (; marker != nullptr; marker = marker->_nextNode)
		{
			if (watcher->HasVisableMarker(marker))
			{
				watcher->RemoveVisableMarker(marker);
			}
		}
	}


	// 3. 继续观察的 Tower
	for (auto index : updateTowner)
	{
		Tower* tower = m_towers[index];

		// Tower 没变，但是 Watcher 的位置变了
		// 所以里面的 Marker 可能从：
		//
		// 看得见 -> 看不见
		// 看不见 -> 看得见
		//
		Marker* marker = tower->GetMarkers();

		for (; marker != nullptr; marker = marker->_nextNode)
		{
			bool oldVisible = watcher->HasVisableMarker(marker);
			bool newVisible = watcher->IsMarkerVisible(marker);

			// 原来能看到，现在看不到了
			if (oldVisible && !newVisible)
			{
				watcher->RemoveVisableMarker(marker);
			}
			// 原来看不到，现在能看到了
			else if (watcher->_guid != marker->_guid &&
				!oldVisible && newVisible)
			{
				watcher->AddVisableMarker(marker);
			}
		}
	}
}


// 根据新旧 TowerIndexList 计算新增、删除、继续观察的 Tower
void TowerAoi::TowerDifference(
	const TowerIndexList& oldTowerIndexs,
	const TowerIndexList& newTowerIndexs,
	TowerIndexList& addTower,
	TowerIndexList& rmTower,
	TowerIndexList& updateTower)
{
	addTower.clear();
	rmTower.clear();
	updateTower.clear();

	auto oldIndex = oldTowerIndexs.begin();
	auto oldEnd = oldTowerIndexs.end();

	auto newIndex = newTowerIndexs.begin();
	auto newEnd = newTowerIndexs.end();

	// 两边都有数据，进行双指针比较
	for (; oldIndex != oldEnd && newIndex != newEnd;)
	{
		if (*oldIndex < *newIndex)
		{
			// 旧的有，新的没有
			// 不再观察这个 Tower
			rmTower.push_back(*oldIndex);
			++oldIndex;
		}
		else if (*oldIndex > *newIndex)
		{
			// 新的有，旧的没有
			// 新增观察这个 Tower
			addTower.push_back(*newIndex);
			++newIndex;
		}
		else
		{
			// 新旧都有
			// 继续观察这个 Tower
			updateTower.push_back(*oldIndex);

			++oldIndex;
			++newIndex;
		}
	}

	// 旧 Tower 剩余的全部删除
	for (; oldIndex != oldEnd; ++oldIndex)
	{
		rmTower.push_back(*oldIndex);
	}

	// 新 Tower 剩余的全部新增
	for (; newIndex != newEnd; ++newIndex)
	{
		addTower.push_back(*newIndex);
	}
}


void TowerAoi::OnObjectLeave(u_int64_t guid)
{
	OnLeave(guid);
}

void TowerAoi::OnLeave(u_int64_t guid)
{
	RemoveMarker(guid);
	RemoveWatcher(guid);
}



bool TowerAoi::RemoveMarker(u_int64_t guid)
{
	auto it = m_markers.find(guid);
	if (it == m_markers.end())
	{
		return false;
	}

	Marker* marker = it->second;

	Tower* tower = m_towers[marker->_towerIndex];

	// 先通知所有能看到我的 Watcher
	OnMarkerRemove(marker, tower);

	// 再从 Tower 中移除
	tower->RemoveMarker(marker);

	// 再从全局容器中移除
	m_markers.erase(it);

	delete marker;

	return true;
}

//marker被移除了 要通知所有能看到他的watcher
void TowerAoi::OnMarkerRemove(Marker* marker, Tower* tower)
{
	const WatcherMap& watchMap = tower->GetWatchers();


	for (auto watcherPair : watchMap)
	{
		Watcher* watcher = watcherPair.second;
		if (watcher->HasVisableMarker(marker))
		{
			watcher->RemoveVisableMarker(marker);
		}
	}
}

bool TowerAoi::RemoveWatcher(u_int64_t guid)
{
	auto it = m_watchers.find(guid);

	if (it == m_watchers.end())
	{
		return false;
	}

	Watcher* watcher = it->second;

	// 从所有观察的 Tower 中注销
	OnWatcherRemove(watcher, watcher->_watchTowerIndexs);

	// 从全局 WatcherMap 中删除
	m_watchers.erase(it);

	delete watcher;

	return true;
}


void TowerAoi::OnWatcherRemove(Watcher* watcher, TowerIndexList& watchTower)
{
	for (auto index : watchTower)
	{
		Tower* tower = m_towers[index];
		tower->RemoveWathcer(watcher);

		Marker* marker = tower->GetMarkers();

		for (; marker != nullptr; marker = marker->_nextNode) 
		{
			if (watcher->HasVisableMarker(marker)) 
			{
				watcher->RemoveVisableMarker(marker);
			}
		}
	}
}