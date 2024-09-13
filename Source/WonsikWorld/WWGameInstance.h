// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IOCPClient.h"
#include "WonsikWorldClientProxy.h"
#include "WonsikWorldClientStub.h"
#include "WWEnum.h"
#include "WWVector2D.h"
#include <atomic>
#include "WWGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class WONSIKWORLD_API UWWGameInstance : public UGameInstance, public IOCPClient, public WonsikWorldClientProxy, public WonsikWorldClientStub
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	UWWGameInstance();
	virtual ~UWWGameInstance();
	
	//Network
protected:
	virtual void OnConnect() override;
	virtual void OnConnectFail() override;
	virtual void OnDisconnect() override;
	virtual void OnRecv(CRecvBuffer& buf) override;
	virtual void Run();
public:
	bool _onConnecting = false;
	
	UPROPERTY(BlueprintReadOnly)
	bool bConnectFail = false;

	UPROPERTY(BlueprintReadOnly)
	bool bNickNameDuplication = false;

	std::atomic<bool> bQuitGame = false;

private:
	short _instanceMapID= MAP_ID_LOBBY;
	LONG64 _myPlayerID;
	WString _myNickName;
public:
	bool ConncectToServer(const String& ip);
	WString GetMyNickName();
	void SetMyNickName(const WString& NickName);
	short GetInstanceMapID();
	LONG64 GetMyPlayerID();
public:
	class WWJobQueue* GJobQueue;

	//RPC
protected:
	bool IsGameDestroyed = false;
	virtual void ProcEnterGame_SC(short enterGameResult, LONG64 playerID) override;
	virtual void ProcCreateMyCharacter_SC(short mapID, WWVector2D& dirVec, WWVector2D& location) override;
	virtual void ProcCreateOtherCharacter_SC(short mapID, LONG64 playerID, WString& nickName, WWVector2D& dirVec, WWVector2D& location) override;
	virtual void ProcDeleteCharacter_SC(short mapID, LONG64 palyerID) override;
	virtual void ProcChangeMap_SC(short beforeMapID, short afterMapID) override;
	virtual void ProcSendChatMessage_SC(short mapID, LONG64 playerID, WString& chatMessage) override;
	virtual void ProcMoveMyCharacter_SC(short mapID, Vector<WWVector2D>& destinations) override;
	virtual void ProcMoveOtherCharacter_SC(short mapID, LONG64 playerID, Vector<WWVector2D>& destinations) override;

private:
};
