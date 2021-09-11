/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_CLASS_
#define _QNX_AUDI_CLASS_

#include "modules/lmgr.hh"

/** 
 * Class responsible for communication with Audi.
 * Contains other reversed functions from Audi's libraries.
 */
class Audi
{

public:
    Audi(ComStack *comStack);
    ~Audi();

    // ----
    //  Other
    // ----

    void talkToLayerManager(int *inputData, const int inputDataSize, const int param3);

    void getKey();

private:
    ComStack *m_comStack;
};

#endif