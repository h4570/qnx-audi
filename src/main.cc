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
#include "external/lmgr.h"

int main(int argc, char *argv[])
{
  int lmgrParam1[3] = {40, 16, 19};
  unsigned int lmgrParam2, lmgrParam3 = 0;
  int sid[3];

  // gf_dev_attach
  // gf_display_attach
  comStackConnect();
  lmgrCheckVersion();
  lmgrRegisterDisplayable(lmgrParam1[0], lmgrParam2, lmgrParam3, 2);
  lmgrGetVfb(lmgrParam1[0], sid);
  // gf_context_create
  // gf_surface_attach_by_sid
  // OPENGL - DRAW
  lmgrUpdateVfb(lmgrParam1[0]);
  lmgrTalkToLayerManager(lmgrParam1, 3, 0);
  comStackDisconnect();

  return 0;
}
