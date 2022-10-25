#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void searchName(struct node* root, char *value)
{
    if (root != NULL)
    {
        searchName(root->leftChild, value);
        if (strcmp(root->contactName, value) == 0)
        {
            printf("Found Contact:\nName: %s\nAddress: %s\nPhone Number: %s\n",
            root->contactName, root->contactAddress, root->phoneNumber);
        }
        searchName(root->rightChild, value);
    }
}

void searchNumber(struct node* root, int value)
{
    if (root != NULL)
    {
        if (atoi(root->phoneNumber) == value)
        {
            printf("Found Contact:\nName: %s\nAddress: %s\nPhone Number: %s\n",
            root->contactName, root->contactAddress, root->phoneNumber);
        } 
        else if (value < atoi(root->phoneNumber))
        {
            searchNumber(root->leftChild, value);
        } 
        else
        {
            searchNumber(root->rightChild, value);
        }
    }
}

int main(void)
{

    char fileName[100], c;
    char name[20];
    char address[20];
    char phoneNumber[20];
    char command[10];
    int line = 0;
    FILE *fptr;
    int itemFlag = 0;
    int firstNodeFlag = 0;
    int i = 0;
    struct node* root = NULL;

    printf("\n\n Read Phonebook Data & Store using a Binary Search Tree :\n");
    printf("-------------------------------------------------\n");
    printf("Would you like to import tree data?\nAnswer: 'yes' or 'no'\n");
    scanf("%s", fileName);
    if (strcmp(fileName, "yes")==0)
    {
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
    }
    
    while(strcmp(command, "quit") != 0)
    {   
        printf("\nEnter command: \n");
        scanf("%s", command);

        if (strcmp(command, "inorder") == 0)
        {
            inorder(root);
        } 
        else if (strcmp(command, "delete") == 0)
        {
            char deleteNumber[20];
            printf("What number would you like to delete?: ");
            scanf("%s", deleteNumber);
            delete(root, atoi(deleteNumber));
        }
        else if (strcmp(command, "search") == 0)
        {
            char searchValue[20];
            printf("What number/name would you like to search?: ");
            scanf("%s", searchValue);
            if (atoi(searchValue) == 0)
            {
                searchName(root, searchValue);
            } else {
                searchNumber(root, atoi(searchValue));
            }
        }
        else if (strcmp(command, "add") == 0)
        {
            printf("\nInserting New Contact\n");
            printf("Name: ");
            scanf("%s", name);
            printf("Address: ");
            scanf("%s", address);
            printf("Phone Number: ");
            scanf("%s", phoneNumber);
            insert(root, phoneNumber, name, address);
            memset(name, 0, sizeof(name));
            memset(address, 0, sizeof(address));
            memset(phoneNumber, 0, sizeof(phoneNumber));
        }
    }

    return 0;
};
