#!/usr/bin/env python3

class Node:
    def __init__(self, key):
        self.data = key
        self.left = None
        self.right = None 

def insert(root, key):
    if root is None:
        return Node(key)
    else: 
        if root.data == key:
            return root
        elif root.data < key:
            root.right = insert(root.right, key)
        else:
            root.left = insert(root.left, key)
    return root

def in_order(root):
    if root: 
        in_order(root.left)
        print(root.data)
        in_order(root.right)

def search(root, key):
    if root is None:
        return False
    
    if (root.data == key):
        return True
    
    check_left = search(root.left, key)
    if check_left is True:
        return True
    
    check_right = search(root.right, key)
    return check_right

def read_file():
    numbers = []
    with open('details.txt') as f:
        for line in f:
            name, address, number = line.strip().split(",")
            numbers.append(int(number))
    f.close()
    return numbers

def main():
    root = Node(856734560)

    phonebook = read_file() 

    for i in phonebook:
        insert(root, i)
    in_order(root)

    number = int(input("Search for phone number: "))

    if search(root, number) is True:
        print("Found {}".format(number))
    else:
        print("{} not found".format(number))


if __name__ == "__main__":
    main()