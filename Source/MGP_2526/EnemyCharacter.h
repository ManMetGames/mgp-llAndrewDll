// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "EnemyCharacter.generated.h"



UENUM(BlueprintType)
enum class EAttackType : uint8 // defines the elemental attack types used in the combat system
{
	Normal,
	Fire,
	Ice,
	Shock
};


UCLASS()
class MGP_2526_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	EAttackType Weakness = EAttackType::Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UWidgetComponent* HealthWidget;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float MaxHealth = 100.0f;

	void TakeAttackDamage(float Damage, EAttackType AttackType);

	void UpdateHealthBar();

	void ShowHitText(FString Text, FLinearColor TextColour);



	

};
