#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

UCLASS()
class STEALTHTAKEDOWN_API UEnemyAnimInstance : public UAnimInstance
{
GENERATED_BODY()
public:
	UEnemyAnimInstance();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool isEnemyBeingAssassinated() const
	{
		return m_isEnemyBeingAssassinated;
	}
private:
	bool m_isEnemyBeingAssassinated;
};
