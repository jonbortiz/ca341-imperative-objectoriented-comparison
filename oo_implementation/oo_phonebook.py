#!/usr/bin/env python3

# Program is not fully complete: 

class Node:                                         # Create node class so we can assign our name, address and number to the class to add to tree
    def __init__(self, name, address, number):
        self.data = number
        self.name = name
        self.address = address
        self.left = None                            # assigning left and right node to none so we can insert to tree later
        self.right = None 

def insert(root, name, address, number):               # function to insert node to binary tree sorted by phone number
    if root is None:                            
        return Node(name, address, number)             # if root is empty will assign node to binary tree
    else: 
        if root.data == number:
            return root
        elif root.data < number:                       # checks if node inserted can go in the left or right leaf depending on how number is sorted
            root.right = insert(root.right, name, address, number)      # using recursion to call again with certain direction
        else:
            root.left = insert(root.left, name, address, number)
    return root

def search_number(root, number):                                       # function to search for contact on binary tree
    if root is None or root.data == number: 
        return root.name, root.address                                 # returns the name and address linked with phone number given in function 
    
    if root.data < number:                                             # if not found yet, function is called again to look at left or right node depending on how it is sorted
        return search_number(root.right, number)
    return search_number(root.left, number)

def read_file():                                                        # using function to read our file which has all of our contacts from phonebook stored
    contacts = {}
    with open('details.txt') as f:
        for line in f:
            line = line.strip()
            name, address, number = line.strip().split(" ")
            contacts[name] = address, int(number)                       # dictionary returned so we can enter the name, address and number to binary tree so they would be all linked together
    f.close()
    return contacts

def main():
    root = Node("Abby", "Cork", 856734560)                              # assigning root node to our tree 
    phonebook = read_file()
    file = open("details.txt", "a")

    for name, value in phonebook.items():                               # iterating through phonebook dictionary so we can sort the numbers into the binary tree
        address, number = value[0], value[1]
        insert(root, name, address, number)

    print("\nWelcome to the phonebook command line")
    
    print("Commands in use: search, new, delete, quit")
    print("____________________________________________________________________________\n")

    while True:                                                         # command line is running while statement is true, will only exit program once user types "exit"
        command = input(">> ")
        if(command == 'quit'):                                          # exits program if user writes "quit"
            break
    
        if(command == "search"):                                        # searches contact name and address matching phone number
            number = int(input("Search number: "))
            try:  
                result = search_number(root, number)
                print("Name: {} \nAddress: {}".format(result[0], result[1]))
            except AttributeError:
                print("{} not found in phonebook".format(number))
        
        elif(command == "new"):
            name = input("Enter Name: ")
            address = input("Enter County: ")
            number = int(input("Enter Number: "))
            insert(root, name, address, number)
            phonebook[name] = (address, number)
            file.write("\n{}, {}, {}".format(name, address, number))
            file.close()
            print("Contact added to phonebook!")

if __name__ == "__main__":
    main()