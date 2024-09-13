// Fill out your copyright notice in the Description page of Project Settings.


#include "WWJobQueue.h"
#include "WWPlayerController.h"
WWJobQueue::WWJobQueue()
{
}

WWJobQueue::~WWJobQueue()
{
}

void WWJobQueue::QuitGame()
{
	_wwPlayerController->QuitGame_BP();
}

void WWJobQueue::ChangeMapSC(short beforeMapID, short afterMapID)
{
	_wwPlayerController->ChangeMapSC(beforeMapID, afterMapID);
}

void WWJobQueue::CreateMyCharacterSC(short mapID, FVector& dirVec, FVector& location)
{
	_wwPlayerController->CreateMyCharacterSC(mapID, dirVec, location);
}

void WWJobQueue::CreateOtherCharacterSC(short mapID, LONG64 playerID, FString nickName, FVector& dirVec, FVector& location)
{
	_wwPlayerController->CreateOtherCharacterSC(mapID, playerID, nickName, dirVec, location);
}

void WWJobQueue::DeleteCharacterSC(short mapID, LONG64 playerID)
{
	_wwPlayerController->DeleteCharacterSC(mapID, playerID);
}

void WWJobQueue::SendChatMessageSC(short mapID, LONG64 playerID, FString chatMessage)
{
	_wwPlayerController->SendChatMessageSC(mapID, playerID, chatMessage);
}

void WWJobQueue::MoveMyCharacterSC(short mapID, List<FVector>& destinations)
{
	_wwPlayerController->MoveMyCharacterSC(mapID, destinations);
}

void WWJobQueue::MoveOtherCharacterSC(short mapID, LONG64 playerID, List<FVector>& destinations)
{
	_wwPlayerController->MoveOtherCharacterSC(mapID, playerID, destinations);
}
