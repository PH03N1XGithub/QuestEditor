#pragma once
#include "QuestRuntimeNodeBase.h"
#include "QuestRuntimeTriggerNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInitializeDelegates, FName, Tag);

UCLASS()
class QUESTEDITORRUNTIME_API UQuestRuntimeTriggerNode : public UQuestRuntimeNodeBase
{
	GENERATED_BODY()

public:

	FOnInitializeDelegates InitDelegates;
	bool bCanExecute = false;
	
	void InitializeDelegates() const;
	virtual UQuestRuntimeNodeBase* ExecuteNode() override;
};