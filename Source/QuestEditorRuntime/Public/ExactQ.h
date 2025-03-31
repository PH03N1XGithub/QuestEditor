#pragma once
#include "CoreMinimal.h"
#include "ExactQ.generated.h"

class UQuestRuntimeNodeBase;

UCLASS(BlueprintType, Blueprintable, EditInlineNew)
class QUESTEDITORRUNTIME_API UExactQ : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintImplementableEvent)
	void ExecuteQuestNode(UQuestRuntimeNodeBase* Parent);
	virtual void ExecuteQuestNode_Implementation(){GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"ExecuteQuestNode");};
    
};