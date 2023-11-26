#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Character.h"
#include "CharacterController.generated.h"

class UInputMappingContext;
class UInputAction;

class UCameraComponent;
class USpringArmComponent;

struct FInputActionValue;

UCLASS()
class STEALTHTAKEDOWN_API ACharacterController : public ACharacter 
{
GENERATED_BODY()
public:
	ACharacterController();
private:
	UPROPERTY(EditDefaultsOnly, Category = Camera)
	TObjectPtr<UCameraComponent> m_Camera;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> m_SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> m_InputMappingContext;	

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> m_MoveInputAction;	

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> m_LookInputAction;

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& InputActionValue);

	void Look(const FInputActionValue& InputActionValue);
};
