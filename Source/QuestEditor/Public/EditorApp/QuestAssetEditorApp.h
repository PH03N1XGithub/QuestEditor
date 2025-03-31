// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "Nodes/QuestGraphNodeBase.h"
#include "Nodes/QuestRuntimeNodeBase.h"
#include "NodeType.h"
#include "QuestAsset.h"
/**
 * 
 */


namespace QuestEditor::EditorApp
{
	class QUESTEDITOR_API QuestAssetEditorApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
	{
	public: // FWorkflowCentricApplication interface
		virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
		void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* InObject);

		class UQuestAsset* GetWorkingAsset() const { return WorkingAsset; }
		class UEdGraph* GetWorkingGraph() const { return WorkingGraph; }

		// Factory map for node type to class mapping
		static const TMap<EQuestNodeType, TSubclassOf<UQuestGraphNodeBase>>& GetNodeTypeClassMap();
		static const TMap<EQuestNodeType, TSubclassOf<UQuestRuntimeNodeBase>>& QuestAssetEditorApp::GetNodeTypeRuntimeClassMap();

		void SetWorkingGraphUI(const TSharedPtr<SGraphEditor>& InWorkingGraphUI) { WorkingGraphUI = InWorkingGraphUI; }
		void SetSelectedNodeDetailView(const TSharedPtr<class IDetailsView>& DetailsView);
		void OnGraphSelectionChanged(const FGraphPanelSelectionSet& Selections) const;

	public: // FAssetEditorToolkit interface
		virtual FName GetToolkitFName() const override { return FName(TEXT("QuestAssetEditorApp")); }
		virtual FText GetBaseToolkitName() const override { return FText::FromString(TEXT("QuestAssetEditorApp")); }
		virtual FString GetWorldCentricTabPrefix() const override { return TEXT("QuestAssetEditorApp"); }
		virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f); }
		virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit) override { }
		virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit) override { }

		virtual void OnClose() override;
		void OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& Event) const;
		void OnGraphChanged(const FEdGraphEditAction& EditAction) const;

	protected:
		virtual void SaveAsset_Execute() override;

		void UpdateWorkingAssetFromGraph() const;
		void UpdateEditorGraphFromWorkingAsset() const;
	
	private:
	
		class UQuestAsset* WorkingAsset = nullptr;
		class UEdGraph* WorkingGraph = nullptr;

		FDelegateHandle GraphChangeListenerHandle;

		// Working graph UI
		TSharedPtr<class SGraphEditor> WorkingGraphUI = nullptr;

		TSharedPtr<class IDetailsView> SelectedNodeDetailsView = nullptr;

	
	};
}
