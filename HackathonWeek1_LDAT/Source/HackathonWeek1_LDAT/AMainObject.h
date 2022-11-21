// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMainObject.generated.h"

UCLASS()
class HACKATHONWEEK1_LDAT_API AAMainObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAMainObject();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *Cube;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* CurrentMaterial;
	
	UPROPERTY(EditAnywhere)
	UMaterialInterface* BrickMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnEndCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* ClickedComponent,FKey ButtonPress);
};
