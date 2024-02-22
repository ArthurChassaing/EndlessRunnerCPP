// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameMode.generated.h"

class ATile;
/**
 * 
 */
UCLASS()
class ENDLESSRUNNERCPP_API ARunGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Ref")
	ATile *Tile;

protected:

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void SpawnTile(ATile* newTile); // Spawn a tile

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile")
	FTransform NextSpawnPoint; 	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile")
	TSubclassOf<AActor> Tileclass; 	
};
