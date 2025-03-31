#pragma once
#include "CoreMinimal.h"
#include "Nodes/QuestRuntimeNodeBase.h"
#include "QuestRuntimeGraph.generated.h"

UCLASS()
class QUESTEDITORRUNTIME_API UQuestRuntimeGraph : public UObject {
    GENERATED_BODY()

public:
    UQuestRuntimeGraph()
        : QuestRuntimeNode(GetStartNode())
    {
        UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("QuestRuntimeGraph Created"));
    }
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Runtime Node")
    TArray<TObjectPtr<UQuestRuntimeNodeBase>> Nodes;

    UPROPERTY()
    UQuestRuntimeNodeBase* QuestRuntimeNode;

    UFUNCTION(BlueprintCallable)
    UQuestRuntimeNodeBase* GetStartNode()
    {
        if (Nodes.Num() > 0 && Nodes[0]) 
        {
            return Nodes[0]->NodeType == EQuestNodeType::StartNode ? Nodes[0] : nullptr;
        }
        return nullptr;
    }

};
