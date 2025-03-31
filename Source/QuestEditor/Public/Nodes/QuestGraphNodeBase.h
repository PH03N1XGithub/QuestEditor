#pragma once
#include "EdGraph/EdGraphNode.h"
#include "ToolMenuSection.h"
#include "ToolMenus.h"
#include "NodeType.h"
#include "NodeInfos/QuestNodeInfoBase.h"
#include "QuestGraphNodeBase.generated.h"


UCLASS()
class QUESTEDITOR_API UQuestGraphNodeBase : public UEdGraphNode
{  
	GENERATED_BODY()

public: // Graph Node interface
	virtual UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName Name) { /* Must be overridden */ return nullptr;}
	virtual void InitNodeInfo(UObject* Outer) { /* None by default */ }
	virtual void SetNodeInfo(class UQuestNodeInfoBase* M_NodeInfo){/* None by default */ }
	virtual UQuestNodeInfoBase* GetNodeInfo() const {return nullptr;}
	virtual EQuestNodeType GetQuestNodeType(){return EQuestNodeType::None;}
};
