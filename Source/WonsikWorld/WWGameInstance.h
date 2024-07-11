// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IOCPClient.h"
#include "WonsikWorldClientProxy.h"
#include "WonsikWorldStub.h"
#include "WWJobManager.h"
#include "WWGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class WONSIKWORLD_API UWWGameInstance : public UGameInstance, public IOCPClient, public WonsikWorldClientProxy, public WonsikWorldStub
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	UWWGameInstance();
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AWWJobManager> WWJobManager;
	//Network
protected:

	SessionInfo _sessionInfo;
	virtual void OnDisconnect(SessionInfo sessionInfo);
	virtual void OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void Run();
public:
	UPROPERTY(BlueprintReadOnly)
	bool ConnectSuccess = true;
	//RPC
protected:
	
	
	UFUNCTION(BlueprintCallable, Category = "Chat")
	void SendChatMessageOnServer(FString ChatMessage);
	virtual void ProcSendChatMessage(SessionInfo sessionInfo,String id, String chatMessage) override;
};
