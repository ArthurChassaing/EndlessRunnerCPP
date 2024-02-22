// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class ENDLESSRUNNERCPP_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	UFUNCTION()
	void OverlapStarted(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult
	);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnGet(); // Blueprint event

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Skin")
	class UStaticMeshComponent *StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Skin")
	class USphereComponent *SphereComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
