// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Obstacle.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(RootComponent);

	ExitTrigger = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	ExitTrigger->SetupAttachment(RootComponent);

	ObstacleSpawn = CreateDefaultSubobject<UBoxComponent>("ObstacleSpawn");
	ObstacleSpawn->SetupAttachment(RootComponent);

	PickupSpawn = CreateDefaultSubobject<UBoxComponent>("PickupSpawn");
	PickupSpawn->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	ExitTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnOverlap);
	
}

void ATile::TrySpawnObstacle()
{
	if(UKismetMathLibrary::RandomBoolWithWeight(0.6f))
		SpawnObstacle();
}

void ATile::TrySpawnPickup()
{
	for(int i = 0; i < 4; i++) // Spawn 2 pickups
	{
		if(UKismetMathLibrary::RandomBoolWithWeight(0.3f))
			SpawnItem();
	}
}

void ATile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != (AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) return;
	OnTileExit.Broadcast(this);
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATile::TileDestroy, 2, false); 
	
}

void ATile::TileDestroy()
{
	for (AObstacle* Obstacle : ObstaclesSpawned)
	{
		Obstacle->Destroy();
	}

	for (APickup *Pickup : PickupSpawned)
	{
		Pickup->Destroy();
	}
	
	Destroy(); 
}

void ATile::SpawnObstacle()
{
	FVector randomPosition = UKismetMathLibrary::RandomPointInBoundingBox(ObstacleSpawn->GetComponentLocation(), ObstacleSpawn->GetScaledBoxExtent());
	FTransform SpawnTransform = FTransform(randomPosition);
	int32 RandomIndex = FMath::RandRange(0, ObstacleTypes.Num() - 1);
	TSubclassOf<AObstacle> SelectedObstacleClass = ObstacleTypes[RandomIndex];
	AObstacle *Obstacle = GetWorld()->SpawnActor<AObstacle>(SelectedObstacleClass, SpawnTransform);
	ObstaclesSpawned.Add(Obstacle);
}

void ATile::SpawnItem()
{
	FVector randomPosition = UKismetMathLibrary::RandomPointInBoundingBox(PickupSpawn->GetComponentLocation(), PickupSpawn->GetScaledBoxExtent());
	FTransform SpawnTransform = FTransform(randomPosition);
	int32 RandomIndex = FMath::RandRange(0, PickupTypes.Num() - 1);
	TSubclassOf<APickup> SelectedPickupClass = PickupTypes[RandomIndex];
	APickup *Pickup = GetWorld()->SpawnActor<APickup>(SelectedPickupClass, SpawnTransform);
	PickupSpawned.Add(Pickup);
}

FTransform ATile::GetAttachTransform()
{
	return ArrowComponent->GetComponentTransform();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

