// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TTGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "TTItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class THEWISE_API ATTItemChest : public AActor, public ITTGameplayInterface
{
	GENERATED_BODY()
	
	void Interact_Implementation(APawn* InstigatorPawn);
	
public:	
	// Sets default values for this actor's properties
	ATTItemChest();

	UPROPERTY(EditAnywhere)
	float TargetRoll;
	

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
