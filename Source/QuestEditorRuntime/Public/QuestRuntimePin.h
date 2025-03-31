#pragma once
#include "CoreMinimal.h"
#include "QuestRuntimePin.generated.h"

UCLASS()
class QUESTEDITORRUNTIME_API UQuestRuntimePin : public UObject {
	GENERATED_BODY()

public:
	UQuestRuntimePin() = default;

	UPROPERTY()
	FName PinName;

	UPROPERTY()
	FGuid PinId;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UQuestRuntimePin* Connection = nullptr;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	class UQuestRuntimeNodeBase* Parent = nullptr;
};