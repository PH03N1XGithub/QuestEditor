#pragma once
#include "CoreMinimal.h"
#include "QuestNodeInfoBase.h"
#include "UObject/ObjectMacros.h"
#include "QuestNodeInfo.generated.h"


UCLASS(BlueprintType)
class QUESTEDITORRUNTIME_API UQuestNodeInfo : public UQuestNodeInfoBase
{
	GENERATED_BODY()


public:
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly , Instanced, Category="Node Info")
	class UExactQ* UExactQ;
	
};
