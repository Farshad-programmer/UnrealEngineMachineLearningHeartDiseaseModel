// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Main.generated.h"

UCLASS()
class CPY_API AMain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RunPythonScript();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString FileContent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString FileContent2;

	// Function to sum two integers and save the result to a file
	UFUNCTION(BlueprintCallable, Category = "MyFunctions")
	void SendPatientInformation(int32 age, int32 sex, int32 cp, int32 trestbps, int32 chol, int32 fbs, int32 restecg, int32 thalach, int32 exang, float oldpeak, int32 slope, int32 ca, int32 thal);

	// Function to read from the Python-generated file and print the result on screen
	UFUNCTION(BlueprintCallable, Category = "MyFunctions")
	void FinalResultFromPython();


};
