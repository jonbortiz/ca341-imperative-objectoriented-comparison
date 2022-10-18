#!/usr/bin/env python3

class Details:
    def __init__(self, name, address, number):
        self.name = name
        self.address = address
        self.number = number

def main():
    phonebook = []
    with open('../details.txt') as f:
        for line in f:
            info = line.split(",")
            name = info[0]
            address = info[1]
            number = info[2]
            # phonebook.append(Details(name, address, number))
            test = Details(name, address, number)


if __name__ == "__main__":
    main()