// Fill out your copyright notice in the Description page of Project Settings.


#include "AMainObject.h"

bool ToggleMaterial = true;

// Sets default values
AAMainObject::AAMainObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainCube"));
	Cube->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShapeCube(
		TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (ShapeCube.Succeeded())
	{
		Cube->SetStaticMesh(ShapeCube.Object);
		CurrentMaterial = Cube->GetMaterial(0);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BrickMaterialFinder(
		TEXT("/Game/StarterContent/Materials/M_Brick.M_Brick"));

	if (BrickMaterialFinder.Succeeded())
	{
		BrickMaterial = BrickMaterialFinder.Object;
	}

	Cube->OnClicked.AddDynamic(this, &AAMainObject::OnClicked);
	Cube->OnBeginCursorOver.AddDynamic(this, &AAMainObject::OnBeginCursorOver);
	Cube->OnEndCursorOver.AddDynamic(this, &AAMainObject::OnEndCursorOver);
}

// Called when the game starts or when spawned
void AAMainObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAMainObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAMainObject::OnClicked(UPrimitiveComponent* ClickedComponent, FKey ButtonPress)
{
	Cube->SetMaterial(0, ToggleMaterial ? BrickMaterial : CurrentMaterial);
	ToggleMaterial = !ToggleMaterial;
}

void AAMainObject::OnBeginCursorOver(UPrimitiveComponent* TouchedComponent)
{
	Cube->SetRenderCustomDepth(true);
}

void AAMainObject::OnEndCursorOver(UPrimitiveComponent* TouchedComponent)
{
	Cube->SetRenderCustomDepth(false);
}