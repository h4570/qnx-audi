/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_CONFIG_
#define _QNX_CONFIG_

#define AUDI_SD_PATH "/mnt/sdcard10t12"
#define AUDI_LOGS_FILE AUDI_SD_PATH "/logs/log.txt"

#define PC_ASSETS_PATH "/proj"
#define AUDI_ASSETS_PATH "/mnt/sdcard10t12/assets"

#ifdef TARGET_AUDI
#define ASSETS_PATH AUDI_ASSETS_PATH;
#else
#define ASSETS_PATH PC_ASSETS_PATH;
#endif

#endif