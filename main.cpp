#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<sstream>

#include "Node.h"
#include "Compare.h"
#include "Minheap.h"
#include "Hufftree.h"

using namespace std;

void accept(Node *l, ifstream &text)
{
    int inp;
    char c;

    while(text.get(c))
    {
        inp = c-32;

        if(inp == -22)
        {
            inp = 95;

            l[inp].freq++;
            l[inp].id = '\n';

            continue;
        }

        if(inp >= 0 && inp <= 94)
        {
            l[inp].freq++;
            l[inp].id = inp + 32;
        }
    }
}

int main()
{
    int p=0, q=1, letter, temp, a, choice, rem;
    Node leaf[96];
    char block[7], c;
    string line, stri;
    ifstream text;
    fstream huff;
    ofstream out;

    cout<<"\nChoose an option : \n1.Compression\n2.Uncompression\n";
    cin>>choice;
   // cout<<"\nEnter the name of input file: ";


    if(choice == 1)
    {
        text.open("wikipage.txt", ios::in);
        out.open("comptext.txt", ofstream::out|ofstream::trunc);
        huff.open("temp.txt", ofstream::out|ofstream::in|ofstream::trunc);

        accept(leaf,text);

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

        hufftree();

        for(int i=0; i<r; i++)
        {
            cout<<"\n"<<code[i].id<<" = "<<code[i].freq<<" = "<<code[i].line;
        }

        text.clear();
        text.seekg(0,ios::beg);

        out<<r<<"\n";

        for(int i=0; i<r; i++)
        {
            out<<code[i].id<<code[i].line<<"\n";
        }

        while(text.get(c))
        {
            for(int i=0; i<r; i++)
            {
                if(code[i].id == c)
                {
                    huff<<code[i].line;
                    break;
                }
            }
        }

        huff.clear();
        huff.seekg(0,ios::beg);

        letter = 0;
        a=6;

        while(huff.get(c))
        {
            block[6-a] = c;
            temp = c - '0';

            if(temp)
            {
                letter += pow(2,a);
            }

            a--;

            if(a<0)
            {
                c = letter+32;
                out<<c;
                a = 6;
                letter = 0;
            }
        }

        letter = 5 - a;

        if(a<6)
        {
            c = 160;
            out<<c;

            for(int i=0; i<=letter; i++)
            {
                out<<block[i];
            }
        }

        out.close();
        huff.close();
        text.close();

    }
    else if(choice == 2)
    {
        text.open("comptext.txt", ios::in);
        out.open("uncomptext.txt", ofstream::out|ofstream::trunc);
        huff.open("temp.txt", ofstream::out|ofstream::in|ofstream::trunc);

        getline(text,line);
        istringstream iss(line);

        iss >> p;

        for(int i=1; i<=p; i++)
        {
            getline(text,line);

            if(line == "")
            {
                leaf[i].id = '\n';
                getline(text,line);
                leaf[i].line = line;
                continue;
            }

            leaf[i].id = line[0];
            leaf[i].line = line.substr(1);

            cout<<leaf[i].id<<" "<<leaf[i].line<<"\n";
        }

        while(text.get(c))
        {
            q = (unsigned char)c-32;

            if(q == 128)
            {
                break;
            }

            a = 6;

            while(a>=0)
            {
                rem = q%2;
                q /= 2;
                block[a] = rem + '0';
                a--;
            }

            huff<<block;
        }

        while(text.get(c))
        {
            huff<<c;
        }

        huff.clear();
        huff.seekg(0,ios::beg);

        stri = "";

        while(huff.get(c))
        {
            stri += c;

            cout<<stri<<" ";

            for(int i=0; i<=p; i++)
            {
                if(stri == leaf[i].line)
                {
                    out<<leaf[i].id;
                    stri = "";
                    break;
                }
            }
        }

        out.close();
        huff.close();
        text.close();
    }

    return 0;
}
