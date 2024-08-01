#pragma once
#include "Room.h"
#include "MyStlContainer.h"
#include "LockGuard.h"
#include <thread>
#include "Session.h"
//��ϵǾ��ִ� Room���� ������ ��� �����ؾ���
class RoomSystem
{
private:
	SRWLOCK _srwLock;
	friend class Room;
	class IOCPServer* _pServer = nullptr;
	std::jthread* _roomUpdateThread;
	HashMap<Room::ID,SharedPtr<Room>> _rooms;
	HashMap<SessionInfo::ID, Room::ID> _sessionToRoomID;
	bool bShutDown = false;
	int _updatePeriod=15;
	int _newRoomID = 0;
	void UpdateRooms();
	void EnterRoom(SessionInfo sessionInfo,Room* beforeRoom ,int afterRoomID);
	bool ChangeRoom(SessionInfo sessionInfo, Room* beforeRoom, int afterRoomID);
public:
	void SetUpdatePeriod(int updatePeriod)
	{
		_updatePeriod = updatePeriod;
	}
	void LeaveRoomSystem(SessionInfo sessionInfo);
	bool EnterRoomSystem(SessionInfo sessionInfo, int roomID);
	RoomSystem(class IOCPServer* pServer);
	virtual ~RoomSystem();

	int RegisterRoom(const SharedPtr<Room>& pRoom);
	void DeregisterRoom(int roomID);
};