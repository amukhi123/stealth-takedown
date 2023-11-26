#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class UMovementComponent;

UCLASS()
class STEALTHTAKEDOWN_API UPlayerAnimInstance : public UAnimInstance
{
GENERATED_BODY()
public:
	UPlayerAnimInstance();
protected:
	UPROPERTY(BlueprintReadOnly)
	double m_GroundSpeed;
private:
	TObjectPtr<UMovementComponent> m_PlayerMovementComponent;

	void NativeInitializeAnimation() override;

	void NativeUpdateAnimation(float DeltaTime) override;
};
