// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

/**
 * 
 */
namespace QuestEditor::EditorApp
{
	class QUESTEDITOR_API QuestAssteAppMode : public FApplicationMode
	{
	public:
		QuestAssteAppMode(TSharedPtr<class QuestAssetEditorApp> app);

		virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;
		virtual void PreDeactivateMode() override;
		virtual void PostActivateMode() override;

	

	protected:
		TWeakPtr<class QuestAssetEditorApp> _app;
		FWorkflowAllowedTabSet _tabs;
	};
}
 