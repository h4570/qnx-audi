/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "utils/debug.hh"

#ifdef NDEBUG

// ----
// Release mode, all
// ----

#ifdef TARGET_PC

// ----
// Release mode, x86
// ----

void Debug::_assert(const bool &t_condition, const char *t_message, const char *t_file, const int &t_line) {}
void Debug::_log(const char *t_message, const char *t_file, const int &t_line) {}
void Debug::_log(const char *t_key, const int t_value, const char *t_file, const int &t_line) {}
void Debug::_log(const char *t_key, const unsigned int t_value, const char *t_file, const int &t_line) {}
void Debug::_log(const char *t_key, const bool t_value, const char *t_file, const int &t_line) {}
void Debug::_log(const char *t_key, const char *t_value, const char *t_file, const int &t_line) {}

#else // TARGET_PC

// ----
// Release mode, SHLE
// ----

void Debug::_assert(const bool &t_condition, const char *t_message, const char *t_file, const int &t_line) {}
void Debug::_log(const char *t_message, const char *t_file, const int &t_line) {}
void Debug::_log(const char *t_key, const int t_value, const char *t_file, const int &t_line) {}
void Debug::_log(const char *t_key, const unsigned int t_value, const char *t_file, const int &t_line) {}
void Debug::_log(const char *t_key, const bool t_value, const char *t_file, const int &t_line) {}
void Debug::_log(const char *t_key, const char *t_value, const char *t_file, const int &t_line) {}

#endif // TARGET_PC
#else  // NDEBUG

// ----
// Debug mode, all
// ----

#include <stdlib.h>
#include <stdio.h>
#include <GLES/gl.h>

void Debug::_checkOpenGLError(const char *t_statement, const char *t_name, const int &t_line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        printf("OpenGL error %08x, at %s:%i - for %s\n", err, t_name, t_line, t_statement);
        exit(1);
    }
}

#ifdef TARGET_PC

// ----
// Debug mode, x86
// ----

void Debug::_assert(const bool &t_condition, const char *t_message, const char *t_file, const int &t_line)
{
    if (!t_condition)
    {
        fprintf(stdout, "Assertion failed: %s | %s:%d\n", t_message, t_file, t_line);
        fprintf(stderr, "Assertion failed: %s | %s:%d\n", t_message, t_file, t_line);
        exit(1);
    }
}

void Debug::_log(const char *t_message, const char *t_file, const int &t_line)
{
    fprintf(stdout, "Log: %s | %s:%d\n", t_message, t_file, t_line);
}

void Debug::_log(const char *t_key, const int t_value, const char *t_file, const int &t_line)
{
    fprintf(stdout, "Log: %s = %d | %s:%d\n", t_key, t_value, t_file, t_line);
}

void Debug::_log(const char *t_key, const unsigned int t_value, const char *t_file, const int &t_line)
{
    fprintf(stdout, "Log: %s = %d | %s:%d\n", t_key, t_value, t_file, t_line);
}

void Debug::_log(const char *t_key, const bool t_value, const char *t_file, const int &t_line)
{
    fprintf(stdout, "Log: %s = %d | %s:%d\n", t_key, t_value, t_file, t_line);
}

void Debug::_log(const char *t_key, const char *t_value, const char *t_file, const int &t_line)
{
    fprintf(stdout, "Log: %s = %s | %s:%d\n", t_key, t_value, t_file, t_line);
}

#else // TARGET_PC

// ----
// Debug mode, SHLE
// ----

#include <fstream>
#include "config.hh"

void Debug::_assert(const bool &t_condition, const char *t_message, const char *t_file, const int &t_line)
{
    if (!t_condition)
    {
        std::ofstream myfile;
        myfile.open(AUDI_LOGS_FILE, std::ios_base::app);
        myfile << "Assertion failed: " << t_message << " | " << t_file << ":" << t_line << "\n";
        myfile.close();
        exit(1);
    }
}

void Debug::_log(const char *t_message, const char *t_file, const int &t_line)
{
    std::ofstream myfile;
    myfile.open(AUDI_LOGS_FILE, std::ios_base::app);
    myfile << "Log: " << t_message << " | " << t_file << ":" << t_line << "\n";
    myfile.close();
}

void Debug::_log(const char *t_key, const int t_value, const char *t_file, const int &t_line)
{
    std::ofstream myfile;
    myfile.open(AUDI_LOGS_FILE, std::ios_base::app);
    myfile << "Log: " << t_key << " = " << t_value << " | " << t_file << ":" << t_line << "\n";
    myfile.close();
}

void Debug::_log(const char *t_key, const unsigned int t_value, const char *t_file, const int &t_line)
{
    std::ofstream myfile;
    myfile.open(AUDI_LOGS_FILE, std::ios_base::app);
    myfile << "Log: " << t_key << " = " << t_value << " | " << t_file << ":" << t_line << "\n";
    myfile.close();
}

void Debug::_log(const char *t_key, const bool t_value, const char *t_file, const int &t_line)
{
    std::ofstream myfile;
    myfile.open(AUDI_LOGS_FILE, std::ios_base::app);
    myfile << "Log: " << t_key << " = " << t_value << " | " << t_file << ":" << t_line << "\n";
    myfile.close();
}

void Debug::_log(const char *t_key, const char *t_value, const char *t_file, const int &t_line)
{
    std::ofstream myfile;
    myfile.open(AUDI_LOGS_FILE, std::ios_base::app);
    myfile << "Log: " << t_key << " = " << t_value << " | " << t_file << ":" << t_line << "\n";
    myfile.close();
}

#endif // TARGET_PC
#endif // NDEBUG