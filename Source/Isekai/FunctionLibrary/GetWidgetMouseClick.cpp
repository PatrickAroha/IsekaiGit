#include "GetWidgetMouseClick.h"
#include "Blueprint/UserWidget.h"
#include "Slate/SObjectWidget.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Engine.h"
#include "Framework/Application/SlateApplication.h"

UUserWidget* UGetWidgetMouseClick::GetWidgetUnderCursor(APlayerController* PC, bool& bIsSlotInventory)
{
    bIsSlotInventory = false;

    if (!PC) return nullptr;

    // Pega a posição ABSOLUTA do mouse direto do Slate (desktop coords)
    FVector2D AbsolutePos = FSlateApplication::Get().GetCursorPos();

    // Faz o hit-test no Slate
    FWidgetPath WidgetPath = FSlateApplication::Get().LocateWindowUnderMouse(
        AbsolutePos,
        FSlateApplication::Get().GetInteractiveTopLevelWindows()
    );

    if (WidgetPath.IsValid() && WidgetPath.Widgets.Num() > 0)
    {
        // percorre de trás pra frente até achar um UserWidget
        for (int32 i = WidgetPath.Widgets.Num() - 1; i >= 0; --i)
        {
            const FArrangedWidget& ArrangedWidget = WidgetPath.Widgets[i];
            TSharedRef<SWidget> SlateWidget = ArrangedWidget.Widget;

            if (SlateWidget->GetTypeAsString() == "SObjectWidget")
            {
                TSharedPtr<SObjectWidget> ObjWidget = StaticCastSharedRef<SObjectWidget>(SlateWidget);
                if (UUserWidget* UserWidget = ObjWidget->GetWidgetObject())
                {
                    // 🔹 Só marca true se for W_SlotInventory
                    FString ClassName = UserWidget->GetClass()->GetName();
                    if (ClassName.Contains(TEXT("W_SlotInventory")))
                    {
                        bIsSlotInventory = true;
                        return UserWidget;
                    }
                    if (ClassName.Contains(TEXT("W_Equipment")))
                    {
                        bIsSlotInventory = false;
                        return UserWidget;
                    }
                }
            }
        }
    }
    return nullptr; // nada sob o cursor
}
