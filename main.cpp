//Emma Bilhimer
//Busch Data Structures SP24
//Lab: UnsortedList
/* Description: A data structure of objects arranged in a linear order. The order is determined by a pointer in each object. See definition on pg. 134 and implementation on pg. 167 of the 6th
 edition of C++ Plus Data Structures. Your welcome to learn from the books implementation,
 however, make sure to write your own code. This unsorted list must be implemented with
 pointers. You will then write a client code that will have a function that will take two unsorted lists and perform the union set operation. The resulting new unsorted list will consist of all the
 unique items from the original two lists with no duplicates.
*/
#include <iostream>

// put Enum for comparison types here
enum RelationType { LESS, GREATER, EQUAL };

//  class representing the type of items in the list
class ItemType {
public:
    // my constructor
    ItemType(int value) : value(value) {}

    // getter for the value
    int getValue() const {
        return value;
    }

    // the function to compare ItemType objects
    RelationType comparedTo(ItemType otherItem) const {
        if (value < otherItem.getValue())
            return LESS;
        else if (value > otherItem.getValue())
            return GREATER;
        else
            return EQUAL;
    }

private:
    int value;
};

// use Node class to represent each element in the list
class NodeType {
public:
    ItemType info;
    NodeType* next;
};

// UnsortedType class to represent the unsorted linked list
class UnsortedType {
public:
    // Constructor
    UnsortedType() {
        length = 0;
        front = nullptr;
    }

    // a destructor
    ~UnsortedType() {
        makeEmpty();
    }

    // a method to search for an item in the list
    NodeType* search(ItemType target) {
        NodeType* current = front;
        while (current != nullptr) {
            if (current->info.comparedTo(target) == EQUAL)
                return current;
            current = current->next;
        }
        return nullptr; // Return nullptr if not found
    }

    // a method to insert an item into the list
    void insertItem(ItemType newItem) {
        NodeType* newNode = new NodeType;
        newNode->info = newItem;
        newNode->next = front;
        front = newNode;
        length++;
    }

    // a method to delete an item from the list
    void deleteItem(ItemType target) {
        NodeType* current = front;
        NodeType* previous = nullptr;

        // code to find the target node
        while (current != nullptr) {
            if (current->info.comparedTo(target) == EQUAL)
                break;
            previous = current;
            current = current->next;
        }

        // use if target node found
        if (current != nullptr) {
            if (previous == nullptr)
                front = current->next; // if the target node is the first node
            else
                previous->next = current->next;

            delete current;
            length--;
        }
    }

    // a method to get the next item in the list
    void getNextItem() {
        if (position != nullptr)
            position = position->next;
    }

    // a method to make the list empty
    void makeEmpty() {
        NodeType* tempPtr;
        while (front != nullptr) {
            tempPtr = front;
            front = front->next;
            delete tempPtr;
        }
        length = 0;
    }

    // a method to check if the list is full
    bool isFull() const {
        NodeType* location;
        try {
            location = new NodeType;
            delete location;
            return false;
        } catch (std::bad_alloc exception) {
            return true;
        }
    }

    // a method to reset the current position to the front of the list
    void resetList() {
        position = front;
    }

    // a method to get the length of the list
    int getLength() const {
        return length;
    }

    // a method to perform union operation on two lists
    UnsortedType unionLists(const UnsortedType& list2) {
        UnsortedType result;
        NodeType* current = front;

        // code to copy items from first list
        while (current != nullptr) {
            result.insertItem(current->info);
            current = current->next;
        }

        // code section to copy items from second list
        current = list2.front;
        while (current != nullptr) {
            // Check if item already exists in the result list
            if (result.search(current->info) == nullptr)
                result.insertItem(current->info);
            current = current->next;
        }

        return result;
    }

private:
    int length;
    NodeType* front;
    NodeType* position;
};

// put test function here ->
void testUnionOperation() {
    UnsortedType list1;
    list1.insertItem(ItemType(1));
    list1.insertItem(ItemType(2));
    list1.insertItem(ItemType(3));

    UnsortedType list2;
    list2.insertItem(ItemType(3));
    list2.insertItem(ItemType(4));
    list2.insertItem(ItemType(5));

    UnsortedType unionList = list1.unionLists(list2);

    unionList.resetList();
    std::cout << "Union of list1 and list2: ";
    for (int i = 0; i < unionList.getLength(); ++i) {
        ItemType item = unionList.search(unionList.position->info)->info;
        std::cout << item.getValue() << " ";
        unionList.getNextItem();
    }
    std::cout << std::endl;
}

int main() {
    testUnionOperation();
    return 0;
}

//Lab Description Continued
/* Class Names: ItemType, UnsortedType
 ▪ Attributes:
 • Max items – A constant specifying the maximum number of items to be
 on the list.
 • ItemType – A class encapsulating the type of the items in the list.
 • RelationType – An enumeration type that consists of LESS, GREATER,
 EQUAL
 • Front pointer – A pointer to the first item in the list
 • Position pointer – A pointer to the current position in the list.
 ▪ Methods:
 • Search – Search list for a given item.
 o Precondition – Given a value to search for and the object has
 been created.
 o Postcondition – A pointer to the location is returned or NULL
 pointer is return if no such item exists.
 • InsertItem – Adds item to the list.
 • DeleteItem – Deletes the element whose key matches item’s key.
 • GetNextItem – Updates position pointer to next item in the list.
 • MakeEmpty – Initializes list to empty state.
 • IsFull – Determines whether list is full.
 • ResetList – Initializes current position to front of the list.
 • ComparedTo – Determines the ordering of two ItemType objects based
 on their keys.
 • GetLength – Determines the number of elements in list.
 • Union – The mathematical set operation of union is performed on two
 given lists and a new list is created with unique elements from both
 lists.
*/
