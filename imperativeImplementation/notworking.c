#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024
#define MAX_ARGS 64
#define SEPARATORS " \t\n"


struct node {
    char contactName[20];
    char contactAddress[20];
    char phoneNumber[20];
    struct node *leftChild, *rightChild;
};
 
struct node* newNode(char *newNumber, char *newName, char *newAddress)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    strncpy(temp->phoneNumber, newNumber, 20);
    strncpy(temp->contactAddress, newAddress, 20);
    strncpy(temp->contactName, newName, 20);
    temp->leftChild = temp->rightChild = NULL;
    return temp;
} 

struct node* insert(struct node* node, char *newNumber, char *newName, char *newAddress)
{
    if (node == NULL)
    {
        return newNode(newNumber, newName, newAddress);
    }

    if (atoi(newNumber) < atoi(node->phoneNumber))
    {
        node->leftChild = insert(node->leftChild, newNumber, newName, newAddress);
    }
    else if (atoi(newNumber) > atoi(node->phoneNumber))
    {
        node->rightChild = insert(node->rightChild, newNumber, newName, newAddress);
    }

    return node;
}

struct node* minValue(struct node* node)
{
    struct node* currentNode = node;

    while (currentNode && (currentNode->leftChild != NULL))
    {
        currentNode = currentNode->leftChild;
    }

    return currentNode;
}

struct node* delete(struct node* root, int deleteNumber)
{
    if (root == NULL)
    {
        return root;
    }

    int rootNumber = atoi(root->phoneNumber);

    if (deleteNumber < rootNumber)
    {
        root->leftChild = delete(root->leftChild, deleteNumber);
    } else if (deleteNumber > rootNumber)
    {
        root->rightChild = delete(root->rightChild, deleteNumber);
    } else
    {
        struct node* tempNode;
        if (root->leftChild == NULL)
        {
            tempNode = root->rightChild;
            free(root);
            return tempNode;
        } else if (root->rightChild == NULL)
        {
            tempNode = root->leftChild;
            free(root);
            return tempNode;
        }

        tempNode = minValue(root->rightChild);
        strncpy(tempNode->phoneNumber, root->phoneNumber, 20);

        root->rightChild = delete(root->rightChild, atoi(tempNode->phoneNumber));
    }

    return root;
}

void inorder(struct node* root)
{
    if (root != NULL) 
    {
        inorder(root->leftChild);
        printf("number:%s name:%s address:%s \n", root->phoneNumber, root->contactName, root->contactAddress);
        inorder(root->rightChild);
    }
}

struct node* treeFromFile(struct node* root, char *name, char* address, char *phoneNumber)
{
    char fileName[100], c;
    FILE *fptr;
    int itemFlag = 0;
    int firstNodeFlag = 0;
    int i = 0;

    printf(" Input the filename to be opened: ");
    scanf("%s", fileName);

    fptr = fopen(fileName, "r");

    if (fptr == NULL)
    {
        printf("file cannot be opened, make sure file is in the same directory as program \n");
        exit(0);
    }

    c = fgetc(fptr);
    while (c != EOF)
    {
        if (c == '\n')
        {
            itemFlag = 0;
            i = 0;
            if (firstNodeFlag == 0)
                {
                    firstNodeFlag = 1;
                    root = insert(root, phoneNumber, name, address);
                }

            insert(root, phoneNumber, name, address);
            memset(name, 0, sizeof(name));
            memset(address, 0, sizeof(address));
            memset(phoneNumber, 0, sizeof(phoneNumber));
            c = fgetc(fptr);
        }

        if (c == ' ')
        {
            itemFlag++;
            i = 0;
            c = fgetc(fptr);
        }

        if (itemFlag == 0)
        {
            name[i] = c;
        } else if (itemFlag == 1)
        {
            address[i] = c;
        } else if (itemFlag == 2)
        {
            phoneNumber[i] = c;
        }

        i++;
        c = fgetc(fptr);
    }

    fclose(fptr);
    return root;
}

void tokeniseInput(char ** args, char ** arg, char buff[])
{
    arg = args;
    *arg++ = strtok(buff, SEPARATORS);
    while ((*arg++ = strtok(NULL, SEPARATORS)));
}

int command(char ** args)
{
    char name[20];
    char deleteNumber[20];
    char address[20];
    char phoneNumber[20];
    struct node* root = NULL;

    if (!strcmp(args[0], "readfile"))
    {
        treeFromFile(root, name, address, phoneNumber);
        return(1);
    } 
    else if (!strcmp(args[0], "quit"))
    {
        return(0);
    }
    else if (!strcmp(args[0], "inorder"))
    {
        inorder(root);
        return(1);
    }
    else if (!strcmp(args[0], "delete"))
    {
        printf("What number would you like to delete?\n");
        scanf("%s", deleteNumber);
        delete(root, atoi(deleteNumber));
        return(1);
    }
}

int main(int argc, char ** argv)
{
    char buff[MAX_BUFFER];
    char * args[MAX_ARGS];
    char ** arg;
    char * prompt = "==> ";

    char name[20];
    char deleteNumber[20];
    char address[20];
    char phoneNumber[20];
    struct node* root = NULL;
    int exitCondition = 1;
    

    printf("\n\n Read Phonebook Data & Store using a Binary Search Tree :\n");
    printf("---Commands---\n");
    printf("quit : exit the program\nreadfile : read tree data from file\ninorder : print tree inorder\ndelete : delete node from tree\n");
    printf("-------------------------------------------------\n");
    
    while(!feof(stdin))
    {
        fputs (prompt, stdout);

        if (fgets(buff, MAX_BUFFER, stdin))
        {
            tokeniseInput(args, arg, buff);

            if (args[0])
            {
                if(exitCondition == 0)
                {
                    break;
                } else
                {
                    continue;
                }

                arg = args;
                while (*arg)
                {
                    fprintf(stdout, "%s ", *arg++);
                    fputs("\n", stdout);
                }
            }
        }
    }

    // inorder(root);
    // delete(root, 864862149);
    // printf("\n");
    // inorder(root);

    return 0;
};
