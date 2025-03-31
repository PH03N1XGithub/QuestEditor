#include "EditorApp/QuestGraphSchema.h"
#include "Nodes/QuestGraphNode.h"
#include "EdGraph/EdGraphSchema.h"
#include "Nodes/QuestIfNode.h"
#include "Nodes/QuestRuntimeNodeBase.h"
#include "Nodes/QuestStartGraphNode.h"
#include "Nodes/StopExecutionNode.h"
#include "Nodes/TriggerNode.h"



	void QuestEditor::EditorApp::UQuestGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& contextMenuBuilder) const {
		TSharedPtr<FNewNodeAction> newNodeAction(
			new FNewNodeAction(
				FText::FromString(TEXT("Nodes")), 
				FText::FromString(TEXT("New node")), 
				FText::FromString(TEXT("Makes a new node")), 
				0,
				EQuestNodeType::QuestNode
			)
		);

		contextMenuBuilder.AddAction(newNodeAction);

		// Add Stop Execution Node
		{
			TSharedPtr<FNewNodeAction> stopExecutionNodeAction = MakeShareable(
				new FNewNodeAction(
					FText::FromString(TEXT("Nodes")), 
					FText::FromString(TEXT("Stop Execution Node")),
					FText::FromString(TEXT("Creates a Stop Execution Node")),
					0,
					EQuestNodeType::StopNode
				)
			);
			contextMenuBuilder.AddAction(stopExecutionNodeAction);
		}

		{
			TSharedPtr<FNewNodeAction> TriggerNodeAction = MakeShareable(
				new FNewNodeAction(
					FText::FromString(TEXT("Nodes")), 
					FText::FromString(TEXT("Trigger Node")),
					FText::FromString(TEXT("Creates a Trigger Node")),
					0,
					EQuestNodeType::TriggerNode
				)
			);
			contextMenuBuilder.AddAction(TriggerNodeAction);
		}

		{
			TSharedPtr<FNewNodeAction> IfNodeAction = MakeShareable(
				new FNewNodeAction(
					FText::FromString(TEXT("Nodes")), 
					FText::FromString(TEXT("If Node")),
					FText::FromString(TEXT("Creates a If Node")),
					0,
					EQuestNodeType::IfNode
				)
			);
			contextMenuBuilder.AddAction(IfNodeAction);
		}
   
	}

	const FPinConnectionResponse QuestEditor::EditorApp::UQuestGraphSchema::CanCreateConnection(const UEdGraphPin* a, const UEdGraphPin* b) const {
		// Neither can be nullptr
		UE_LOG(QuestAssetEditorAppLogSub, Display, TEXT("UQuestGraphSchema::CanCreateConnection"));
		if (a == nullptr || b == nullptr) {
			return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Need 2 pins"));
		}

		// Make sure the directions are different (no inputs to inputs or outputs to outputs)
		if (a->Direction == b->Direction) {
			return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Inputs can only connect to outputs"));
		}

		// Else allow it but break all connections
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_AB, TEXT(""));
	}

	void QuestEditor::EditorApp::UQuestGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
	{
		UQuestStartGraphNode* StartGraphNode = NewObject<UQuestStartGraphNode>(&Graph);
		StartGraphNode->CreateNewGuid();
		StartGraphNode->NodePosX = 0;
		StartGraphNode->NodePosY = 0;

		StartGraphNode->CreateCustomPin(EGPD_Output,FName("Start"));

		Graph.AddNode(StartGraphNode,true,true);
		Graph.Modify();
		//Super::CreateDefaultNodesForGraph(Graph);
	}


	UEdGraphNode* QuestEditor::EditorApp::FNewNodeAction::PerformAction(UEdGraph* parentGraph, UEdGraphPin* fromPin, const FVector2D location, bool bSelectNewNode) {
    
		UQuestGraphNodeBase* Result = nullptr;
		switch (NodeType) {
		case EQuestNodeType::QuestNode:
			UE_LOG(QuestAssetEditorAppLogSub, Display, TEXT("Quest node created"));
			Result = NewObject<UQuestGraphNode>(parentGraph);
			break;
		case EQuestNodeType::StopNode:
			UE_LOG(QuestAssetEditorAppLogSub, Display, TEXT("Stop node created"));
			Result = NewObject<UStopExecutionNode>(parentGraph);
			break;
		case EQuestNodeType::TriggerNode:
			UE_LOG(QuestAssetEditorAppLogSub, Display, TEXT("Trigger node created"));
			Result = NewObject<UTriggerNode>(parentGraph);
			break;
		case EQuestNodeType::EndNode:
			break;
		case EQuestNodeType::IfNode:
			UE_LOG(QuestAssetEditorAppLogSub, Display, TEXT("If node created"));
			Result = NewObject<UQuestIfNode>(parentGraph);
			break;
		default: ;
		}

    
		Result->CreateNewGuid();
		Result->NodePosX = location.X;
		Result->NodePosY = location.Y;

    
		//Result->SetNodeInfo(NewObject<UQuestNodeInfo>(Result));
		Result->InitNodeInfo(Result);

		UEdGraphPin* InputPin = Result->CreateCustomPin(EEdGraphPinDirection::EGPD_Input, TEXT("Input"));
		if (NodeType == EQuestNodeType::IfNode)
		{
			Result->CreateCustomPin(EEdGraphPinDirection::EGPD_Output, TEXT("True"));
			Result->CreateCustomPin(EEdGraphPinDirection::EGPD_Output, TEXT("False"));
		}else
		{
			Result->CreateCustomPin(EEdGraphPinDirection::EGPD_Output, TEXT("Output"));
		}

		// If the from pin is not null, connect them
		if (fromPin != nullptr) {
			Result->GetSchema()->TryCreateConnection(fromPin, InputPin);
		}

		parentGraph->Modify();
		parentGraph->AddNode(Result, true, true);

		return Result;
    

    
	}
	

