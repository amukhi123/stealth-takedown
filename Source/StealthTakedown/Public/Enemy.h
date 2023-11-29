#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "Enemy.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class USceneComponent;

class UAnimMontage;

UCLASS()
class STEALTHTAKEDOWN_API AEnemy : public AActor
{
GENERATED_BODY()
public:
	AEnemy();

	FORCEINLINE TObjectPtr<UCapsuleComponent> CapsuleComponent() const
	{
		return m_CapsuleComponent;
	}

	FORCEINLINE TObjectPtr<USceneComponent> AssassinationPosition() const
	{
		return m_AssassniationPosition;
	}

	void Die() const;
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> m_SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> m_CapsuleComponent;

	UPROPERTY(EditDefaultsOnly, Category = Assassination)
	TObjectPtr<USceneComponent> m_AssassniationPosition;

	UPROPERTY(EditDefaultsOnly, Category = Assassination)
	TObjectPtr<UAnimMontage> m_AssassinatedAnimMontage;

	void PlayAnimMontage() const;
};
