#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Docking/TabManager.h"
#include "Styling/SlateStyle.h"


namespace QuestEditor
{
	class FQuestEditorModule final : public IModuleInterface
	{
	public:
		// Implement base functionality for Startup and Shutdown
		virtual void StartupModule() override;
		virtual void ShutdownModule() override;
	private:
		TSharedPtr<FSlateStyleSet> StyleSet = nullptr;
		TSharedPtr<struct FQuestPinFactory> PinFactory = nullptr;
	};
}
