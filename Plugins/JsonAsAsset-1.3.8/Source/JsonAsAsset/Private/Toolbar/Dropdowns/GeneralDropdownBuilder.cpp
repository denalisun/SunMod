﻿/* Copyright JsonAsAsset Contributors 2024-2025 */

#include "Toolbar/Dropdowns/GeneralDropdownBuilder.h"

#include "ISettingsModule.h"
#include "Logging/MessageLog.h"
#include "Utilities/Compatibility.h"

void IGeneralDropdownBuilder::Build(FMenuBuilder& MenuBuilder) const {
	MenuBuilder.AddSeparator();
	
	MenuBuilder.AddMenuEntry(
		FText::FromString("Open Plugin Settings"),
		FText::FromString("Navigate to the JsonAsAsset plugin settings"),
#if ENGINE_UE5
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Settings"),
#else
		FSlateIcon(FEditorStyle::GetStyleSetName(), "ProjectSettings.TabIcon"),
#endif
		FUIAction(
			FExecuteAction::CreateLambda([this]() {
				/* Send user to plugin settings */
				FModuleManager::LoadModuleChecked<ISettingsModule>("Settings")
					.ShowViewer("Editor", "Plugins", "JsonAsAsset");
			})
		),
		NAME_None
	);
	MenuBuilder.AddMenuEntry(
		FText::FromString("Open Message Log"),
		FText::FromString("View message logs of JsonAsAsset"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "MessageLog.TabIcon"),
		FUIAction(
			FExecuteAction::CreateLambda([this] {
				FMessageLog MessageLogger = FMessageLog(FName("JsonAsAsset"));
				MessageLogger.Open(EMessageSeverity::Info, true);
			})
		),
		NAME_None
	);
}
