//Erhan Yalniz   -   150117905
#include <stdio.h>
#include <stdlib.h> // Will be used for allocating and reallocating space.

// This will hold the sequence that was read from user.
int *seq;
// This will hold the count of numbers that was entered.
int length;

// This will be our structure for nodes in binary search tree.
typedef struct node {
    int key; // Value of node.
    struct node *left, *right; // Left and right binary search subtrees.
}node;

// Binary search tree's start point will be this pointer.
node *treeHead;

// This will hold depth of binary search tree.
long long depth;

// This will hold how many different sequences yield the same BST topology.
long long numberOfSameTrees;

// This function will read sequence of integers from user to pointer "seq".
void getSequence();

// This function will print sequence that was read to pointer "seq".
void printSequence();

// This function will build the binary search tree from sequence of integers ("seq").
void buildTree();

// Just a basic function that will get depth of binary search tree. Parameter will be head of binary search tree.
long long getDepth(node *current);

// Just a basic function that will 2 to the power of n.
long long pow2(long long n);

// This function will print content of binary search tree by taking head of tree as a parameter and taking how it will print with a number.
void printTree(node *current, long long n);

// This function calculates how many different sequences yield the same BST topology.
long long findSameTrees(node *current);

// This function will calculate how many different sequences yield the same BST topology and show them.
void printSameTrees();

int main(){
    // Read sequence from user.
    getSequence();
    // Show entered sequence.
    printSequence();
    // Build binary search tree from given sequence.
    buildTree();
    // Get depth of BST and store it in "depth".
    depth = getDepth(treeHead);
    printf("Current tree: { ");
    // Show tree.
    printTree(treeHead, pow2(depth)-1);
    printf("}\n");
    //   Find how many different sequences yield the same BST topology.
    printSameTrees();
    return 0;
}

// This function will read sequence of integers from user to pointer "seq".
void getSequence(){
    int buf;
    length = 0;
    // Allocate sequence for the first time.
    seq = (int *) malloc(sizeof(int));
    // Start reading numbers from input.
    // scanf will return 1 unless a number cannot be read to "buf".
    while(scanf("%d", &buf)==1){
        // Increase total count of numbers read.
        length++;
        // Reallocate pointer "seq" to store the new number.
        seq = (int *) realloc(seq, sizeof(int) * length);
        // Store in pointer seq just like an array.
        *(seq + length - 1) = buf;
    }
}

// This function will print sequence that was read to pointer "seq".
void printSequence(){
    int i;
    printf("You entered: { ");
    // Print all elements of sequence "seq".
    for(i = 0;i < length;i++){
        printf("%d ", *(seq + i));
    }
    printf("}\n");
}

// This function will build the binary search tree from sequence of integers ("seq").
void buildTree(){
    int i;
    // Allocate space for head of binary search tree (root).
    treeHead = (node *) malloc(sizeof(node));
    // Store first element of sequence at the root of binary search tree.
    treeHead->key = *seq;
    // Empty left subtree.
    treeHead->left = NULL;
    // Empty right subtree.
    treeHead->right = NULL;
    // Store root of binary search tree.
    node *head = treeHead;
    for(i = 1;i < length;i++){
        // Return "treeHead" to root of binary search tree stored in "head".
        treeHead = head;
        // Traverse while any of the left or right subtree is existing.
        while(treeHead->left != NULL || treeHead->right !=  NULL){
            // If the current member of sequence is less then current node of binary search tree traverse to left subtree.
            if(treeHead->key > *(seq + i)){
                // If left subtree is empty stop traversing.
                if(treeHead->left == NULL){
                    break;
                }
                // Otherwise traverse to left.
                treeHead = treeHead->left;
            }
            // If the curretn member of sequence is greater then current node of binary search tree traverse to right subtree.
            else{
                // If right subtree is empty stop traversing
                if(treeHead->right == NULL){
                    break;
                }
                // Otherwise traverse to right.
                treeHead = treeHead->right;
            }
        }
        // When traversing is over assign current member of sequence to corresponding node.
        // If current member of sequence is less then last traversed node of binary search tree then store it in the left node.
        if(treeHead->key > *(seq + i)){
            // Allocate space for the node.
            treeHead->left = (node *) malloc(sizeof(node));
            // Store current member of sequence.
            treeHead->left->key = *(seq + i);
        }
        // Otherwise store current member of sequence in the right node.
        else{
            // Allocate space for the node.
            treeHead->right = (node *) malloc(sizeof(node));
            // Store current member of sequence.s
            treeHead->right->key = *(seq + i);
        }
    }
    // Return "treeHead" pointer to root of binary search tree.
    treeHead = head;
}

// Just a basic function that will get depth of binary search tree. Parameter will be head of binary search tree.
long long getDepth(node *current){
    // If current element of exist try to find which one of the subtrees of current element is more deep. 
    if(current != NULL){
        // Call "getDepth" recursively to find out depth of left subtree.
        long long left = 1 + getDepth(current->left);
        // Call "getDepth" recursively to find out depth of right subtree.
        long long right = 1 + getDepth(current->right);
        // Select and return the deepest one.
        return (left > right ? left : right);
    }
    // Return 0 if current element is not existing.
    return 0;
}

// Just a basic function that will 2 to the power of n.
long long pow2(long long n){
    long long result = 1;
    // Multiply 2 by itself "n" times.
    for(;n>0;n--){
        result*=2;
    }
    // Return the calculated value.
    return result;
}

// This function will print content of binary search tree by taking head of tree as a parameter and taking how it will print with a number.
void printTree(node *current, long long n){
    // Check if current element exist.
    if(current != NULL){
        // If then print the key of current element.
        printf("%d ", current->key);
        // Check if the least significant bit of number "n".
        if(n & 1){
            // If the least significant bit is 1 then print left subtree first. Shift number "n" to right just one bit so we get how we will print next subtree.
            printTree(current->left, n>>1);
            // Then print right subtree. Shift number "n" to right just one bit so we get how we will print next subtree.
            printTree(current->right, n>>1);
        }else{
            // If least significant bit is 0 then print right subtree first.
            printTree(current->right, n>>1);
            // Then print right subtree. Shift number "n" to right just one bit so we get how we will print next subtree.
            printTree(current->left, n>>1);
        }
    }
}

// This function calculates how many different sequences yield the same BST topology.
long long findSameTrees(node *current){
    // Check if current element exists.
    if(current != NULL){
        // if we are at a leaf or singleton return 1.
        if(current->left == NULL || current->right == NULL){
            return 1;
        }
        return findSameTrees(current->left) + findSameTrees(current->right);
    }
}

// This function will calculate how many different sequences yield the same BST topology and show them.
void printSameTrees(){
    int i;
    // Count each one of singleton (linked from left or right) subtrees, if there is none then count leafs at the and of each branch.
    // You can exchange as blocks (not interchanging) which means we can combine this block in whatever order we like and it will still give the same BST as result.
    // If we get all combinations of these non-singleton trees printed both starting from left then right and right then left, which means 2 to the power of each time that is important to print one side first;
    // that means 2 to the power of non-singleton trees should be the number of same binary search trees that can be build with differently ordered same sequences consisting of same numbers.
    // This is because there is only two options when traversing through binary search tree and printing it:
    // 1- You can either print left subtree first then print right subtree.
    // 2- Or you can either print right subtree first then print left subtree.
    numberOfSameTrees = pow2(findSameTrees(treeHead));
    // Print the total count of different sequences that yield the same BST topology.
    printf("%lld different sequences yield the same BST topology.\n", numberOfSameTrees);
    // Print each one of them by just applying each one of printing combinations on our binary search tree.
    for(i = 0;i < numberOfSameTrees;i++){
        // Print binary search tree in style of "i".
        printTree(treeHead, i);
        // After printing whole sequence go on to next by newline.
        printf("\n");
    }
}
