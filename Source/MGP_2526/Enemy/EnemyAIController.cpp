// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerPawn)
	{
		float Distance = FVector::Dist(GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());

		if (Distance > AcceptanceRadius)
		{
			MoveToActor(PlayerPawn, AcceptanceRadius);
		}
		else
		{
			StopMovement();
			//maybe add attacks in here later
		}
	}
	
}

