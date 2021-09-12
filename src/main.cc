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
#include "modules/ipc_ch8.hh"
#include "modules/lmgr.hh"
#include "modules/screen.hh"
#include "modules/audi.hh"

#include "playground.cc" // TEMP!

int main(int argc, char *argv[])
{
  ComStack comStack;
  Screen screen(&comStack);
  Audi audi(&comStack);
  IpcCh8 ipcCh8;

#ifdef ARCH_SHLE
  const int lmgrParams0 = 40;
  int lmgrParams[3] = {lmgrParams0, 16, 19};
  comStack.connect();
#endif
  screen.init();

  // draw(screen);

#ifdef ARCH_SHLE
  screen.updateVfb();
  audi.unknown(40);
  audi.talkToLayerManager(lmgrParams, 3, 0);
  // ipcCh8.connect();
  // KeyboardEvent key = ipcCh8.waitForKey();
  // if (key == Left)
  //   logMessage("Left");
  // else if (key == Right)
  //   logMessage("Right");
  // else if (key == Undefined)
  //   logMessage("Undefined");
  // ipcCh8.disconnect();
#endif

  screen.uninit();
#ifdef ARCH_SHLE
  comStack.disconnect();
#endif

  return 0;
}
