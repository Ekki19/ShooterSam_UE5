// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterEnemy.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AShooterEnemy::AShooterEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
	HealthBarWidget->SetRelativeLocation(FVector(0, 0, 110)); // Über dem Kopf
	HealthBarWidget->SetRelativeRotation(FRotator::ZeroRotator); // Über dem Kopf

	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen); // Immer zum Spieler gedreht

	if (GetMesh())
	{
		// Schiebt den Dummy in die untere Hälfte der Kapsel
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		// Dreht ihn nach vorne (Standard Unreal Dummy schaut sonst zur Seite)
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}
}

// Called when the game starts or when spawned
void AShooterEnemy::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AShooterEnemy::OnDamageTaken);
	Health = MaxHealth;

	
}

// Called every frame
void AShooterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AShooterEnemy::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Display, TEXT("Damage taken: %f"), Damage);

	if (Health <= 0.0f)
	{
		if (UCapsuleComponent* Capsule = GetCapsuleComponent())
		{
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		HealthBarWidget->SetVisibility(false);
		UE_LOG(LogTemp, Display, TEXT("Character died: %s"), *GetActorNameOrLabel());
	}
}

