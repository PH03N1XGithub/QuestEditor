#pragma once
#include "QuestRuntimeNodeBase.h"
#include "NodeInfos/IfNodeInfo.h"
#include "QuestRuntimeIfNode.generated.h"

UCLASS()
class QUESTEDITORRUNTIME_API UQuestRuntimeIfNode : public UQuestRuntimeNodeBase
{
	GENERATED_BODY()

public:
	UQuestRuntimeIfNode();
	
	virtual UQuestRuntimeNodeBase* ExecuteNode() override;

	UPROPERTY()
	const UIfNodeInfo* IfNodeInfo;
};