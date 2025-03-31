// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "QuestAsset.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MyGameInstanceSubsystem.generated.h"


class UQuestRuntimeNodeBase;
/**
 * 
 */
UCLASS()
class QUESTEDITORRUNTIME_API UMyGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UFUNCTION()
	void ActivateDelegate(FName Name);
	
	void InitializeDelegates();
	
	UFUNCTION()
	void OnTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UPROPERTY()
	UQuestRuntimeNodeBase* QuestRuntimeNode;
	
	UFUNCTION()
	static UQuestAsset* GetQuestAsset();
	
	UPROPERTY()
	UQuestAsset* M_QuestAsset;
	
	UFUNCTION()
	static void ExecuteQuest(const UQuestAsset* QuestAsset);
};
