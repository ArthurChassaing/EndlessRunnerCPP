// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickUpDelegate);

UCLASS()
class ENDLESSRUNNERCPP_API ARunCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARunCharacter();

	UPROPERTY(BlueprintAssignable)
	FDeathDelegate OnDeath;

	UPROPERTY(BlueprintAssignable)
	FPickUpDelegate OnPickUp;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent *SpringArmComponent; // Spring arm component

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent *CameraComponent; // Camera component

	UFUNCTION(BlueprintCallable)
	void AddCoin();
	

public:
	UPROPERTY(BlueprintReadOnly)
	int32 Coins = 0;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsDead = false;

	UFUNCTION(BlueprintCallable)
	void Death();


};
