// Fill out your copyright notice in the Description page of Project Settings.


#include "RunCharacter.h"

#include "RunCharacterController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARunCharacter::ARunCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent"); // Create spring arm component
	SpringArmComponent->SetupAttachment(RootComponent); // Attach spring arm component to root component
	SpringArmComponent->TargetArmLength = 500.f; 

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent"); // Create camera component
	CameraComponent->SetupAttachment(SpringArmComponent); // Attach camera component to spring arm component
}

// Called when the game starts or when spawned
void ARunCharacter::BeginPlay()
{
	Super::BeginPlay();
	IsDead = false;

	//Listen to the event 
	this->OnDeath.AddDynamic(this, &ARunCharacter::Death);
	
}

void ARunCharacter::AddCoin()
{
	Coins++;
}

// Called every frame
void ARunCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARunCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ARunCharacter::Death()
{
	if(IsDead)
		return; //If the character is already dead, don't do anything
	
	IsDead = true;

	OnDeath.Broadcast();
	
	GetCharacterMovement()->StopMovementImmediately();
	GetMesh()->SetVisibility(false);
	DetachFromControllerPendingDestroy();
	
}

