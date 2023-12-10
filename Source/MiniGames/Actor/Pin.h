// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor.h"
#include "../Enum/EPinType.h"
#include "Pin.generated.h"


/**
 * 
 */
UCLASS()
class MINIGAMES_API APin : public AMyActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TArray<class UMaterialInstance*> MaterialList;

	UPROPERTY(EditAnywhere)
	EPinType MyType{ EPinType::UNKNOWN };

	UPROPERTY(EditAnywhere)
	float DefaultSize{ 0.3 };

	UPROPERTY(EditAnywhere)
	float MiniSize{ 0.15 };

	UPROPERTY(EditAnywhere)
	float MaxSize{ 0.35 };

	// -------------------------------------------------- //
	// --------------------- Sounds --------------------- //
	// -------------------------------------------------- //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|SE")
	TObjectPtr<class USoundBase> PinSE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|SE")
	TObjectPtr<class USoundBase> HitSE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound|SE")
	TObjectPtr<class USoundBase> BlowSE;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound|SE")
	TObjectPtr<class USoundBase> CurrentSE{ PinSE };

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent> QuestionMark;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UInterpToMover* InterpToMoverComp{ nullptr };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> PinMesh{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector AnimationOffset{ FVector(-20, -20, 20) };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveTime{ 0.3f };


public:
	APin();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	const EPinType GetType() const { return MyType; }

public:
	void Setup(EPinType Type);

	void PlaySE();

};
