#pragma once

DECLARE_LOG_CATEGORY_EXTERN(CrazyUAssetLog, Verbose, All);

/*
* MessageTypeIdx > 0 Tips
* MessageTypeIdx < 0 Warning
* else Error!!!
*/
void CrazyLogOnly(const FString& Message, int MessageTypeIdx = 1);

// Screen Debug

void CrazyScreenMessage(const FString& Message, const FColor& Color = FColor::Cyan);

void CrazyScreenMessageWithLog(const FString& Message, const FColor& Color = FColor::Cyan);

// Dialog Debug

/*
* MessageTypeIdx > 0 Tips
* MessageTypeIdx < 0 Warning
* else Error!!!
*/
EAppReturnType::Type CrazyDialogMessage(EAppMsgType::Type MsgType, const FString& Message, int MessageTypeIdx = 1);

/*
* MessageTypeIdx > 0 Tips
* MessageTypeIdx < 0 Warning
* else Error!!!
*/
EAppReturnType::Type CrazyDialogMessageWithLog(EAppMsgType::Type MsgType, const FString& Message, int MessageTypeIdx = 1);

// Notification Debug

void CrazyNotificationMessage(const FString& Message);

/*
* MessageTypeIdx > 0 Tips
* MessageTypeIdx < 0 Warning
* else Error!!!
*/
void CrazyNotificationMessageWithLog(const FString& Message, int MessageTypeIdx = 1);
