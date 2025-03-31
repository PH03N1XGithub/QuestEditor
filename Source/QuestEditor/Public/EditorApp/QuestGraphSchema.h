#pragma once

#include "CoreMinimal.h"
#include "NodeType.h"
#include "EdGraph/EdGraph.h"

#include "QuestGraphSchema.generated.h"


	//enum class EQuestNodeType : uint8;

	UCLASS()
	class UQuestGraphSchema : public UEdGraphSchema {
		GENERATED_BODY()

	public:
		virtual void GetGraphContextActions(FGraphContextMenuBuilder& contextMenuBuilder) const override;
		virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* a, const UEdGraphPin* b) const override;
		virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;

	
	};

	USTRUCT()
	struct FNewNodeAction : public FEdGraphSchemaAction {
		GENERATED_BODY();

	public:
		FNewNodeAction() {}
		FNewNodeAction(FText inNodeCategory, FText inMenuDesc, FText inToolTip, const int32 inGrouping, const EQuestNodeType M_NodeType)
			: FEdGraphSchemaAction(inNodeCategory, inMenuDesc, inToolTip, inGrouping), NodeType(M_NodeType) { }

		virtual UEdGraphNode* PerformAction(UEdGraph* parentGraph, UEdGraphPin* fromPin, const FVector2D location, bool bSelectNewNode = true) override;


		// Add NodeType to distinguish different types of nodes
		EQuestNodeType NodeType;
	};


namespace QuestEditor::EditorApp {
	using UQuestGraphSchema = UQuestGraphSchema;
	using FNewNodeAction = FNewNodeAction;
}

