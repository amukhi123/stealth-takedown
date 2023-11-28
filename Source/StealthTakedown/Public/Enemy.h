#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "Enemy.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class USceneComponent;

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
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> m_SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> m_CapsuleComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> m_AssassniationPosition;
};
