// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Enemy/EnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemyCharacter::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 150.0f;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEnemyCharacter::TakeAttackDamage(float damage, EAttackType AttackType)
{
	float FinalDamage = damage;

	if (AttackType == Weakness)
	{
		FinalDamage *= 2.0f;
		UE_LOG(LogTemp, Warning, TEXT("WEAK HIT"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Normal hit"));
	}

	Health -= FinalDamage;

	UE_LOG(LogTemp, Warning, TEXT("Enemy Health: %f"), Health);

	if (Health <= 0.0f)
	{
		Destroy();
	}
}


