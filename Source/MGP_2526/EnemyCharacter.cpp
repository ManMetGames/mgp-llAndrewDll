// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Enemy/EnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "Math/Color.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 150.0f;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);

	HealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HealthWidget->SetupAttachment(RootComponent);
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidget->SetDrawSize(FVector2D(300.0f, 80.0f));
	HealthWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 220.0f));

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	MaxHealth = Health;
	if (HealthWidget)
	{
		HealthWidget->InitWidget();
	}
	UpdateHealthBar();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEnemyCharacter::TakeAttackDamage(float damage, EAttackType AttackType)
{
	float FinalDamage = damage;
	FString HitText = TEXT("");
	FLinearColor TextColour;

	if (AttackType == Weakness)
	{
		FinalDamage *= 1.5f;
		HitText = TEXT("WEAK HIT!");
		TextColour = FLinearColor::Red;
		UE_LOG(LogTemp, Warning, TEXT("WEAK HIT"));
	}
	else
	{
		FinalDamage *= 0.25f;
		HitText = TEXT("RESISTED!");
		TextColour = FLinearColor::Gray;
		UE_LOG(LogTemp, Warning, TEXT("Normal hit"));
	}

	Health -= FinalDamage;
	UpdateHealthBar();
	FString DamageText = FString::Printf(TEXT("%s %.0f"), *HitText, FinalDamage);
	ShowHitText(DamageText, TextColour);

	UE_LOG(LogTemp, Warning, TEXT("Enemy Health: %f"), Health);

	if (Health <= 0.0f)
	{
		Destroy();
	}
}

void AEnemyCharacter::UpdateHealthBar()
{
	if (!HealthWidget) return;

	UUserWidget* Widget = HealthWidget->GetUserWidgetObject();
	if (!Widget) return;

	UProgressBar* Bar = Cast<UProgressBar>(Widget->GetWidgetFromName(TEXT("HealthBar")));

	if (Bar)
	{
		Bar->SetPercent(Health / MaxHealth);

		switch (Weakness)
		{
		case EAttackType::Fire:
			Bar->SetFillColorAndOpacity(FLinearColor::Red);
			break;

		case EAttackType::Ice:
			Bar->SetFillColorAndOpacity(FLinearColor(0.4f, 0.8f, 1.0f, 1.0f));
			break;

		case EAttackType::Shock:
			Bar->SetFillColorAndOpacity(FLinearColor(0.0f, 0.2f, 0.8f, 1.0f));
			break;

		default:
			Bar->SetFillColorAndOpacity(FLinearColor::White);
			break;
		}
	}
}

void AEnemyCharacter::ShowHitText(FString Text, FLinearColor TextColour)
{
	if (!HealthWidget) return;

	UUserWidget* Widget = HealthWidget->GetUserWidgetObject();
	if (!Widget) return;

	static FName FunctionName(TEXT("SetHitText"));
	UFunction* Function = Widget->FindFunction(FunctionName);

	if (Function)
	{
		struct FParams
		{
			FString Text;
			FLinearColor Colour;
		};

		FParams Params;
		Params.Text = Text;
		Params.Colour = TextColour;

		Widget->ProcessEvent(Function, &Params);
	}
}



