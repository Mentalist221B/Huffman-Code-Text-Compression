#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "Minheap.h"

void hufftree()
{
    Node *top, *left, *right, *lnode, *rnode;
        while(1)
        {
            left = extractMin();

            lnode = new Node;
            lnode->left = left->left;
            lnode->right = left->right;
            lnode->freq = left->freq;
            lnode->id = left->id;

            std::cout<<lnode->freq<<" "<<lnode->id<<"\t";

            minheap[1] = minheap[position-1];
            position--;
            sinkDown(1);

            right = extractMin();

            rnode = new Node;
            rnode->left = right->left;
            rnode->right = right->right;
            rnode->freq = right->freq;
            rnode->id = right->id;
            std::cout<<rnode->freq<<" "<<rnode->id<<"\n";

            minheap[1] = minheap[position-1];
            position--;
            sinkDown(1);

            if(left->freq == 0 || right->freq == 0)
            {
                break;
            }

            top = new Node;

            top->left = lnode;
            top->right = rnode;
            top->id = '$';
            top->freq = lnode->freq + rnode->freq;

            insertn(*top);
        }

        std::cout<<"\n\n\n";
        display(top, "");
}

#endif
