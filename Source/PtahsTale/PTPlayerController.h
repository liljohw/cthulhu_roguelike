#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PTPlayerController.generated.h"

UCLASS()
class THE_PTAH_TALE_API APTPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    APTPlayerController();

protected:
    virtual void SetupInputComponent() override;

private:
    void PrimaryAction();
};
