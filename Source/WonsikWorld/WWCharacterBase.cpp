// Fill out your copyright notice in the Description page of Project Settings.


#include "WWCharacterBase.h"
#include "WWEnum.h"
#include "MathUtil.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AWWCharacterBase::AWWCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWWCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MOVE_SPEED;
	_moveSpeed = MOVE_SPEED;
}

// Called every frame
void AWWCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

// Called to bind functionality to input
void AWWCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AWWCharacterBase::Stop()
{
	_destinations.clear();
}

void AWWCharacterBase::SetDestinaions(List<FVector>& destinations)
{
    if (destinations.empty())
    {
        //길을 못찾았을 때 아무것도 서버에서 보내지 않치만 나중에 바뀌었을때를 대비해서 만들어둠
		return;
    }
	//좌표차이가 너무 났을때
	FVector serverStartLocation = destinations.front();
	destinations.pop_front();
	FVector clientCurLocation = GetActorLocation();
	FVector diffVector = serverStartLocation - clientCurLocation;
	diffVector.Z = 0;
	if (diffVector.Length() > GRID_CELL_SIZE/2)
	{
		TeleportTo(serverStartLocation, diffVector.Rotation());
	}
    _destinations = destinations;
}

void AWWCharacterBase::Move(float deltaTime)
{
	if (_destinations.size() > 0)
	{
		FVector destination = _destinations.front();
		FVector curLocation = GetActorLocation();
		destination.Z = curLocation.Z;
		FVector dirVec = destination - curLocation;
		//도착했는지 확인
		if (IsSameGrid(destination.X, destination.Y, curLocation.X, curLocation.Y, GRID_CELL_SIZE) == true && dirVec.Length() < CLOSE_DISTANCE)
		{
			_destinations.pop_front();
		}

		//UE_LOG(LogTemp, Log, TEXT("destination: x: %f y: %f z: %f"), destination.X, destination.Y, destination.Z);
		//UE_LOG(LogTemp, Log, TEXT("curlocation: x: %f y: %f z: %f"), curLocation.X, curLocation.Y, curLocation.Z);
		
		if (_destinations.size() > 0)
		{
			destination= _destinations.front();
			destination.Z = curLocation.Z;
			dirVec = destination - curLocation;
			dirVec.Normalize();
			//dirVec로 이동
			SetActorRotation(dirVec.Rotation());
			AddMovementInput(dirVec);
			GetCharacterMovement()->Velocity = dirVec * _moveSpeed;
		}
	}
}
