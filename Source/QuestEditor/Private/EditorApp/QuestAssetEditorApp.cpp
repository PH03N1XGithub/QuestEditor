// Fill out your copyright notice in the Description page of Project Settings.



#include "EditorApp/QuestAssetEditorApp.h"
#include "QuestAsset.h"
#include "EditorApp/QuestAssteAppMode.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "EditorApp/QuestGraphSchema.h"
#include "QuestRuntimeGraph.h"
#include "Nodes/QuestGraphNode.h"
#include "Nodes/QuestIfNode.h"
#include "Nodes/QuestStartGraphNode.h"
#include "Nodes/StopExecutionNode.h"
#include "Nodes/TriggerNode.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Nodes/QuestRuntimeIfNode.h"
#include "Nodes/QuestRuntimeNode.h"
#include "Nodes/QuestRuntimeStartNode.h"
#include "Nodes/QuestRuntimeTriggerNode.h"
#include "Widgets/Notifications/SNotificationList.h"

//DEFINE_LOG_CATEGORY_STATIC(QuestAssetEditorAppLogSub, Log, All); 

namespace QuestEditor::EditorApp
{
	// Define the static node type to class mapping
	const TMap<EQuestNodeType, TSubclassOf<UQuestGraphNodeBase>>& QuestAssetEditorApp::GetNodeTypeClassMap()
	{
		// Create a static local map that persists between function calls
		static TMap<EQuestNodeType, TSubclassOf<UQuestGraphNodeBase>> NodeTypeToClass;
	
		// Initialize the map only once
		if (NodeTypeToClass.Num() == 0)
		{
			NodeTypeToClass.Add(EQuestNodeType::StartNode, UQuestStartGraphNode::StaticClass());
			NodeTypeToClass.Add(EQuestNodeType::QuestNode, UQuestGraphNode::StaticClass());
			NodeTypeToClass.Add(EQuestNodeType::StopNode, UStopExecutionNode::StaticClass());
			NodeTypeToClass.Add(EQuestNodeType::TriggerNode, UTriggerNode::StaticClass());
			NodeTypeToClass.Add(EQuestNodeType::IfNode, UQuestIfNode::StaticClass());
		}
	
		return NodeTypeToClass;
	}

	const TMap<EQuestNodeType, TSubclassOf<UQuestRuntimeNodeBase>>& QuestAssetEditorApp::GetNodeTypeRuntimeClassMap()
	{
		// Create a static local map that persists between function calls
		static TMap<EQuestNodeType, TSubclassOf<UQuestRuntimeNodeBase>> NodeTypeToRuntimeClass;
	
		// Initialize the map only once
		if (NodeTypeToRuntimeClass.Num() == 0) 
		{
			NodeTypeToRuntimeClass.Add(EQuestNodeType::StartNode, UQuestRuntimeStartNode::StaticClass());
			NodeTypeToRuntimeClass.Add(EQuestNodeType::QuestNode, UQuestRuntimeNode::StaticClass());
			NodeTypeToRuntimeClass.Add(EQuestNodeType::TriggerNode, UQuestRuntimeTriggerNode::StaticClass());
			NodeTypeToRuntimeClass.Add(EQuestNodeType::IfNode, UQuestRuntimeIfNode::StaticClass());
		}
	
		return NodeTypeToRuntimeClass;
	}

	void QuestAssetEditorApp::RegisterTabSpawners(const TSharedRef<class FTabManager>& tabManager)
	{
		FWorkflowCentricApplication::RegisterTabSpawners(tabManager);
	}

	void QuestAssetEditorApp::InitEditor(const EToolkitMode::Type Mode,
	                                     const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* InObject)
	{
		// Add validation
		if (!InObject)
		{
			UE_LOG(QuestAssetEditorAppLogSub, Error, TEXT("Failed to initialize editor: Invalid object"));
			return;
		}

		TArray<UObject*> ObjectsToEdit;
		ObjectsToEdit.Add(InObject);
    
		WorkingAsset = Cast<UQuestAsset>(InObject);
	
		// Validate cast succeeded
		if (!WorkingAsset)
		{
			UE_LOG(QuestAssetEditorAppLogSub, Error, TEXT("Failed to initialize editor: Object is not a UQuestAsset"));
			return;
		}

		// Create an editor graph
		WorkingGraph = FBlueprintEditorUtils::CreateNewGraph(
			WorkingAsset, 
			NAME_None, 
			UEdGraph::StaticClass(), 
			UQuestGraphSchema::StaticClass()
		);

		if (!WorkingGraph)
		{
			UE_LOG(QuestAssetEditorAppLogSub, Error, TEXT("Failed to create editor graph"));
			return;
		}

		InitAssetEditor( 
			Mode, 
			InitToolkitHost, 
			TEXT("QuestAssetEditor"), 
			FTabManager::FLayout::NullLayout, 
			true, // createDefaultStandaloneMenu 
			true,  // createDefaultToolbar
			ObjectsToEdit,
			true,
			true);

		// Add our modes (just one for this example)
		AddApplicationMode(TEXT("QuestAssetAppMode"), MakeShareable(new QuestAssteAppMode(SharedThis(this))));

		// Set the mode
		SetCurrentMode(TEXT("QuestAssetAppMode"));
	
#ifdef WITH_MY_EDITOR
		UpdateEditorGraphFromWorkingAsset();
#endif
	
		GraphChangeListenerHandle = WorkingGraph->AddOnGraphChangedHandler(
			FOnGraphChanged::FDelegate::CreateSP(this, &QuestAssetEditorApp::OnGraphChanged)
		);
	
	}

	void QuestAssetEditorApp::SetSelectedNodeDetailView(const TSharedPtr<class IDetailsView>& DetailsView)
	{
		UE_LOG(QuestAssetEditorAppLogSub, Log, TEXT("Setting selected node detail view"));
	
		if (!DetailsView)
		{
			UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Invalid details view provided"));
			return;
		}

		SelectedNodeDetailsView = DetailsView;
		SelectedNodeDetailsView->OnFinishedChangingProperties().AddRaw(this, &QuestAssetEditorApp::OnNodeDetailViewPropertiesUpdated);
	}

	void QuestAssetEditorApp::OnGraphSelectionChanged(const FGraphPanelSelectionSet& Selections) const
	{
		UE_LOG(QuestAssetEditorAppLogSub, Log, TEXT("Graph selection changed"));

		if (!SelectedNodeDetailsView)
		{
			UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("SelectedNodeDetailsView is not set"));
			return;
		}

		// Find the first node
		for (UObject* Object : Selections)
		{
			if (const UQuestGraphNodeBase* Node = Cast<UQuestGraphNodeBase>(Object))
			{
				UQuestNodeInfoBase* NodeInfo = Node->GetNodeInfo();
				SelectedNodeDetailsView->SetObject(NodeInfo);
			
				if (NodeInfo)
				{
					UE_LOG(QuestAssetEditorAppLogSub, Verbose, TEXT("Selected node info: %s"), *NodeInfo->GetName());
				}
				else
				{
					UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Selected node has no node info"));
				}
				return;
			}
		}
	
		// No valid node found
		UE_LOG(QuestAssetEditorAppLogSub, Verbose, TEXT("No graph node selected"));
		SelectedNodeDetailsView->SetObject(nullptr);
	}

	void QuestAssetEditorApp::OnClose()
	{
#ifdef WITH_MY_EDITOR
		UpdateWorkingAssetFromGraph();
#endif
		WorkingGraph->RemoveOnGraphChangedHandler(GraphChangeListenerHandle);
		FAssetEditorToolkit::OnClose();
	}

	void QuestAssetEditorApp::OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& Event) const
	{
		if (WorkingGraphUI != nullptr)
		{
			WorkingGraphUI->NotifyGraphChanged();
		}
	}

	void QuestAssetEditorApp::OnGraphChanged(const FEdGraphEditAction& EditAction) const
	{
#ifdef WITH_MY_EDITOR
		UpdateWorkingAssetFromGraph();
#endif
	}

	void QuestAssetEditorApp::SaveAsset_Execute()
	{
		// Perform any custom pre-save actions here
		UE_LOG(QuestAssetEditorAppLogSub, Log, TEXT("Saving Quest Asset"));

		// Mark for transaction
		if (WorkingAsset)
		{
			WorkingAsset->Modify();
		}
#ifdef WITH_MY_EDITOR
		// Update the working asset from the graph
		UpdateWorkingAssetFromGraph();
#endif
		// Call parent implementation
		FWorkflowCentricApplication::SaveAsset_Execute();

		// Show notification for successful save
		FNotificationInfo Info(NSLOCTEXT("QuestEditor", "SavedAsset", "Quest asset saved successfully"));
		Info.ExpireDuration = 2.0f;
		FSlateNotificationManager::Get().AddNotification(Info);
	}

	void QuestAssetEditorApp::UpdateWorkingAssetFromGraph() const
	{
		if (WorkingAsset == nullptr || WorkingGraph == nullptr) 
		{
			UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Cannot update asset: Invalid asset or graph"));
			return;
		}

		// Mark for modification to enable undo/redo
		WorkingAsset->Modify();

		// Update the state we need into our savable format
		UQuestRuntimeGraph* RuntimeGraph = NewObject<UQuestRuntimeGraph>(WorkingAsset);
		// Set flags for proper ownership and undo/redo
		RuntimeGraph->SetFlags(RF_Transactional);
		WorkingAsset->Graph = RuntimeGraph;

		// Using Unreal types instead of STL
		TArray<TPair<FGuid, FGuid>> Connections;
		TMap<FGuid, UQuestRuntimePin*> PinIdToRuntimePinMap;

		// First create all the nodes/pins and record the connections
		for (UEdGraphNode* EditorNode : WorkingGraph->Nodes) 
		{
			// Skip invalid nodes
			if (!EditorNode)
			{
				UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Skipping null editor node"));
				continue;
			}

			UQuestGraphNodeBase* QuestEditorNodeBase = Cast<UQuestGraphNodeBase>(EditorNode);
			const TMap<EQuestNodeType, TSubclassOf<UQuestRuntimeNodeBase>>& NodeTypeToClass = GetNodeTypeRuntimeClassMap();
			TSubclassOf<UQuestRuntimeNodeBase> NodeClass = NodeTypeToClass.FindRef(QuestEditorNodeBase->GetQuestNodeType());
			UQuestRuntimeNodeBase* RuntimeNode;
			RuntimeNode = NewObject<UQuestRuntimeNodeBase>(RuntimeGraph, NodeClass);
		
			/*switch (QuestEditorNodeBase->GetQuestNodeType()) {
		case EQuestNodeType::None:
			break;
		case EQuestNodeType::StartNode:
			RuntimeNode = NewObject<UQuestRuntimeStartNode>(RuntimeGraph);
			break;
		case EQuestNodeType::QuestNode:
			RuntimeNode = NewObject<UQuestRuntimeNode>(RuntimeGraph);
			break;
		case EQuestNodeType::StopNode:
			break;
		case EQuestNodeType::TriggerNode:
			RuntimeNode = NewObject<UQuestRuntimeTriggerNode>(RuntimeGraph);
			break;
		case EQuestNodeType::IfNode:
			RuntimeNode = NewObject<UQuestRuntimeIfNode>(RuntimeGraph);
			break;
		case EQuestNodeType::EndNode:
			break;
		}*/
		
			//UQuestRuntimeNodeBase* RuntimeNode = NewObject<UQuestRuntimeNodeBase>(RuntimeGraph);
			RuntimeNode->SetFlags(RF_Transactional);
			RuntimeNode->Position = FVector2D(EditorNode->NodePosX, EditorNode->NodePosY);

			for (UEdGraphPin* EditorPin : EditorNode->Pins) 
			{
				if (!EditorPin)
				{
					UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Skipping null editor pin"));
					continue;
				}

				UQuestRuntimePin* RuntimePin = NewObject<UQuestRuntimePin>(RuntimeNode);
				RuntimePin->SetFlags(RF_Transactional);
				RuntimePin->PinName = EditorPin->PinName;
				RuntimePin->PinId = EditorPin->PinId;
				RuntimePin->Parent = RuntimeNode;

				// Only record the output side of the connection since this is a directed graph
				if (EditorPin->HasAnyConnections() && EditorPin->Direction == EEdGraphPinDirection::EGPD_Output) 
				{
					// Only 1 connection is allowed so just take the first one
					if (EditorPin->LinkedTo.Num() > 0 && EditorPin->LinkedTo[0])
					{
						TPair<FGuid, FGuid> Connection(EditorPin->PinId, EditorPin->LinkedTo[0]->PinId);
						Connections.Add(Connection);
					}
				}
            
				PinIdToRuntimePinMap.Add(EditorPin->PinId, RuntimePin);
			
				if (EditorPin->Direction == EEdGraphPinDirection::EGPD_Input) 
				{
					RuntimeNode->InputPin = RuntimePin;
				} 
				else 
				{
					RuntimeNode->OutputPins.Add(RuntimePin);
				}
			}

			if (UQuestGraphNodeBase* QuestEditorNode = Cast<UQuestGraphNodeBase>(EditorNode))
			{
				if (const UQuestNodeInfoBase* NodeInfo = QuestEditorNode->GetNodeInfo())
				{
					RuntimeNode->NodeInfo = DuplicateObject(NodeInfo, RuntimeNode);
					RuntimeNode->NodeInfo->SetFlags(RF_Transactional);
				}
				//RuntimeNode->ParentNode = QuestEditorNode;
				RuntimeNode->NodeType = QuestEditorNode->GetQuestNodeType();
			}
			else
			{
				UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Editor node is not a UQuestGraphNodeBase"));
			}

			RuntimeGraph->Nodes.Add(RuntimeNode);
		}

		// Now make all the connections
		for (const TPair<FGuid, FGuid>& Connection : Connections) 
		{
			UQuestRuntimePin* OutPin = PinIdToRuntimePinMap.FindRef(Connection.Key);
			UQuestRuntimePin* InPin = PinIdToRuntimePinMap.FindRef(Connection.Value);
		
			if (OutPin && InPin)
			{
				OutPin->Connection = InPin;
			}
			else
			{
				UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Invalid connection between pins"));
			}
		}
	}

	void QuestAssetEditorApp::UpdateEditorGraphFromWorkingAsset() const
	{
		// Add validation for WorkingAsset and WorkingGraph
		if (!WorkingAsset || !WorkingGraph)
		{
			UE_LOG(QuestAssetEditorAppLogSub, Error, TEXT("Cannot update editor graph: Invalid asset or graph"));
			return;
		}

		if (WorkingAsset->Graph == nullptr) 
		{
			UE_LOG(QuestAssetEditorAppLogSub, Log, TEXT("No graph in asset, creating default nodes"));
			WorkingGraph->GetSchema()->CreateDefaultNodesForGraph(*WorkingGraph);
			return;
		}

		// Create all the nodes/pins first
		TArray<TPair<FGuid, FGuid>> Connections;
		TMap<FGuid, UEdGraphPin*> PinIdToEditorPinMap;
	
		// Get the reference to the node type class map
		const TMap<EQuestNodeType, TSubclassOf<UQuestGraphNodeBase>>& NodeTypeToClass = GetNodeTypeClassMap();
	
		for (UQuestRuntimeNodeBase* RuntimeNode : WorkingAsset->Graph->Nodes) 
		{
			if (!RuntimeNode)
			{
				UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Skipping null runtime node"));
				continue;
			}
		
			// Use the factory pattern with the node type class map
			UQuestGraphNodeBase* NewNode;
			//auto NodeTypeToClass = GetNodeTypeClassMap();
			TSubclassOf<UQuestGraphNodeBase> NodeClass = NodeTypeToClass.FindRef(RuntimeNode->NodeType);

			if (NodeClass)
			{
				NewNode = NewObject<UQuestGraphNodeBase>(WorkingGraph, NodeClass);
			}
			else
			{
				UE_LOG(QuestAssetEditorAppLogSub, Error, 
				       TEXT("Unknown node type: %d - cannot create editor node"), 
				       static_cast<int32>(RuntimeNode->NodeType));
				continue;
			}
		
			// Set node properties
			NewNode->CreateNewGuid();
			NewNode->NodePosX = RuntimeNode->Position.X;
			NewNode->NodePosY = RuntimeNode->Position.Y;
		
			// Set flags for proper memory management
			NewNode->SetFlags(RF_Transactional);

			// Fix node info initialization
			if (RuntimeNode->NodeInfo != nullptr)
			{
				if (UQuestNodeInfoBase* DuplicatedInfo = DuplicateObject(RuntimeNode->NodeInfo, NewNode))
				{
					DuplicatedInfo->SetFlags(RF_Transactional);
					NewNode->SetNodeInfo(DuplicatedInfo);
				}
				else
				{
					UE_LOG(QuestAssetEditorAppLogSub, Warning, 
					       TEXT("Failed to duplicate node info, initializing default info"));
					NewNode->InitNodeInfo(NewNode);
				}
			}
			else
			{
				NewNode->InitNodeInfo(NewNode);
			}

			// Process input pin if it exists
			if (RuntimeNode->InputPin != nullptr) 
			{
				UQuestRuntimePin* RuntimePin = RuntimeNode->InputPin;
				if (!RuntimePin)
				{
					UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Null input pin found, skipping"));
					continue;
				}
			
				UEdGraphPin* EditorPin = NewNode->CreateCustomPin(EEdGraphPinDirection::EGPD_Input, RuntimePin->PinName);
				if (!EditorPin)
				{
					UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Failed to create editor input pin"));
					continue;
				}
			
				EditorPin->PinId = RuntimePin->PinId;

				if (RuntimePin->Connection != nullptr) 
				{
					TPair<FGuid, FGuid> Connection(RuntimePin->PinId, RuntimePin->Connection->PinId);
					Connections.Add(Connection);
				}
				PinIdToEditorPinMap.Add(RuntimePin->PinId, EditorPin);
			}

			// Process output pins
			for (UQuestRuntimePin* RuntimePin : RuntimeNode->OutputPins) 
			{
				if (!RuntimePin)
				{
					UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Null output pin found, skipping"));
					continue;
				}
			
				UEdGraphPin* EditorPin = NewNode->CreateCustomPin(EEdGraphPinDirection::EGPD_Output, RuntimePin->PinName);
				if (!EditorPin)
				{
					UE_LOG(QuestAssetEditorAppLogSub, Warning, TEXT("Failed to create editor output pin"));
					continue;
				}
			
				EditorPin->PinId = RuntimePin->PinId;
            
				if (RuntimePin->Connection != nullptr) 
				{
					TPair<FGuid, FGuid> Connection(RuntimePin->PinId, RuntimePin->Connection->PinId);
					Connections.Add(Connection);
				}
				PinIdToEditorPinMap.Add(RuntimePin->PinId, EditorPin);
			}

			// Add the node to the graph
			WorkingGraph->AddNode(NewNode, true, true);
		}

		// Process connections
		for (const TPair<FGuid, FGuid>& Connection : Connections) 
		{
			UEdGraphPin* FromPin = PinIdToEditorPinMap.FindRef(Connection.Key);
			UEdGraphPin* ToPin = PinIdToEditorPinMap.FindRef(Connection.Value);
		
			if (FromPin && ToPin)
			{
				FromPin->LinkedTo.Add(ToPin);
				ToPin->LinkedTo.Add(FromPin);
			}
			else
			{
				UE_LOG(QuestAssetEditorAppLogSub, Warning, 
				       TEXT("Failed to connect pins: Pin IDs %s and %s not found"), 
				       *Connection.Key.ToString(), *Connection.Value.ToString());
			}
		}
	
		UE_LOG(QuestAssetEditorAppLogSub, Log, 
		       TEXT("Editor graph updated from working asset: %d nodes and %d connections"), 
		       WorkingAsset->Graph->Nodes.Num(), Connections.Num());
	}
}
