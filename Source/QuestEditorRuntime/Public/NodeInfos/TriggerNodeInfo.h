#pragma once
#include "QuestNodeInfoBase.h"
#include "TriggerNodeInfo.generated.h"


UCLASS(BlueprintType)
class QUESTEDITORRUNTIME_API UTriggerNodeInfo : public UQuestNodeInfoBase
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TriggerNodeInfo")
	FName TriggerTag;
	
};
