/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_DEBUG_
#define _QNX_AUDI_DEBUG_

#include <stdio.h>

/** Static class with standard debug features, like assert, log, etc. */
class Debug
{

public:
    static void _assert(const bool &t_condition, const char *t_message, const char *t_file, const int &t_line);
    static void _log(const char *t_message, const char *t_file, const int &t_line);

    static void _log(const char *t_key, const int value, const char *t_file, const int &t_line);
    static void _log(const char *t_key, const unsigned int value, const char *t_file, const int &t_line);
    static void _log(const char *t_key, const bool value, const char *t_file, const int &t_line);

    static void _checkOpenGLError(const char *t_statement, const char *t_name, const int &t_line);
};

// ----
// Helper macros
// ----

#define assert(condition, message) Debug::_assert(condition, message, __FILE__, __LINE__)
#define logMessage(message) Debug::_log(message, __FILE__, __LINE__)
#define logKeyValue(key, value) Debug::_log(key, value, __FILE__, __LINE__)

#ifdef NDEBUG

// ----
// Release mode
// ----

#define GL_CHECK(stmt) stmt

#else // NDEBUG

// ----
// Debug mode
// ----

#define GL_CHECK(stmt)                                       \
    do                                                       \
    {                                                        \
        stmt;                                                \
        Debug::_checkOpenGLError(#stmt, __FILE__, __LINE__); \
    } while (0)

#endif // NDEBUG

#endif // _QNX_AUDI_DEBUG_