//
// Created by lr6549 on 4/2/26.
//

/**
            ,----,
          ,/   .`|                                                                                                                                                                                                                                           .--,-``-.    ,-.----.   ,-.----.
        ,`   .'  :  ,---,                                  ,-.                                                          ,---,.                                                                                                                      ,--,    /   /     '.  \    /  \  \    /  \
      ;    ;     /,--.' |                              ,--/ /|                 ,---,                                  ,'  .' |                                    ,--,               ,--,                                                    ,---,,--.'|   / ../        ; |   :    \ |   :    \
    .'___,/    ,' |  |  :                      ,---, ,--. :/ |                /_ ./|   ,---.           ,--,         ,---.'   |   ,---.    __  ,-.               ,'_ /|             ,--.'|         ,---,                                    ,---.'||  | :   \ ``\  .`-    '|   |  .\ :|   |  .\ :
    |    :     |  :  :  :                  ,-+-. /  |:  : ' /           ,---, |  ' :  '   ,'\        ,'_ /|         |   |   .'  '   ,'\ ,' ,'/ /|          .--. |  | :   .--.--.   |  |,      ,-+-. /  |  ,----._,.          .--.--.       |   | ::  : '    \___\/   \   :.   :  |: |.   :  |: |
    ;    |.';  ;  :  |  |,--.  ,--.--.    ,--.'|'   ||  '  /           /___/ \.  : | /   /   |  .--. |  | :         :   :  :   /   /   |'  | |' |        ,'_ /| :  . |  /  /    '  `--'_     ,--.'|'   | /   /  ' /         /  /    '      |   | ||  ' |         \   :   ||   |   \ :|   |   \ :
    `----'  |  |  |  :  '   | /       \  |   |  ,"' |'  |  :            .  \  \ ,' '.   ; ,. :,'_ /| :  . |         :   |  |-,.   ; ,. :|  |   ,'        |  ' | |  . . |  :  /`./  ,' ,'|   |   |  ,"' ||   :     |        |  :  /`./    ,--.__| |'  | |         /  /   / |   : .   /|   : .   /
        '   :  ;  |  |   /' :.--.  .-. | |   | /  | ||  |   \            \  ;  `  ,''   | |: :|  ' | |  . .         |   :  ;/|'   | |: :'  :  /          |  | ' |  | | |  :  ;_    '  | |   |   | /  | ||   | .\  .        |  :  ;_     /   ,'   ||  | :         \  \   \ ;   | |`-' ;   | |`-'
        |   |  '  '  :  | | | \__\/: . . |   | |  | |'  : |. \            \  \    ' '   | .; :|  | ' |  | |         |   |   .''   | .; :|  | '           :  | | :  ' ;  \  \    `. |  | :   |   | |  | |.   ; ';  |         \  \    `. .   '  /  |'  : |__   ___ /   :   ||   | ;    |   | ;
        '   :  |  |  |  ' | : ," .--.; | |   | |  |/ |  | ' \ \            '  \   | |   :    |:  | : ;  ; |         '   :  '  |   :    |;  : |           |  ; ' |  | '   `----.   \'  : |__ |   | |  |/ '   .   . |          `----.   \'   ; |:  ||  | '.'| /   /\   /   ::   ' |    :   ' |
        ;   |.'   |  :  :_:,'/  /  ,.  | |   | |--'  '  : |--'              \  ;  ;  \   \  / '  :  `--'   \        |   |  |   \   \  / |  , ;           :  | : ;  ; |  /  /`--'  /|  | '.'||   | |--'   `---`-'| |         /  /`--'  /|   | '/  ';  :    ;/ ,,/  ',-    .:   : :    :   : :
        '---'     |  | ,'   ;  :   .'   \|   |/      ;  |,'                  :  \  \  `----'  :  ,      .-./        |   :  \    `----'   ---'            '  :  `--'   \'--'.     / ;  :    ;|   |/       .'__/\_: |        '--'.     / |   :    :||  ,   / \ ''\        ; |   | :    |   | :
                  `--''     |  ,     .-./'---'       '--'                     \  ' ;           `--`----'            |   | ,'                             :  ,      .-./  `--'---'  |  ,   / '---'        |   :    :          `--'---'   \   \  /   ---`-'   \   \     .'  `---'.|    `---'.|
                             `--`---'                                          `--`                                 `----'                                `--`----'                 ---`-'                \   \  /                       `----'              `--`-,,-'      `---`      `---`
                                                                                                                                                                                                           `--`-'
 */

#ifndef SDL3PP_LIBRARY_H
#define SDL3PP_LIBRARY_H

#include <thread>

//* Defines And Error Check
#if !defined(SDL3PP_ALL) && !defined(SDL3PP_AudioHandler) && !defined(SDL3PP_TextRenderer) && !defined(SDL3PP_TextureHandler) && !defined(SDL3PP_WidgetHandler)
    #error "No SDL3PP modules selected"
#endif

#if defined(SDL3PP_ALL) || defined(SDL3PP_AudioHandler) //? Finished Implementation
    #include "SDL3++AudioHandler/AudioHandler.hpp"
#endif

#if defined(SDL3PP_ALL) || defined(SDL3PP_TextRenderer) //? Finished Implementation
    #include "SDL3++TextRenderer/TextRenderer.hpp"
#endif

#if defined(SDL3PP_ALL) || defined(SDL3PP_TextureHandler) //? Finished Implementation
    #include "SDL3++TextureHandler/TextureHandler.hpp"
#endif

#if defined(SDL3PP_ALL) || defined(SDL3PP_WidgetHandler)
    #include "SDL3++WidgetHandler/WidgetHandler.hpp"
#endif

bool initSDL3PP();      //! call all init functions! like in update

void updateSDL3PP();    //! call all update functions of widgets etc!

namespace JFLX::sdl3PP {
    inline void voidNullptr() {}
}

#endif // SDL3PP_LIBRARY_H