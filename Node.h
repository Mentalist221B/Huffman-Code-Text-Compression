#ifndef NODE_H
#define NODE_H

#include<string>

class Node
{
    public:

    unsigned int freq;
    char id;
    std::string line;
    Node *left;
    Node *right;

    Node()
    {
        freq = 0;
        left = NULL;
        right = NULL;
    }
};

#endif

