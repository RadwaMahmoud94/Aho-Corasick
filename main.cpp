#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int CharToInt[256];     //function convert the alphabet to number
char IntToChar[4];      //function convert the number to the char

void InitializeTables()     //like map to Initialize char and these refer numbers
{
    CharToInt['A']=0;
    IntToChar[0]='A';

    CharToInt['C']=1;
    IntToChar[1]='C';

    CharToInt['G']=2;
    IntToChar[2]='G';

    CharToInt['T']=3;
    IntToChar[3]='T';

}
/////////////////////////////////////////////////////////////////////////////////////////////
//create struct node which has 4 child (A,G,C,T) and failuerlink node type and x refer to
struct Node
{
    Node* Child[4];
    Node*FailureLink;
    int x;
};

Node* root;  //the root of trie

/////////////////////////////////////////////////////////////////////////////////////////////

Node* CreateTrieNode() // Create and Initialize Trie Node
{
    Node* node=new Node;
    for(int i=0; i<4; i++)
    {
        node->Child[i]=0;
        node->FailureLink =NULL;
    }

    return node;
}

void InitializeTrie()//create root node
{
    root = CreateTrieNode();

}


void DeleteTrie(Node* node) //delete all nodes in the trie
{
    int i;
    for(i=0; i<4; i++) if(node->Child[i]) DeleteTrie(node->Child[i]);
    delete node;
}
//delete the root node
void DeleteTrie()
{
    DeleteTrie(root);
}
int Id = 0;
void InsertTrieRead(char *readd, int len) // Insert Read r with length len
{
    int i;
    Node *cur_node = root;
    for (i = 0; i < len; i++)
    {

        if (!cur_node->Child[CharToInt[readd[i]]]) //if current node hasn't child se create new node
        {
            cur_node->Child[CharToInt[readd[i]]] = CreateTrieNode();

        }
        cur_node = cur_node->Child[CharToInt[readd[i]]];    //go to new node


    }
    cur_node->x=Id;
    Id++;

}


Node *QueryTrieRead(char *readd, int len) // Find Read r with length n in the trie (search in the trie)
{
    int i;
    Node *cur_node = root;              //start form the root in search operation
    for (i = 0; i < len; i++)           //looping on the length of the trie
    {
        if (!cur_node->Child[CharToInt[readd[i]]]) return NULL;
        cur_node = cur_node->Child[CharToInt[readd[i]]];
    }
    return cur_node;
}

/////////////////////////////////////////////////////////////////////////////////////////////


void Compute()  //Insert all patterns in the trie
{
    InitializeTables();
    InitializeTrie();
    InsertTrieRead("AGA", 3);
    InsertTrieRead("AA", 2);
    InsertTrieRead("AAG", 3);
    InsertTrieRead("GAAG", 4);
    InsertTrieRead("TCG", 3);
}

void FaiulerLink(int cap, char *x, Node *node) //Get the failureLink node for a specific node
{
    for (int i = 1; i < cap; i++)
    {
        char *arrayy = new char[2000];
        int n = 0;
        for (int j = i; j < cap; j++)
        {
            arrayy[n] = x[j];
            n++;
        }
        arrayy[n] = 0;
        if (QueryTrieRead(arrayy, strlen(arrayy)) != NULL)
        {
            node->FailureLink = QueryTrieRead(arrayy, strlen(arrayy));
            break;
        }
    }
    node->FailureLink = root;
    return;
}

char *stringg;
int sizze = 0;

void BuildFailureLink(Node *node) // visit all nodes in the tree
{
    FaiulerLink(sizze, stringg, node);
    for (int i = 0; i < 4; i++)
    {
        if (node->Child[i] == NULL)
        {
            continue;
        }
        else
        {
            stringg[sizze] = CharToInt[i];
            sizze++;
            BuildFailureLink(node->Child[i]);
            sizze--;
        }
    }
}
void computeArray(char *str, int M)
{
    int i = 0;
    Node *node = root;
    while (i < M)
    {

        Node *j = node;
        while (j != root)
        {
            if(j->x != -1)
            {
                cout <<"the pattern idx id = ";
                cout << j->x <<endl;
                cout <<"the current ind = " << i <<endl;
            }
            j = j->FailureLink;
        }
        if (node->Child[CharToInt[str[i]]] != NULL)
        {
            node = node->Child[CharToInt[str[i]]];
            i++;

        }
        else
        {
            node = node->FailureLink;
        }
    }
}

int main()
{
    Compute();
    BuildFailureLink(root);
    computeArray("GAACAAGTGAAGTGAGAAGAAGT", 23);
    return 0;
}

