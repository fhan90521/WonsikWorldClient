#pragma once
#include "Session.h"
#include "CRecvBuffer.h"
#include "MyStlContainer.h"
#include "WonsikWorldPKT_TYPE.h"
class WonsikWorldClientStub
{
public:
	bool PacketProcEnterGame_CS(CRecvBuffer& buf);
	virtual void ProcEnterGame_CS(WString& nickName) {}

	bool PacketProcEnterGame_SC(CRecvBuffer& buf);
	virtual void ProcEnterGame_SC(short enterGameResult, LONG64 playerID) {}

	bool PacketProcCreateMyCharacter_SC(CRecvBuffer& buf);
	virtual void ProcCreateMyCharacter_SC(short mapID, float dirX, float dirY, float locationX, float locationY) {}

	bool PacketProcCreateOtherCharacter_SC(CRecvBuffer& buf);
	virtual void ProcCreateOtherCharacter_SC(short mapID, LONG64 playerID, WString& nickName, float dirX, float dirY, float locationX, float locationY) {}

	bool PacketProcDeleteCharacter_SC(CRecvBuffer& buf);
	virtual void ProcDeleteCharacter_SC(short mapID, LONG64 playerID) {}

	bool PacketProcChangeMap_CS(CRecvBuffer& buf);
	virtual void ProcChangeMap_CS(short beforeMapID, short afterMapID) {}

	bool PacketProcChangeMap_SC(CRecvBuffer& buf);
	virtual void ProcChangeMap_SC(short beforeMapID, short afterMapID) {}

	bool PacketProcSendChatMessage_CS(CRecvBuffer& buf);
	virtual void ProcSendChatMessage_CS(short mapID, WString& chatMessage) {}

	bool PacketProcSendChatMessage_SC(CRecvBuffer& buf);
	virtual void ProcSendChatMessage_SC(short mapID, LONG64 playerID, WString& chatMessage) {}

	bool PacketProcMoveMyCharacter_CS(CRecvBuffer& buf);
	virtual void ProcMoveMyCharacter_CS(short mapID, float destinationX, float destinationY) {}

	bool PacketProcMoveMyCharacter_SC(CRecvBuffer& buf);
	virtual void ProcMoveMyCharacter_SC(short mapID, Vector<float>& destinationsX, Vector<float>& destinationsY) {}

	bool PacketProcMoveOtherCharacter_SC(CRecvBuffer& buf);
	virtual void ProcMoveOtherCharacter_SC(short mapID, LONG64 playerID, Vector<float>& destinationsX, Vector<float>& destinationsY) {}

	bool PacketProcHeartBeat_CS(CRecvBuffer& buf);
	virtual void ProcHeartBeat_CS() {}

	bool PacketProc(CRecvBuffer& buf);
};
