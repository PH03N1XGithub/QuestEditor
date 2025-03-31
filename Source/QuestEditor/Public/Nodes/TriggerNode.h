#pragma once

#include "QuestGraphNodeBase.h"
#include "EdGraph/EdGraphNode.h"
#include "NodeInfos/TriggerNodeInfo.h"
#include "TriggerNode.generated.h"

UCLASS()
class QUESTEDITOR_API UTriggerNode  : public UQuestGraphNodeBase
{
	GENERATED_BODY()
public:
	// UEdGraphNode Interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		if (NodeInfo == nullptr)
			return FText::FromString("Trigger Node");
		return !NodeInfo->NodeName.IsEmpty() ? NodeInfo->NodeName : FText::FromString("Trigger Node");
	}
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor(46, 255, 200)); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
	virtual FLinearColor GetNodeBodyTintColor() const override{return FLinearColor::Blue;};
	
	// Graph Node Interface
	virtual EQuestNodeType GetQuestNodeType() override {return EQuestNodeType::TriggerNode;} 
	virtual UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName Name) override;
	virtual void InitNodeInfo(UObject* Outer) override { NodeInfo = NewObject<UTriggerNodeInfo>(Outer); }
	virtual void SetNodeInfo(UQuestNodeInfoBase* M_NodeInfo) override { NodeInfo = Cast<UTriggerNodeInfo>(M_NodeInfo); }
	virtual UQuestNodeInfoBase* GetNodeInfo() const override { return NodeInfo; }
	
	UPROPERTY()
	UTriggerNodeInfo* NodeInfo;
};
