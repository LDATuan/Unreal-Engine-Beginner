// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PMainPlayer.generated.h"
UCLASS()
class HACKATHONWEEK1_LDAT_API APMainPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APMainPlayer();

	UPROPERTY(EditAnywhere)
	class UCameraComponent *CameraInstance;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent *SpringArmInstance;

	UPROPERTY(EditAnywhere)
	class AAMainObject *CubeActor;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void QPressed();

	UFUNCTION()
	void EPressed();

	UFUNCTION()
	void WPressed();

	UFUNCTION()
	void SPressed();
	
	UFUNCTION()
	void RPressed();

	UFUNCTION()
	void WheelDown();

	UFUNCTION()
	void WheelUp();

	UFUNCTION()
	void PressESC();

	UFUNCTION()
	void LeftMousePress();

	UFUNCTION()
	void LeftMouseRelease();
	
	UFUNCTION()
	void MouseX(float amount);

	UFUNCTION()
	void MouseY(float amount);
};
