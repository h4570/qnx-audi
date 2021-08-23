/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_DEBUG_
#define _QNX_AUDI_DEBUG_

/** Static class with standard debug features, like assert, log, etc. */
class Debug
{

public:
    static void _assert(const bool &t_condition, const char *t_message, const char *t_file, const int &t_line);
    static void _log(const char *t_message, const char *t_file, const int &t_line);
};

// ----
// Helper macros
// ----

#define assert(condition, message) Debug::_assert(condition, message, __FILE__, __LINE__)
#define log(message) Debug::_log(message, __FILE__, __LINE__)

#endif