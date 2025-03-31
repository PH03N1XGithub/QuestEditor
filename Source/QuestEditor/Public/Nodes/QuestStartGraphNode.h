#pragma once

#include "EdGraph/EdGraphNode.h"
#include "QuestGraphNodeBase.h"
#include "QuestStartGraphNode.generated.h"

UCLASS()
class QUESTEDITOR_API UQuestStartGraphNode : public UQuestGraphNodeBase {
	GENERATED_BODY()

public:// UEdGraphNode Interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titalType) const override { return FText::FromString("Start"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Red); }
	virtual bool CanUserDeleteNode() const override { return false; }

	// Graph Node Interface
	virtual UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName Name) override;
	virtual EQuestNodeType GetQuestNodeType() override {return EQuestNodeType::StartNode;}
};
