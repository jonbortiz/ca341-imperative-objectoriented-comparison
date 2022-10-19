#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 50
#define MAX_LENGTH 50

struct node {
    int phoneNumber;
    struct node *leftChild, *rightChild;
};
 
struct node* newNode(int newNumber)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->phoneNumber = newNumber;
    temp->leftChild = temp->rightChild = NULL;
    return temp;
}
 
void inorder(struct node* root)
{
    if (root != NULL) 
    {
        inorder(root->leftChild);
        printf("%d \n", root->phoneNumber);
        inorder(root->rightChild);
    }
}
 

struct node* insert(struct node* node, int newNumber)
{
    if (node == NULL)
    {
        return newNode(newNumber);
    }

    if (newNumber < node->phoneNumber)
    {
        node->leftChild = insert(node->leftChild, newNumber);
    }
    else if (newNumber > node->phoneNumber)
    {
        node->rightChild = insert(node->rightChild, newNumber);
    }

    return node;
}

int main(void)
{
    char contents[MAX_LINES][MAX_LENGTH];
    char fileName[20];
    int line = 0;
    FILE *fptr;

    printf("\n\n Read Phonebook Data & Store using a Binary Search Tree :\n");
    printf("-------------------------------------------------\n");
    printf(" Input the filename to be opened: ");
    scanf("%s", fileName);

    fptr = fopen(fileName, "r");

    if (fptr == NULL)
    {
        printf("file cannot be opened, make sure file is in the same directory as program \n");
        exit(0);
    }

    while (!feof(fptr) && !ferror(fptr))
    {
        if (fgets(contents[line], MAX_LENGTH, fptr) != NULL)
        {
            line++;
        }
    }
    

    struct node* root = NULL;
    root = insert(root, atoi(contents[0]));

    for (int i = 1; i < line; i++)
    {
        insert(root, atoi(contents[i]));
    }

    inorder(root);

    return 0;
};
