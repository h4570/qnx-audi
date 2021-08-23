/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_EXAMPLE_
#define _QNX_AUDI_EXAMPLE_

#include <iostream>

/** 
 * TODO
 */
class Example
{

public:
    Example();
    ~Example();

    float example2;

    // ----
    // Getters
    // ----

    /** TODO */
    const float &getExample() const { return example; };

    // ----
    //  Setters
    // ----

    /** TODO */
    void setExample(const float &t_val) { example = t_val; }

    // ----
    //  Other
    // ----

private:
    float example;
    void doSomething(const float &t_val);
};

#endif