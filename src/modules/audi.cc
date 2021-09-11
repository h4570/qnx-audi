/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "modules/audi.hh"
#include "utils/debug.hh"

// ----
// Constructors/Destructors
// ----

Audi::Audi(ComStack *comStack) : m_comStack(comStack) {}

Audi::~Audi() {}

// ----
// Methods
// ----

void Audi::talkToLayerManager(int *inputData, const int inputDataSize, const int param3)
{
    const int command = 0x800c0505;
    int dwords = (2 + inputDataSize) * 4;
    if (inputDataSize == 0)
        dwords = 3;

    assert(inputDataSize == 0 || inputData != NULL, "talkToLayerManager failed: Wrong input parameter!");

    int *data = new int[dwords];
    assert(data != NULL, "talkToLayerManager failed: Out of memory!");
    data[0] = param3;
    data[1] = inputDataSize;

    if (inputDataSize == 0)
        data[2] = 0;
    else
        for (int i = 0; i < inputDataSize; i++)
            data[2 + i] = inputData[i];

    m_comStack->send(command, data, dwords * 4);
    delete[] data;
    logMessage("[Audi] - talkToLayerManager: Success!");
}

void Audi::unknown(const int param)
{
    const int command = 0x80040501;
    const int dwords = 1;
    int data[dwords] = {param};

    m_comStack->send(command, data, dwords * 4);
    logMessage("[Audi] - unknown: Success!");
}
