#include "Log/CrazyLog.h"

#include "Widgets/Notifications/SNotificationList.h"
#include "FrameWork/Notifications/NotificationManager.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY(LogCrazyUAsset);

void CrazyLogOnly(const FString& Message, int MessageTypeIdx)
{
	if (MessageTypeIdx > 0)
	{
		UE_LOG(LogCrazyUAsset, Log, TEXT("%s"), *Message);
	}
	else if(MessageTypeIdx < 0)
	{
		UE_LOG(LogCrazyUAsset, Warning, TEXT("%s"), *Message);
	}
	else
	{
		UE_LOG(LogCrazyUAsset, Error, TEXT("%s"), *Message);
	}	
}

// Screen Debug

void CrazyScreenMessage(const FString& Message, const FColor& Color)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.f, Color, Message);
	}
}

void CrazyScreenMessageWithLog(const FString& Message, const FColor& Color)
{
	CrazyScreenMessage(Message, Color);
	CrazyLogOnly(Message);
}

// Dialog Debug

EAppReturnType::Type CrazyDialogMessage(EAppMsgType::Type MsgType, const FString& Message, int MessageTypeIdx)
{
	FString title;

	if (MessageTypeIdx > 0)
	{
		title = TEXT("TIP");
	}
	else if (MessageTypeIdx < 0)
	{
		title = TEXT("WARNING");
	}
	else
	{
		title = TEXT("ERROR!!!");
	}

	return FMessageDialog::Open(MsgType, FText::FromString(Message), FText::FromString(title));
}

EAppReturnType::Type CrazyDialogMessageWithLog(EAppMsgType::Type MsgType, const FString& Message, int MessageTypeIdx)
{
	CrazyLogOnly(Message, MessageTypeIdx);

	return CrazyDialogMessage(MsgType, Message, MessageTypeIdx);
}

// Notification Debug

void CrazyNotificationMessage(const FString& Message)
{
	FNotificationInfo NotifyInfo(FText::FromString(Message));
	NotifyInfo.bUseLargeFont = true;
	NotifyInfo.FadeOutDuration = 7.f;

	FSlateNotificationManager::Get().AddNotification(NotifyInfo);
}

void CrazyNotificationMessageWithLog(const FString& Message, int MessageTypeIdx)
{
	CrazyNotificationMessage(Message);
	CrazyLogOnly(Message, MessageTypeIdx);
}
