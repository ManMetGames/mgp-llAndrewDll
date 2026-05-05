

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "EnemyCharacter.h"
#include "PlayerCharacter.generated.h"

class UNiagaraSystem;
class UUserWidget;

UCLASS()
class MGP_2526_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Attacks

	void Fire();
	void Ice();
	void Shock();



protected:
	
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	void MoveForward(float InputValue);
	void MoveRight(float InputValue);

	void TurnCamera(float InputValue);
	void LookUp(float InputValue);

	//Sprint

	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintSpeed = 1000.0f;

	//Attack
	UPROPERTY(EditAnywhere, Category = "Attack")
	EAttackType CurrentAttackType = EAttackType::Fire;
	
	//Effects
	UPROPERTY(EditAnywhere, Category = "Attack Effects")
	UNiagaraSystem* FireEffect;
	
	UPROPERTY(EditAnywhere, Category = "Attack Effects")
	UNiagaraSystem* IceEffect;

	UPROPERTY(EditAnywhere, Category = "Attack Effects")
	UNiagaraSystem* ShockEffect;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDClass;

	UPROPERTY()
	UUserWidget* PlayerHUD;

	UPROPERTY(EditAnywhere, Category = "Player Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Player Health")
	float Health = 100.0f;


	void StartSprint();
	void StopSprint();
	void Attack();
	void UpdatePlayerHUD();

	



};
