#ifndef COMP_H
#define COMP_H

#include "Node.h"

bool Comp(Node const &a, Node const &b)
{
    return a.freq < b.freq;
}

#endif

