#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Character.h"
#include "CharacterController.generated.h"

class UInputMappingContext;
class UInputAction;

class UCameraComponent;
class USpringArmComponent;
class UMotionWarpingComponent;

struct FInputActionValue;

UENUM()
enum class ECharacterState : uint8
{
	// We have no need (currently) for idle, walk, etc so we can just group them into one
	Default = 1 << 0,
	Assassinating = 1 << 1
};

UCLASS()
class STEALTHTAKEDOWN_API ACharacterController : public ACharacter 
{
GENERATED_BODY()
public:
	ACharacterController();

	// Perhaps this should be replaced with a player state
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ECharacterState State() const
	{
		return m_State;
	}

	FORCEINLINE void State(const ECharacterState& State)
	{
		m_State = State;
	}
private:
	UPROPERTY(EditDefaultsOnly, Category = Camera)
	TObjectPtr<UCameraComponent> m_Camera;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> m_SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMotionWarpingComponent> m_MotionWarpingComponent;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> m_InputMappingContext;	

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> m_MoveInputAction;	

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> m_LookInputAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> m_AssassinateInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Assassination)
	TObjectPtr<UAnimMontage> m_AssassinationMontage;

	UPROPERTY(EditDefaultsOnly, Category = Assassination)
	float m_MaxAssassinateDistance;

	UPROPERTY(EditDefaultsOnly, Category = Assassination, meta=(ClampMin="0.0", ClampMax="1.0"))
	double m_MinDotValue;

	ECharacterState m_State;

	void BeginPlay() override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& InputActionValue);

	void Look(const FInputActionValue& InputActionValue);

	void Assassinate(const FInputActionValue& InputActionValue);
};
