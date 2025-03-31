#pragma once
#include "NodeType.h"
#include "QuestRuntimePin.h"
#include "QuestRuntimeNodeBase.generated.h"



class UQuestNodeInfoBase;


DEFINE_LOG_CATEGORY_STATIC(QuestAssetEditorAppLogSub, Log, All);
UCLASS(BlueprintType, Blueprintable, EditInlineNew)
class QUESTEDITORRUNTIME_API UQuestRuntimeNodeBase : public UObject {
	GENERATED_BODY()

public:
	UQuestRuntimeNodeBase(): InputPin(nullptr), NodeInfo(nullptr)
	{
		UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("QuestRuntimeNode Created"));
	}

	UPROPERTY()
	EQuestNodeType NodeType = EQuestNodeType::QuestNode;
    
	UPROPERTY()
	UQuestRuntimePin* InputPin;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	TArray<UQuestRuntimePin*> OutputPins;

	UPROPERTY()
	FVector2D Position;
    
	UPROPERTY()
	UQuestNodeInfoBase* NodeInfo;
    
	UFUNCTION(BlueprintCallable, Category="Runtime Node")
	virtual UQuestRuntimeNodeBase* ExecuteNode();

	static bool HasConnection(const UQuestRuntimePin* Output);

	UQuestRuntimeNodeBase* ActivateOutputPin(const UQuestRuntimePin* Output);
};