#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player
{
    char* firstName;
    char* secondName;
    int points;
} Player;

typedef struct Team
{
    int nPlayers;
    char* teamName;
    Player* p;
} Team;

typedef struct Node
{
    Team val;
    struct Node* next;
} Node;

typedef struct Q
{
    Node* front, *rear;
} Queue;

typedef struct S
{
    Node* data;
    float point;
    struct S* next;
} Stack;

typedef struct L
{
    char* teamName;
    float point;
    struct L* next;
} List;

typedef struct T
{
    char* teamName;
    float point;
    struct T* left;
    struct T* right;
} Tree;

typedef struct AVL
{
    int height;
    List* val;
    struct AVL* left, *right;
} NodeAVL;

//lists
Node* delete(Node *head, char v[]);
List* copyStackToLinkedList(Stack* stack);
List* copyNodeFromStackToList(Stack* stackNode, List* listNode);

//stacks
Stack* initializeStack();
void emptyStack(Stack** stack);
void push(Stack** s,Node* node, float points);
int countElements(Stack* stack);

//queues
Queue *createQueue();
void enqueue(Queue* q, Node* head);
int isEmpty (Queue *q);
void emptyQueue(Queue* queue);
void copyinqfroms(Queue* q, Stack* stack);

//BTS
Tree* createNodeTree(char* teamName, float point);

//AVL
int getBalance(NodeAVL* root);
int nodeHeight(NodeAVL* root);
NodeAVL* RightRotation(NodeAVL* z);
NodeAVL* LeftRotation(NodeAVL* z);
NodeAVL* LRRotation (NodeAVL* z);
NodeAVL* RLRotation (NodeAVL* z);
int getHeight(NodeAVL* root);
NodeAVL* createNodeAVL(List* val);
NodeAVL* insertNodeAVL(NodeAVL* root, List* val);

//write results to file
void writeResults (FILE* out, Node* head);
void writeQueueToFile(Queue* q, int i, FILE* fp);
void display_stack(Stack* s, int i, FILE* fp);
void printTreeToFileRecursive(Tree* root, FILE* file);
void printTreeToFile(Tree* root, FILE* out);
void printLevelAVL(NodeAVL* root, int level, FILE* outFile);
void printSecondLevelAVL(NodeAVL* root);

//free memory
void freePlayer(Player* player);
void freeTeam(Team* team) ;
void freeNode(Node* node);
void freeQueue(Queue* queue);
void freeStack(Stack* stack);
void freeList(List* list);
void freeTree(Tree* root);
void freeAVL(NodeAVL* root);

//print results
void printQueue(Queue* q);
void displayStack(Stack* stack);
void display(Node* head);
void printLevel(NodeAVL* root, FILE* file);
int max(int a, int b);
void printList(List* node);
