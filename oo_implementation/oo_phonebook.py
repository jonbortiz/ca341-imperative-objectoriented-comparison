#!/usr/bin/env python3

class Node:
    def __init__(self, name, address, number):
        self.data = number
        self.name = name
        self.address = address
        self.left = None
        self.right = None 

def insert(root, name, address, key):
    if root is None:
        return Node(name, address, key)
    else: 
        if root.data == key:
            return root
        elif root.data < key:
            root.right = insert(root.right, name, address, key)
        else:
            root.left = insert(root.left, name, address, key)
    return root

def in_order(root):
    if root: 
        in_order(root.left)
        print(root.data, root.name)
        in_order(root.right)

def search_number(root, key):
    if root is None or root.data == key: 
        return root.name, root.address
    
    if root.data < key:
        return search_number(root.right, key)
    return search_number(root.left, key)

def read_file():
    contacts = {}
    with open('details.txt') as f:
        for line in f:
            line = line.strip()
            name, address, number = line.strip().split(" ")
            contacts[name] = address, int(number)
    f.close()
    return contacts

def main():
    root = Node("Abby", "Cork", 856734560)
    phonebook = read_file()
    file = open("details.txt", "a")

    in_order(root)

    for name, value in phonebook.items():
        address, number = value[0], value[1]
        insert(root, name, address, number)

    # in_order(root)

    print("\nWelcome to the phonebook command line you can enter search, new, or delete")
    print("____________________________________________________________________________\n")

    while True:
        command = input(">> ")
        if(command == 'exit'):
            break
    
        if(command == "search"):
            number = int(input("Search number: "))
            result = search_number(root, number)
            print("Name: {} \nAddress: {}".format(result[0], result[1]))
        
        elif(command == "new"):
            name = input("Enter Name: ")
            address = input("Enter Address: ")
            number = int(input("Enter Number: "))
            insert(root, name, address, number)
            phonebook[name] = (address, number)
            file.write("\n{}, {}, {}".format(name, address, number))
            file.close()
            print("Contact added to phonebook!")

if __name__ == "__main__":
    main()