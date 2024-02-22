// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "Pickup.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTileExit, class ATile*, Tile);

UCLASS()
class ENDLESSRUNNERCPP_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UPROPERTY(BlueprintAssignable)
	FOnTileExit OnTileExit;

	FTransform GetAttachTransform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent *SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UArrowComponent *ArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent *ExitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent *ObstacleSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<AObstacle>> ObstacleTypes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AObstacle*> ObstaclesSpawned;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent *PickupSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<APickup>> PickupTypes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<APickup*> PickupSpawned;

	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	void SpawnObstacle();
	void SpawnItem(); 
	void TileDestroy();
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void TrySpawnObstacle();
	void TrySpawnPickup();

};
