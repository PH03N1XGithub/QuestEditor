// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "NodeInfos/IfNodeInfo.h"
#include "QuestGraphNodeBase.h"
#include "QuestIfNode.generated.h"

UCLASS()
class QUESTEDITOR_API UQuestIfNode : public UQuestGraphNodeBase
{
	GENERATED_BODY()
	
public:
	// UEdGraphNode Interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return (!NodeInfo && !NodeInfo->NodeName.IsEmpty()) ? NodeInfo->NodeName : FText::FromString("Quest If Node Node");
	}
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor(150, 0, 255)); }
	virtual FLinearColor GetNodeBodyTintColor() const override { return FLinearColor(1.0f, 0.0f, 0.0f, 1.0f); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
	
	// Graph Node Interface
	virtual EQuestNodeType GetQuestNodeType() override {return EQuestNodeType::IfNode;}  
	virtual UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName Name) override;
	virtual void InitNodeInfo(UObject* Outer) override { NodeInfo = NewObject<UIfNodeInfo>(Outer); }
	virtual void SetNodeInfo(UQuestNodeInfoBase* M_NodeInfo) override { NodeInfo = Cast<UIfNodeInfo>(M_NodeInfo); }
	virtual UQuestNodeInfoBase* GetNodeInfo() const override { return NodeInfo; }

protected:
	UPROPERTY()
	UIfNodeInfo* NodeInfo;
};
