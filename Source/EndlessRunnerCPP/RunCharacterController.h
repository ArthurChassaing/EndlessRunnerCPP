// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RunCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERCPP_API ARunCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	ARunCharacterController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Ref")
	class ARunCharacter *RunCharacter;
	
	void MoveRight(float scale);
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
};
