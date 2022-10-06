// Fill out your copyright notice in the Description page of Project Settings.


#include "TTCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "TTInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATTCharacter::ATTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UTTInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	// Player can face towards the camera/screen
	bUseControllerRotationYaw = false;

}

void ATTCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}


// Called when the game starts or when spawned
void ATTCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Debug: Draws two arrows to visualize rotations of the player
void ATTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

// Called to bind functionality to input
void ATTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ATTCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ATTCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Primary Attack", IE_Pressed, this, &ATTCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Primary Interact", IE_Pressed, this, &ATTCharacter::PrimaryInteract);
	
	
}

void ATTCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	
	FVector HandLocation = GetMesh()->GetChildComponent(0)->GetSocketLocation("muzzle_r");
	
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void ATTCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ATTCharacter::MoveForward(float Value)
{
	FRotator ControlRota = GetControlRotation();
	ControlRota.Pitch = 0.0f;
	ControlRota.Roll = 0.0f;
	
	AddMovementInput(ControlRota.Vector(), Value);
}

void ATTCharacter::MoveRight(float Value)
{
	FRotator ControlRota = GetControlRotation();
	ControlRota.Pitch = 0.0f;
	ControlRota.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRota).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, Value);
}