#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;

int r = 0;

class Node
{
    public:

    unsigned int freq;
    char id;
    string line;
    Node *left;
    Node *right;

    Node()
    {
        freq = 0;
        left = NULL;
        right = NULL;
    }
};

Node minheap[97], code[97];
int position = 0, root = 1, last;

void bubbleUp();
void sinkDown(int);
void swap_a(int , int );

bool Comp(Node const &a, Node const &b)
{
    return a.freq < b.freq;
}

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

void display(Node* root, string str)
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

int main()
{
    int inp, p=0, q=1;
    Node leaf[96], *top, *left, *right, *lnode, *rnode;
    char c;
    ifstream text;
    ofstream huff;

    text.open("abc.txt", ios::in);

    if(text.is_open())
    {
        while(text.get(c))
        {
            inp = c-32;

            if(inp == -22)
            {
                inp = 95;

                leaf[inp].freq++;
                leaf[inp].id = '\n';

                continue;
            }

            if(inp >= 0 && inp <= 94)
            {
                leaf[inp].freq++;
                leaf[inp].id = inp + 32;
            }
        }

        stable_sort(leaf, leaf+96, Comp);

        while(leaf[p].freq == 0)
        {
            p++;
        }

        for(q=1; p<96; q++)
        {
            minheap[q] = leaf[p];
            cout<<minheap[q].id<<" "<<minheap[q].freq<<"\n";
            p++;
        }

        last = q;
        position = q;

        while(1)
        {
            left = extractMin();

            lnode = new Node;
            lnode->left = left->left;
            lnode->right = left->right;
            lnode->freq = left->freq;
            lnode->id = left->id;

            cout<<lnode->freq<<" "<<lnode->id<<"\t";

            minheap[1] = minheap[position-1];
            position--;
            sinkDown(1);

            right = extractMin();

            rnode = new Node;
            rnode->left = right->left;
            rnode->right = right->right;
            rnode->freq = right->freq;
            rnode->id = right->id;
            cout<<rnode->freq<<" "<<rnode->id<<"\n";

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

        cout<<"\n\n\n";
        display(top, "");

        for(int i=0; i<r; i++)
        {
            cout<<"\n"<<code[i].id<<" = "<<code[i].freq<<" = "<<code[i].line;
        }

    }
    else
    {
        cout<<"Error in opening file!";
    }

    return 0;
}
