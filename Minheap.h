#ifndef MINHEAP_H
#define MINHEAP_H

#include "Node.h"

int r = 0;
Node minheap[97], code[97];
int position = 0, root = 1, last;

void bubbleUp();
void sinkDown(int);
void swap_a(int , int );

void insertn(Node x)
{
    if(position==0)
    {
        minheap[position+1] = x;
        position = 2;
        last++;
    }
    else
    {
        minheap[position++] = x;
        last++;
        bubbleUp();
    }
}

void bubbleUp()
{
		int pos = position-1;

		while(pos>0 && minheap[pos/2].freq > minheap[pos].freq)
        {
			Node y = minheap[pos];
			minheap[pos] = minheap[pos/2];
			minheap[pos/2] = y;
			pos = pos/2;
		}
}

Node *extractMin()
{
		Node *minm;
		minm = &minheap[1];
		return minm;
}

void sinkDown(int k)
{
        Node a = minheap[k];
		int smallest =k;
		if(2*k<position && minheap[smallest].freq > minheap[2*k].freq)
        {
			smallest = 2*k;
		}
		if(2*k+1<position && minheap[smallest].freq > minheap[2*k+1].freq)
		{
			smallest = 2*k+1;
		}
		if(smallest!=k)
		{
			swap_a(k,smallest);
			sinkDown(smallest);
		}

	}

void swap_a(int a, int b)
{
		Node temp = minheap[a];
		minheap[a] = minheap[b];
		minheap[b] = temp;
}

void display(Node* root, std::string str)
{
    if (root == NULL)
    {
       return;
    }
    else
    {
        root->line = str;

        if(root->id != '$')
        {
            code[r] = *root;
            r++;
        }
    }


    display(root->left, str+"0");
    display(root->right, str+"1");
}

#endif


