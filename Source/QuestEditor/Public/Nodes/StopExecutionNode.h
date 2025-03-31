#pragma once

#include "QuestGraphNodeBase.h"
#include "EdGraph/EdGraphNode.h"
#include "StopExecutionNode.generated.h"


UCLASS()
class QUESTEDITOR_API UStopExecutionNode  : public UQuestGraphNodeBase
{
	GENERATED_BODY()
public:
	// UEdGraphNode Interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override{return FText::FromString("Stop Execution");}
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Blue); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	// Graph Node Interface
	virtual EQuestNodeType GetQuestNodeType() override {return EQuestNodeType::StopNode;} 
	virtual UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName Name) override;
};
