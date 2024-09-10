# include "head.h"

//task1
int makelist(Node** head, FILE* in)
{
    int n, i, j; // n-numar de echipe
    if (in == NULL)
    {
        printf("Can't open the file.");
        return -1;
    }
    fscanf(in, "%d", &n); //fgetc(in);
    for (i = 0; i < n; i++)
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode != NULL)
        {
            fscanf(in, "%d", &(newNode->val.nPlayers));
            fgetc(in); // trece peste spatiu
            newNode->val.teamName = (char*)malloc(50 * sizeof(char));
            fgets(newNode->val.teamName, 70, in);
            newNode->val.teamName[strcspn(newNode->val.teamName, "\n")] = '\0'; // sterge linia noua
            newNode->val.p = (Player*)malloc(sizeof(Player) * newNode->val.nPlayers);
            for (j = 0; j < newNode->val.nPlayers; j++)
            {
                newNode->val.p[j].firstName = (char*)malloc(50 * sizeof(char));
                newNode->val.p[j].secondName = (char*)malloc(50 * sizeof(char));
                fscanf(in, "%s", newNode->val.p[j].firstName);
                fscanf(in, "%s", newNode->val.p[j].secondName);
                fscanf(in, "%d", &(newNode->val.p[j].points));
            }
            newNode->next = *head; // Adauga nodul la inceputul listei
            *head = newNode; // Actualizeaza head cu noul nod
        }
    }
    return n;
}

//task2
float calculatePoints(Node*head)
{
    int points=0;
    float totalPoints=0.00;
    if (head!=NULL)
    {
        for (int j=0; j<head->val.nPlayers; j++)
        {
            points=points+head->val.p[j].points;
        }
        totalPoints=(float)points/head->val.nPlayers;
    }
    return totalPoints;
}

Node* teamElimination(Node* head, int n, int *newn)
{
    int nelim = 0; // nelim -numar echipe ramase
    int p=1;
    float totalPoints, minim; // totalPoints - pt fiecare echipa
    char tName[30]; // tName - numele echipei cu puncte minime
    Node* copyHead;

    while ((p*2)<n)
    {
        p=p*2;
    }
    for (int k=0; k<n-p; k++)
    {
        copyHead = head;
        minim = 999999.9999;
        while(copyHead!=NULL)
        {
            totalPoints=calculatePoints(copyHead);
            if(totalPoints<minim)
            {
                minim=totalPoints;
                strcpy(tName, copyHead->val.teamName);
            }
            copyHead=copyHead->next;
        }
        head=delete(head, tName);
        nelim++;
    }
    *newn=n-nelim;
    return head;
}

//task3
Stack* stacks(Queue* q, Stack* sWin, Stack* sLose,  FILE* out, int i)
{
    float pointst1,pointst2;
    writeQueueToFile(q,i,out);
    while(q->front!=NULL)
    {
        pointst1=calculatePoints(q->front);
        pointst2=calculatePoints(q->front->next);
        if(pointst1 > pointst2)
        {
            for(int j = 0; j < q->front->val.nPlayers; j++)
            {
                q->front->val.p[j].points++;
            }
            push(&sWin,q->front,calculatePoints(q->front));
            push(&sLose,q->front->next,calculatePoints(q->front->next));
        }
        else
        {
            for(int j = 0; j < q->front->next->val.nPlayers; j++)
            {
                q->front->next->val.p[j].points++;
            }
            push(&sLose,q->front,calculatePoints(q->front));
            push(&sWin,q->front->next,calculatePoints(q->front->next));
        }
        q->front=q->front->next;
        q->front=q->front->next;
    }
    display_stack(sWin, i, out);
    return sWin;
}

List* task3(Queue* q, FILE* out, char winner[])
{
    int nr, i=1;
    List* newlist=NULL;
    Stack *sWin,*sLose;
    sWin=initializeStack();
    sLose=initializeStack();
    sWin=stacks(q,sWin,sLose,out,i);
    nr=countElements(sWin);
    while(nr>=1)
    {
        i++;
        if(nr==1)
        {
            strcpy(winner,sWin->data->val.teamName);
            break;
        }
        if(nr==8)
        {
            newlist=copyStackToLinkedList(sWin);
        }
        emptyQueue(q);
        copyinqfroms(q,sWin);
        emptyStack(&sWin);
        emptyStack(&sLose);
        sWin=stacks(q,sWin,sLose,out,i);

        nr=countElements(sWin);
    }
    return newlist;
}

//task4
Tree* insertNode(Tree* root, char* teamName, float point)
{
    if (root == NULL)
    {
        return createNodeTree(teamName, point);
    }

    if (point>root->point)
    {
        root->left=insertNode(root->left, teamName, point);
    }
    else if (point<root->point)
    {
        root->right=insertNode(root->right, teamName, point);
    }
    else
    {
        if (strcmp(teamName, root->teamName) < 0)
        {
            root->right=insertNode(root->right, teamName, point);
        }
        else
        {
            root->left=insertNode(root->left, teamName, point);
        }
    }
    return root;
}

//task5
void sortList(List** headRef)
{
    if (*headRef == NULL || (*headRef)->next == NULL)
        return;

    int swapped;
    List** ptr1;
    List* lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = headRef;

        while ((*ptr1)->next != lptr)
        {
            List* current = *ptr1;
            List* next = current->next;

            if (current->point < next->point || (current->point == next->point && strcmp(current->teamName, next->teamName) < 0))
            {
                current->next = next->next;
                next->next = current;
                *ptr1 = next;
                swapped = 1;
            }

            ptr1 = &(*ptr1)->next;
        }

        lptr = *ptr1;
    }
    while (swapped);
}

NodeAVL* copyListToAVL(List* head)
{
    NodeAVL* root = NULL;
    List* current = head;

    while (current != NULL)
    {
        root = insertNodeAVL(root, current);
        current = current->next;
    }
    return root;
}

int main(int argc, char *argv[])
{

    Node* head = NULL;
    int nTeams;
    int nT; //nT- number of teams after teamElimination function
    FILE* in = fopen(argv[2], "r");
    //FILE* in= fopen("d.in","r");
    FILE* out;
    FILE* file= fopen(argv[1],"r");
    //FILE* file= fopen("c.in","r");
    int objectives[5];
    Queue *q;
    Tree* root=NULL;
    NodeAVL* avl=NULL;
    List* newlist;
    char winner[50];
    int i;
    for (i=0; i<5; i++)
    {
        fscanf(file, "%d", &objectives[i]);
    }
    fclose(file);

    if(objectives[0]==1)
    {
        //task1
        out= fopen(argv[3],"w");
        //out= fopen("r.out","w");
        nTeams=makelist(&head, in);
        writeResults(out,head);
        fclose(out);
    }
    if(objectives[1]==1)
    {
        //task2
        out= fopen(argv[3],"w");
        //out= fopen("r.out","a");
        head=teamElimination(head, nTeams, &nT);
        writeResults(out,head);
        fclose(out);
    }
    if(objectives[2]==1)
    {
        //task3
        out= fopen(argv[3],"a");
        //out= fopen("r.out","a");
        q=createQueue();
        enqueue(q, head);
        newlist=task3(q,out,winner);
        fclose(out);
    }
    if(objectives[3]==1)
    {
        //task4
        out= fopen(argv[3],"a");
        //out= fopen("r.out","a");
        List* copynewlist=newlist;
        while(copynewlist!=NULL)
        {
            root=insertNode(root, copynewlist->teamName, copynewlist->point);
            copynewlist=copynewlist->next;
        }
        fprintf(out,"\nTOP 8 TEAMS:\n");
        printTreeToFile(root,out);
        //printList(newlist);
        fclose(out);
    }
    if(objectives[4]==1)
    {
        //task5
        out= fopen(argv[3],"a");
        //out= fopen("r.out","a");
        sortList(&newlist);
        avl=copyListToAVL(newlist);
        printSecondLevelAVL(avl);
        fclose(out);
    }
    fclose(in);
    //freememory
    freeList(newlist);
    freeNode(head);
    freeAVL(avl);
    freeTree(root);
    freeQueue(q);
    return 0;
}

