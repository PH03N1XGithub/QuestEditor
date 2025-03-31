// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "QuestRuntimeGraph.h"
#include "UObject/Object.h"
#include "QuestAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class QUESTEDITORRUNTIME_API UQuestAsset : public UObject 
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Runtime Node")
	UQuestRuntimeGraph* Graph = nullptr;
};
