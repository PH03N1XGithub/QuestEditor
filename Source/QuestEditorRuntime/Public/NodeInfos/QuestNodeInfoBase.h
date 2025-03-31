#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "QuestNodeInfoBase.generated.h"


UCLASS(BlueprintType)
class QUESTEDITORRUNTIME_API UQuestNodeInfoBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Node Info")
	FText NodeName;
};
