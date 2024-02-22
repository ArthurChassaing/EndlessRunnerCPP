// Fill out your copyright notice in the Description page of Project Settings.


#include "RunCharacterController.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "RunCharacter.h"
#include "Kismet/GameplayStatics.h"


ARunCharacterController::ARunCharacterController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ARunCharacterController::BeginPlay()
{
	Super::BeginPlay();
	RunCharacter = Cast<ARunCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ARunCharacterController::MoveRight(float scale)
{
	if(RunCharacter == nullptr)
		return;
	RunCharacter->AddMovementInput(RunCharacter->GetActorRightVector() * scale);
}

void ARunCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveRight", this, &ARunCharacterController::MoveRight);
}

void ARunCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RunCharacter->AddMovementInput(RunCharacter->GetActorForwardVector());
}



