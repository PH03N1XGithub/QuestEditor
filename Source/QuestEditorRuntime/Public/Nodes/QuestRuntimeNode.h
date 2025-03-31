#pragma once
#include "ExactQ.h"
#include "QuestRuntimeNodeBase.h"
#include "NodeInfos/QuestNodeInfo.h"
#include "QuestRuntimeNode.generated.h"


UCLASS()
class QUESTEDITORRUNTIME_API UQuestRuntimeNode : public UQuestRuntimeNodeBase
{
	GENERATED_BODY()

public:
	UQuestRuntimeNode();

	virtual UQuestRuntimeNodeBase* ExecuteNode() override;

	
	UPROPERTY()
	const UQuestNodeInfo* QuestNodeInfo;
};