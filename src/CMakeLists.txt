﻿file (GLOB_RECURSE MY_SOURCE_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.cpp)
target_sources (${CMAKE_PROJECT_NAME} PRIVATE ${MY_SOURCE_FILES} "../include/StateMachine.h" "../include/Animation.h" "../include/Camera.h" "../include/Resources.h"
"../include/Tile.h" "../include/Level.h" 
"../include/entity/Entity.h" "../include/entity/Player.h"

"../include/states/StartState.h" "../include/states/BaseState.h" "../include/states/PlayState.h"
"../include/guis/Gui.h" "../include/world/TilesMap.h" "../include/utilities.h" "../include/PhysicsMove.h"
"../include/states/FadeInState.h" "../include/states/FadeOutState.h" "../include/states/TransitionState.h" "../include/states/StartMenuState.h" "../include/guis/ProgressBar.h"
"../include/guis/Button.h" "../include/Game.h" "../include/Stack.h" "../include/Utilities/StartMenuOptions.h" "../include/Utilities/Fades.h" "../include/tileson/tileson.hpp" "../include/Pokemon/Pokemon.h" "../include/Pokemon/Party.h" "../include/Pokemon/PokemonFactory.h" "../include/states/EncounterBattleState.h" "../include/states/BattleDialogState.h" "../include/Battle.h" "../include/SoundTon.h" "../include/states/TakeTurnState.h" "../include/states/TakeDamageState.h" "../include/states/AddExpState.h" "../include/states/PlayerMenuState.h" "../include/states/PokemonMenuState.h" "../include/states/ChoosePokemonState.h"   "../include/states/GuideState.h")
