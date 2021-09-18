/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "utils/string.hh"
#include "utils/debug.hh"
#include <sstream>
#include <string.h>

char *intToChar(int t_number)
{
    std::stringstream ss;
    ss << t_number;
    char *result = new char[ss.str().length() + 1];
    strcpy(result, ss.str().c_str());
    return result;
}