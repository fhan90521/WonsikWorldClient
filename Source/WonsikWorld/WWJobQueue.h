// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Job/JobQueue.h"
/**
 * 
 */
class WONSIKWORLD_API WWJobQueue: public JobQueue
{
public:
	WWJobQueue();
	~WWJobQueue();
	
	UPROPERTY()
	TObjectPtr<class AWWPlayerController> _wwPlayerController;

public:
	//Job

	void QuitGame();
	void ChangeMapSC(short beforeMapID, short afterMapID);
	void CreateMyCharacterSC(short mapID, FVector& dirVec, FVector& location);
	void CreateOtherCharacterSC(short mapID, LONG64 playerID, FString& nickName, FVector& dirVec, FVector& location);
	virtual void DeleteCharacterSC(short mapID, LONG64 playerID);
	void SendChatMessageSC(short mapID, LONG64 playerID, FString& chatMessage);
	void MoveMyCharacterSC(short mapID, List<FVector>& destinations);
	void MoveOtherCharacterSC(short mapID, LONG64 playerID, List<FVector>& destinations);
};
