// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Container/MyStlContainer.h"
#include "WWCharacterBase.generated.h"

UCLASS()
class WONSIKWORLD_API AWWCharacterBase : public ACharacter
{
	GENERATED_BODY()

private:
	int _moveSpeed;
	List<FVector> _destinations;
public:
	// Sets default values for this character's properties
	AWWCharacterBase();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	void SetDestinaions( List<FVector>& destinations);
	void Move(float deltaTime);
	void Stop();
};
