#include "ImgManager.h"

//include all the images
#include "images/background.h"
#include "images/board.h"
#include "images/tiger.h"
#include "images/goat.h"
#include "images/selector.h"
#include "images/selectorhighlight.h"
#include "images/tigerIcon.h"
#include "images/lastmove.h"
#include "images/mainMenu/back.h"
#include "images/mainMenu/backH.h"
#include "images/mainMenu/credits.h"
#include "images/mainMenu/creditsH.h"
#include "images/mainMenu/creditsText.h"
#include "images/mainMenu/exit.h"
#include "images/mainMenu/exitH.h"
#include "images/mainMenu/humanVsGoat.h"
#include "images/mainMenu/humanVsGoatH.h"
#include "images/mainMenu/humanVsTiger.h"
#include "images/mainMenu/humanVsTigerH.h"
#include "images/mainMenu/humanVshuman.h"
#include "images/mainMenu/humanVshumanH.h"
#include "images/mainMenu/mmbase.h"
#include "images/mainMenu/levels/l1.h"
#include "images/mainMenu/levels/l2.h"
#include "images/mainMenu/levels/l3.h"
#include "images/mainMenu/levels/l4.h"
#include "images/mainMenu/levels/l5.h"
#include "images/mainMenu/levels/l1H.h"
#include "images/mainMenu/levels/l2H.h"
#include "images/mainMenu/levels/l3H.h"
#include "images/mainMenu/levels/l4H.h"
#include "images/mainMenu/levels/l5H.h"

bool ImgManager::LoadImages()
{
    if (!boardimg.LoadFromMemory(board_png, board_png_size)    ||
            !backgroundimg.LoadFromMemory(background_png, background_png_size)   ||
            !selectorimg.LoadFromMemory(selector_png, selector_png_size)   ||
            !highlightimg.LoadFromMemory(selectorhighlight_png, selectorhighlight_png_size) ||
            !lastmoveimg.LoadFromMemory(lastmove_png, lastmove_png_size)   ||
            !tigerimg.LoadFromMemory(tiger_png, tiger_png_size) ||
            !goatimg.LoadFromMemory(goat_png, goat_png_size) ||
            !iconimg.LoadFromMemory(tigericon_png, tigericon_png_size) ||
            !mmBase.LoadFromMemory(mmbase_png, mmbase_png_size) ||
            !mmGoat.LoadFromMemory(humanVsGoat_png, humanVsGoat_png_size) ||
            !mmGoatH.LoadFromMemory(humanvsgoatH_png, humanvsgoatH_png_size) ||
            !mmTiger.LoadFromMemory(humanVsTiger_png, humanVsTiger_png_size) ||
            !mmTigerH.LoadFromMemory(humanvstigerH_png, humanvstigerH_png_size) ||
            !mmHuman.LoadFromMemory(humanVsHuman_png, humanVsHuman_png_size) ||
            !mmHumanH.LoadFromMemory(humanvshumanH_png, humanvshumanH_png_size) ||
            !mmExit.LoadFromMemory(exit_png, exit_png_size) ||
            !mmExitH.LoadFromMemory(exitH_png, exitH_png_size) ||
            !mmCredits.LoadFromMemory(credits_png, credits_png_size) ||
            !mmCreditsH.LoadFromMemory(creditsH_png, creditsH_png_size) ||
            !mmCreditsText.LoadFromMemory(creditstext_png, creditstext_png_size) ||
            !mmBack.LoadFromMemory(back_png, back_png_size) ||
            !mmBackH.LoadFromMemory(backH_png, backH_png_size) ||
            !l1.LoadFromMemory(l1_png, l1_png_size) ||
            !l2.LoadFromMemory(l2_png, l2_png_size) ||
            !l3.LoadFromMemory(l3_png, l3_png_size) ||
            !l4.LoadFromMemory(l4_png, l4_png_size) ||
            !l5.LoadFromMemory(l5_png, l5_png_size) ||
            !l1H.LoadFromMemory(l1H_png, l1H_png_size) ||
            !l2H.LoadFromMemory(l2H_png, l2H_png_size) ||
            !l3H.LoadFromMemory(l3H_png, l3H_png_size) ||
            !l4H.LoadFromMemory(l4H_png, l4H_png_size) ||
            !l5H.LoadFromMemory(l5H_png, l5H_png_size))
    {
        return false;
    }
    return true;
}
