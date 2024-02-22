// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"
#include "RunCharacter.h"
#include "Tile.h"

void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Listen to the event 
	if (ATile *tile = Cast<ATile>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		tile->OnTileExit.AddDynamic(this, &ARunGameMode::SpawnTile);
	}
	
	//Spawn default tiles
	for (int i = 0; i < 4; i++)
	{
		SpawnTile(Tile);
	}
}

void ARunGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void ARunGameMode::SpawnTile(ATile* newTile)
{
	ATile* NewTile = GetWorld()->SpawnActor<ATile>(Tileclass, NextSpawnPoint);
	NewTile->TrySpawnObstacle();
	NewTile->TrySpawnPickup();
	NextSpawnPoint = NewTile->GetAttachTransform();

	NewTile->OnTileExit.AddDynamic(this, &ARunGameMode::SpawnTile);
	
}

