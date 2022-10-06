// Fill out your copyright notice in the Description page of Project Settings.


#include "TTItemChest.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATTItemChest::ATTItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetRoll = -110.0f;
	
}

void ATTItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(0, 0, TargetRoll));
}


// Called when the game starts or when spawned
void ATTItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATTItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

