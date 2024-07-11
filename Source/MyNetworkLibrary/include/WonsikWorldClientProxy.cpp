#include  "WonsikWorldClientProxy.h"
#include "WonsikWorldPKT_TYPE.h"
void WonsikWorldClientProxy::SendChatMessage(SessionInfo sessionInfo, String id, String chatMessage, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_SendChatMessage << id << chatMessage;
	}
	catch(int useSize)
	{
	}
	_pClient->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void WonsikWorldClientProxy::SendChatMessage(List<SessionInfo>& sessionInfoList, String id, String chatMessage, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_SendChatMessage << id << chatMessage;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pClient->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void WonsikWorldClientProxy::HeartBeat(SessionInfo sessionInfo, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_HeartBeat;
	}
	catch(int useSize)
	{
	}
	_pClient->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void WonsikWorldClientProxy::HeartBeat(List<SessionInfo>& sessionInfoList, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_HeartBeat;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pClient->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
