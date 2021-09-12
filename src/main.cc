/*

                                                __         
                                               /\ \  __    
   __     ___    __  _         __     __  __   \_\ \/\_\   
 /'__`\ /' _ `\ /\ \/'\      /'__`\  /\ \/\ \  /'_` \/\ \  
/\ \L\ \/\ \/\ \\/>  </     /\ \L\.\_\ \ \_\ \/\ \L\ \ \ \ 
\ \___, \ \_\ \_\/\_/\_\    \ \__/.\_\\ \____/\ \___,_\ \_\
 \/___/\ \/_/\/_/\//\/_/     \/__/\/_/ \/___/  \/__,_ /\/_/
      \ \_\                                                
       \/_/                                                

# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "utils/debug.hh"
#include "modules/com_stack.hh"
#include "modules/keyboard/ipc_ch8.hh"
#include "modules/keyboard/ps2.hh"
#include "modules/lmgr.hh"
#include "modules/screen.hh"
#include "modules/audi.hh"

#include "playground.cc" // TEMP!

int main(int argc, char *argv[])
{
  ComStack comStack;
  Screen screen(&comStack);
  Audi audi(&comStack);
#ifdef ARCH_SHLE
  IpcCh8 keyboard;
#else
  Ps2 keyboard;
#endif
  keyboard.init();

#ifdef ARCH_SHLE
  const int lmgrParams0 = 40;
  int lmgrParams[3] = {lmgrParams0, 16, 19};
  comStack.connect();
#endif
  screen.init();

  prepare();
  for (int xd = 0; xd < 100; xd++)
  {
    if (keyboard.isExitPressed())
      break;
    if (xd % 20 == 0)
      logMessage("Im here!");
    draw(screen);
  }
  dispose();

#ifdef ARCH_SHLE
  screen.updateVfb();
  audi.unknown(40);
  audi.talkToLayerManager(lmgrParams, 3, 0);
#endif

  keyboard.dispose();
  screen.uninit();

#ifdef ARCH_SHLE
  comStack.disconnect();
#endif

  return 0;
}
