# data-structures-c: *LAN PARTY PROJECT*
Description and tasks (romanian language): https://ocw.cs.pub.ro/courses/sda-ab/tema1

## Objectives
Understanding the concept of operation and implementation of data structures.


## Description
The Faculty of Automatic Control and Computer Science, through LSAC, organizes a LAN Party each semester where all students who want to test their skills in a certain game participate. A software solution (executable program) that can automate this process is desired.<br>
**A list** with information from the d.in file will be created (the list will be formed by adding elements at the beginning - O(1)).<br>
From the previously created list, teams with the lowest team score will be removed (information about the calculation of this score is found in the Technical Details section) so that n teams remain in the list (where n is maximum and n is a power of 2). If several teams have the same score, the first team found in the list will be removed. After each elimination, the list will be traversed from the beginning.<br>
The necessary data structures will be implemented to conduct the matches:<br>
- **A queue** will be created in which the matches between teams will be placed.
Teams will form matches in the order they are in the list from the previous point, the first two teams will form the first match (and so on).
- **Two stacks** will be created - one for the losers and one for the winners - which will contain the teams that lost, respectively, won the previous match.
Teams will be added to the stack based on the result obtained, and a point will be added to the team score of the teams that won.
In the case of a match where both teams have the same score, the first team added in the contested match will be chosen.
Teams found in the losers' stack will be deleted. (at the end of each stage; e.g., from a round with 8 teams, deletion is done after all teams have been eliminated. In this case, after 4 of the teams have been eliminated, they will be deleted. In the next round, for example, 2 teams will be added to the losers' stack, after which it will be cleared again - the losers' stack -.)
From the winners' stack, teams will be extracted and the queue of matches will be refilled, forming matches with consecutive teams (the first team taken out of the stack will play with the second team taken out of the stack the first match).
The listed steps will be repeated until the teams for the first 8 places are found, which will be saved in another list, after finding them the matches will continue until the winning team is found.
- A ranking of the last 8 teams (saved in the previous sub-item) will be created in the form of **a BST (Binary Search Tree)**. It will be ordered by team score and its content will be displayed in descending order (in case two teams have the same score, they will be ordered by name, descending).
- **An AVL tree** will be created with the last 8 teams (saved in sub-item 3, but sorted as in sub-item 4) and the teams on the second level of the tree will be displayed.



## Implementation
### task1
1. Use the *makelist* function: n stores the number of teams, and then each piece of information from the file is taken in the form of the data structure for Node. With each participant's data retrieval, iterate through the for structure, use the fscanf and fgets functions, as well as the strcspn function to skip the blank line in the data file. Adding is always done at the front, by creating an additional node in which the information is initially placed and making the link between it and the head of the list. As a result, the function transmits the pointer to the first element of the list.
2. The *writeResults* function is used to write the created list in the result file and is called in main. It receives as arguments the file and the root of the list, and iterates through the list using a while loop, and with the fprintf function displays the results in the file.

### task2
1. The *teamElimination* function receives the number of teams, n, the pointer to the root of the list, and another pointer, newn, in which the number of teams remaining after elimination will be stored. It calculates the highest power of 2, stores it in var p, then iterates through the list and removes a team with the delete function until n-p teams remain. To eliminate them, it checks the elimination condition, i.e., calculates the minimum score in the list.
2. The mentioned delete function receives a pointer to the head of the list and the name of the team with the lowest score, stored in v. It goes through the list checking if the team name is the same, and if affirmative, eliminates that node from the list by breaking the links between it and the previous one and remaking it with the next one.
3. The *calculatePoints* function receives the list and returns the total number of points, calculated by summing the points of each team member and dividing the sum by the number of members.
4. The results are written by displaying the modified list with the *writeResults* function, described in task1.

### task3
1. The *createQueue* function initializes the queue and allocates space.
2. The *enqueue* function receives pointers to the queue and list, goes through the list and copies each element of it into a new, allocated node, then adds it to the queue following the cases where the queue is initially empty or already has elements. It uses a while loop to take each node of the list in turn, the list remaining unchanged.
3. The *stacks* function realizes the matches between teams, it receives the winners and losers stacks and the queue. At each call of the function, it displays the queue in the file, i.e., the round and which teams are in it, with the *writeQueueToFile* function. Then as long as the queue has teams, it calculates the scores for 2 nodes/teams from the queue and compares them, putting in the winners' stacks the teams with the higher score and vice versa with the help of the push function. At the end, it displays the winners' stack (which represents the winners of the round). This function only realizes one round.
4. The *task3* function receives the queue, and a vector named winner that will contain the name of the winning team. It creates 2 stacks sWin and sLose which it initializes using the *initializeStack()* function, as well as a newlist which it initializes with NULL, whose structure contains the team name and total score. Further, with the help of the *countElements* function, it counts how many elements the winners' stack has, and as long as it has more than one element or one. it enters the loop, where: if it has one element, it stores it in winner and exits with a break, if it has 8 elements it stores them in the new list using the copyStackToLinkedList function, and in other situations, it empties the queue, copies the elements of the winners' stack into the queue, with the copyingfroms function, empties both stacks with the *emptyStack* function, and calls the stacks function again, but also updates nr, the number of elements from the winners' stack. Thus, through the repeated call of the *stacks* function, it moves to the next match and so on. In the end, the function returns newlist, which is the list with the first 8 teams.
5. The previously mentioned functions: *countElements* receives the stack and goes through it counting the number of traversals which it then returns; push receives the stack with a double pointer to keep the changes, copies the node from the queue into a new node which it then puts in the stack;

### task4
1. The *insertNode* function receives a pointer to the BST tree, the name of a team, and its score. If the tree is initially NULL, it calls the *createNodeTree* function to add the first node in the tree and subsequently adds the others using recursive calls and respecting the ordering requirements for the tree: in descending order of scores, and in case of equal scores, in descending order of team names. In the end, it returns a pointer to the root of the tree.
2. After creating the tree, it is displayed using the *printTreeToFile* function.

### task5
1. Sorting the list after the specified criteria with the *sortList* function:
Checks if the list is empty or contains only one node. In this case, no sorting is needed, so the function ends. A do-while loop is used to iterate through the list and check if another sorting pass is necessary. The swapped variable is used to mark if any exchange was made in an iteration. If there are no exchanges, it means the list is already sorted and the loop can end. A double pointer ptr1 is used to iterate through the list. It is initialized with the start address of the list (headRef). Inside the loop, the current node and the next node in the list are compared. First, the scores are checked, and then, if they are equal, the team names are compared using the strcmp function. If the nodes need to be swapped in order, the swap is made by adjusting the next links and *ptr1 is updated with the address of the new node to maintain the coherence of the list. At the end of the iteration, lptr is updated with the address of the current node, indicating that the last sorted element is to its right. The process repeats until there are no exchanges in an iteration, meaning the list is completely sorted.
2. Inserts each node of the list into the AVL tree using the *createAVLFromList* and *insertNodeAVL* functions, respecting the balance conditions, which are achieved through the RightRotation, LRRotation, LeftRotation, RLRotation functions.
3. Displays the second level of the tree with the help of two functions: *printSecondLevelAVL* and *printLevel*. The function checks if the root node is null, in which case there is nothing to display and the function ends. If the level (level) is 0, then we are at the desired level and we can display the team name in the output file using the fprintf function. If the level is greater than 0, the function is called recursively to display the next level for both the left subtree and the right subtree, with the level decremented by 1. The *printSecondLevelAVL* function receives an AVL node and is responsible for opening the output file, checking if the opening was successful. If the file opening was not successful, an error message is displayed and the function ends.
