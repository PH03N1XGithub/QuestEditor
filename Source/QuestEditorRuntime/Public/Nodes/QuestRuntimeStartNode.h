#pragma once
#include "QuestRuntimeNodeBase.h"
#include "QuestRuntimeStartNode.generated.h"


UCLASS()
class QUESTEDITORRUNTIME_API UQuestRuntimeStartNode : public UQuestRuntimeNodeBase
{
	GENERATED_BODY()

public:

	virtual UQuestRuntimeNodeBase* ExecuteNode() override;
};