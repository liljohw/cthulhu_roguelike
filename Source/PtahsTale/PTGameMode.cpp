#include "PTGameMode.h"

#include "PTPlayerCharacter.h"
#include "PTPlayerController.h"

APTGameMode::APTGameMode()
{
    DefaultPawnClass = APTPlayerCharacter::StaticClass();
    PlayerControllerClass = APTPlayerController::StaticClass();
}
