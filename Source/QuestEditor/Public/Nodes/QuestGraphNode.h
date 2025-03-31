#pragma once
#include "QuestGraphNodeBase.h"
#include "NodeInfos/QuestNodeInfo.h"
#include "QuestGraphNode.generated.h"

UCLASS()
class QUESTEDITOR_API UQuestGraphNode : public UQuestGraphNodeBase
{
    GENERATED_BODY()

public:// UEdGraphNode Interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override{return FText::FromString("QuestNode");}
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Green); }
	virtual FLinearColor GetNodeBodyTintColor() const override { return FLinearColor(0.0f, 1.0f, 0.0f, 1.0f); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
	
	// Graph Node Interface
    virtual UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName Name) override;
	virtual void InitNodeInfo(UObject* Outer) override { M_NodeInfo = NewObject<UQuestNodeInfo>(Outer); }
	virtual void SetNodeInfo(UQuestNodeInfoBase* NodeInfo) override { M_NodeInfo = Cast<UQuestNodeInfo>(NodeInfo); }
    virtual UQuestNodeInfoBase* GetNodeInfo() const override { return M_NodeInfo; }
	virtual EQuestNodeType GetQuestNodeType() override {return EQuestNodeType::QuestNode;}

protected:
	UPROPERTY()
	class UQuestNodeInfo* M_NodeInfo = nullptr;
};
