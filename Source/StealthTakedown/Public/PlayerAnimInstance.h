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

	UFUNCTION(BlueprintCallable)
	double GroundSpeed() const;

	UFUNCTION(BlueprintCallable)
	bool IsAssassinating() const;
private:
	void NativeInitializeAnimation() override;

	void NativeUpdateAnimation(float DeltaTime) override;
};
