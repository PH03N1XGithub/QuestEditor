// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorApp/QuestAssteAppMode.h"
#include "EditorApp/QuestAssetEditorApp.h"
#include "Factoryes/PrimaryTabFactory.h"
#include "Factoryes/PropertiesTabFactory.h"

namespace QuestEditor::EditorApp
{
	QuestAssteAppMode::QuestAssteAppMode(TSharedPtr<class QuestEditor::EditorApp::QuestAssetEditorApp> app) :FApplicationMode(TEXT("QuestAssetAppMode"))
	{
		_app = app;
		_tabs.RegisterFactory(MakeShareable(new Factories::FPrimaryTabFactory(app)));
		_tabs.RegisterFactory(MakeShareable(new Factories::FPropertiesTabFactory(app)));
		
	

		TabLayout = FTabManager::NewLayout("QuestAssetAppMode_Layout_v1")
			->AddArea
			(
				FTabManager::NewPrimaryArea()
				->SetOrientation(Orient_Vertical)
				->Split
				(
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Horizontal)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.75)
						->AddTab(FName(TEXT("QuestAssetPrimaryTab")), ETabState::OpenedTab)
					)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.25)
						->AddTab(FName(TEXT("QuestAssetPropertiesTab")), ETabState::OpenedTab)
					)
				)
			);
	}

	void QuestAssteAppMode::RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager)
	{
		//FApplicationMode::RegisterTabFactories(InTabManager);
		TSharedPtr<QuestAssetEditorApp> app = _app.Pin();
		app->PushTabFactories(_tabs);
		FApplicationMode::RegisterTabFactories(InTabManager);
		UE_LOG(LogHAL, Display, TEXT("QuestAssetEditorApp::RegisterTabFactories"));
	}

	void QuestAssteAppMode::PreDeactivateMode()
	{
		FApplicationMode::PreDeactivateMode();
	}

	void QuestAssteAppMode::PostActivateMode()
	{
		FApplicationMode::PostActivateMode();
	}
}
