#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int nodeData;
    struct node *leftChild, *rightChild;
};

struct node* newTree(int data)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->nodeData = data;
    temp->leftChild = temp->rightChild = NULL;
    return temp;
}

void inorder(struct node* root)
{
    if (root != NULL)
    {
        inorder(root->leftChild);
        printf("%d\n", root->nodeData);
        inorder(root->rightChild);
    }
}

struct node* insert(struct node* node, int data)
{
    if (node == NULL)
    {
        return newTree(data);
    }

    if (data < node->nodeData)
    {
        node->leftChild = insert(node->leftChild, data);
    } else if (data > node->nodeData)
    {
        node->rightChild = insert(node->rightChild, data);
    }
}

int main()
{
    char line[50];
    char fileName[20];
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
    else
    {
        
    }


    return 0;
};
