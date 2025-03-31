#pragma once
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class EQuestNodeType : uint8  
{
	None = 0,
	StartNode,
	QuestNode,
	StopNode,
	TriggerNode,
	IfNode,
	EndNode
};