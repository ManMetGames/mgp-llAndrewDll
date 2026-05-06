// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn(); // Gets the player pawn so the enemy can track the player

	if (PlayerPawn)
	{
		float Distance = FVector::Dist(GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation()); // calculates the distance between the enemy and the player

		if (Distance > AcceptanceRadius) // Moves the enemy towards the player until within attack distance
		{
			MoveToActor(PlayerPawn, AcceptanceRadius);
		}
		else
		{
			StopMovement(); // stops movement once the enemy reaches its target
			//maybe add attacks in here later
		}
	}
	
}

