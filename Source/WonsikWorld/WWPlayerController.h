// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStlContainer.h"
#include "GameFramework/PlayerController.h"
#include "WWPlayerController.generated.h"
/**
 * 
 */
UCLASS()
class WONSIKWORLD_API AWWPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	class WWJobQueue* GJobQueue;
public:
	AWWPlayerController() {};
	virtual void BeginPlay() override;
	void Tick(float deltaTime) override;

private:
	UPROPERTY()
	TObjectPtr<class UWWGameInstance> _wwGameInstance;

public:
	//블루 프린트 변수
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class AWWCharacterBase> MyCharacter;

	UPROPERTY(BlueprintReadWrite)
	TMap<int64, class AWWCharacterBase*> OtherCharacters;

	UPROPERTY(BlueprintReadWrite)
	FString MyFNickName;


	UFUNCTION(BlueprintImplementableEvent)
	void ShowCurMapID_BP(int mapID);
	
	UFUNCTION(BlueprintCallable)
	void QuitGame_BP();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateObstacle_BP(float x, float y);


private:
	short _pcMapID;
	int64 _myPlayerID;
	WString _myNickName;
	bool _bCanProcessJob=false;
	bool _bChangingRoom;
public:
	//Recv 
	void ChangeMapSC(short beforeMapID, short afterMapID);
	void CreateMyCharacterSC(short mapID, float dirX, float dirY, float locationX, float locationY);
	void CreateOtherCharacterSC(short mapID, LONG64 playerID, const FString& nickName, float dirX, float dirY, float locationX, float locationY);
	void DeleteCharacterSC(short mapID, LONG64 playerID);
	void SendChatMessageSC(short mapID, LONG64 playerID,const FString& chatMessage);
	void MoveMyCharacterSC(short mapID, List<FVector>& destinations);
	void MoveOtherCharacterSC(short mapID, LONG64 playerID, List<FVector>& destinations);

	UFUNCTION(BlueprintImplementableEvent, Category = "BluePrintRecv")
	void ChangeMapSC_BP(int afterMapID); 

	UFUNCTION(BlueprintImplementableEvent)
	void CreateMyCharacterSC_BP(const FVector& dirVec, const FVector& location);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateOtherCharacterSC_BP(int64 playerID,const FString& nickName, const FVector& dirVec, const FVector& location);

	UFUNCTION(BlueprintImplementableEvent)
	void DeleteCharacterSC_BP(int64 playerID);

	UFUNCTION(BlueprintImplementableEvent)
	void SendChatMessageSC_BP(int64 playerID, const FString& chatMessage);

	//Send
	UFUNCTION(BlueprintCallable)
	void EnterGameCS(const FString& serverIp, const FString& nickName);

	UFUNCTION(BlueprintCallable)
	void MoveMyCharacterCS(const FVector& destination);

	UFUNCTION(BlueprintCallable)
	void SendChatMessageCS(const FString& ChatMessage);

	UFUNCTION(BlueprintCallable)
	void ChangeMapCS();


private:
	//맵초기화
	void InitMap(const int mapResource[10][10] );
	//Tick 내부 호출 함수
	void ProcessJob();

	ULONG64 _lastHeartBeatTime;
	void HeartBeatCS();
	

};
