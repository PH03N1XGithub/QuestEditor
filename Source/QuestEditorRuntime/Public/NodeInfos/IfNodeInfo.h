#pragma once
#include "QuestNodeInfoBase.h"
#include "IfNodeInfo.generated.h"


UCLASS(BlueprintType)
class QUESTEDITORRUNTIME_API UIfNodeInfo : public UQuestNodeInfoBase
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Node Info")
	bool bCondition;
	
};
