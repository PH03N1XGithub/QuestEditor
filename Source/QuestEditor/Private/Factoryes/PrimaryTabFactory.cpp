// Fill out your copyright notice in the Description page of Project Settings.


#include "Factoryes/PrimaryTabFactory.h"
#include "EditorApp/QuestAssetEditorApp.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "GraphEditor.h"
#include "Internationalization/Text.h"
#include "EdGraph/EdGraph.h"


namespace QuestEditor::Factories
{
	//this and appMode should be same FName("QuestAssetPrimaryTab")
	FPrimaryTabFactory::FPrimaryTabFactory(const TSharedPtr<class QuestEditor::EditorApp::QuestAssetEditorApp>& App) :  FWorkflowTabFactory(FName("QuestAssetPrimaryTab"), App)
	{
		_app = App;

		TabLabel = FText::FromString(TEXT("Primary"));

		ViewMenuDescription = FText::FromString(TEXT("Displays a primary view for whatever you want to do."));
		ViewMenuTooltip = FText::FromString(TEXT("Show the primary view."));
	}

#define LOCTEXT_NAMESPACE "PrimaryTabFactory"
	TSharedRef<SWidget> FPrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
	{
	
		//return SNew(STextBlock).Text(FText::FromString(TEXT("primary quest tab Widget")));
	
		TSharedPtr<QuestEditor::EditorApp::QuestAssetEditorApp> app = _app.Pin();

		SGraphEditor::FGraphEditorEvents GraphEditorEvents;
		GraphEditorEvents.OnSelectionChanged.BindRaw(app.Get(), &EditorApp::QuestAssetEditorApp::OnGraphSelectionChanged);

		FGraphAppearanceInfo AppearanceInfo;
		AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText_AGSGraph", "Quest Editor");

		TSharedPtr<SGraphEditor> GraphEditor = SNew(SGraphEditor)
			.IsEditable(true)
			.Appearance(AppearanceInfo)
			.GraphEvents(GraphEditorEvents)
			.GraphToEdit(app->GetWorkingGraph());
		app->SetWorkingGraphUI(GraphEditor);

		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			.HAlign(HAlign_Fill)
			[
				GraphEditor.ToSharedRef()
			];
	

	}
#undef LOCTEXT_NAMESPACE

	
	FText FPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
	{
		return FText::FromString(TEXT("primary widget"));
	}
}
