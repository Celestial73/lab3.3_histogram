#pragma once
#include <iostream>
#include "../pointers/SharedPtr.h"
#include "../pointers/UniquePtr.h"

template <class T>
struct Node
{
    T item;
    SharedPtr<Node<T>> next;
};

template <class T>
class LinkedList
{
private:
    SharedPtr<Node<T>> head;
    SharedPtr<Node<T>> tail;
    int listSize;

public:
    // Constructor with array of items
    LinkedList(T *items, int count) : head(nullptr), tail(nullptr)
    {
        int itemsIndex = 0;
        this->listSize = 0;
        for (int i = 0; i < count; ++i)
        {
            append(items[itemsIndex++]);
        }

        this->listSize = count;
    }

    // Default constructor
    LinkedList()
    {
        this->head = SharedPtr<Node<T>>();
        this->tail = SharedPtr<Node<T>>();
        this->listSize = 0;
    }

    // Copy constructor
    LinkedList(const LinkedList<T> &other)
    {
        this->listSize = other.listSize;
        SharedPtr<Node<T>> otherTraverseNode = other.head;

        for (int i = 0; i < other.getLength(); i++)
        {
            append(otherTraverseNode->item);
            otherTraverseNode = otherTraverseNode->next;
        }
    }

    // Get the first element
    const T &getFirst() const
    {
        if (this->head.get() == nullptr)
        {
            throw std::out_of_range("Empty list.");
        }
        else
        {
            return this->head->item;
        }
    }

    T &getFirst()
    {
        if (this->head.get() == nullptr)
        {
            throw std::out_of_range("Empty list.");
        }
        else
        {
            return this->head->item;
        }
    }

    // Get the last element
    const T &getLast() const
    {
        if (this->head.get() == nullptr)
        {
            throw std::out_of_range("Empty list.");
        }
        else
        {
            return this->tail->item;
        }
    }

    T &getLast()
    {
        if (this->head.get() == nullptr)
        {
            throw std::out_of_range("Empty list.");
        }
        else
        {
            return this->tail->item;
        }
    }

    // Get an element by index
    const T &get(int index) const
    {
        if (index < 0 || index >= this->listSize)
        {
            throw std::out_of_range("Invalid index.");
        }

        Node<T> *currentNode = this->head.get();
        for (int i = 0; i < index; ++i)
        {
            currentNode = currentNode->next.get();
        }

        return currentNode->item;
    }

    // Get an element by index
    T &get(int index)
    {
        if (index < 0 || index >= this->listSize)
        {
            throw std::out_of_range("Invalid index.");
        }

        Node<T> *currentNode = this->head.get();
        for (int i = 0; i < index; ++i)
        {
            currentNode = currentNode->next.get();
        }

        return currentNode->item;
    }

    // Get a sublist from startIndex to endIndex
    LinkedList<T> *getSubList(int startIndex, int endIndex)
    {
        if (startIndex < 0 || endIndex >= listSize || startIndex > endIndex)
        {
            throw std::out_of_range("Invalid index range");
        }

        LinkedList<T> *subList = new LinkedList<T>();
        Node<T> *current = head.get();
        int index = 0;

        while (current != nullptr)
        {
            if (index >= startIndex && index <= endIndex)
            {
                subList->append(current->item);
            }
            current = current->next.get();
            index++;
        }
        return subList;
    }

    // Get the length of the list
    int getLength() const
    {
        return this->listSize;
    }

    // Append an item to the end of the list
    void append(T item)
    {
        SharedPtr<Node<T>> newNode = SharedPtr<Node<T>>(new Node<T>());
        newNode->item = item;
        newNode->next = SharedPtr<Node<T>>();

        if (listSize == 0)
        {
            head = newNode; // Move newNode to head
        }
        else
        {
            tail->next = newNode; // Move newNode to tail's next
        }
        tail = newNode; // Move newNode to tail
        listSize++;
    }

    // Prepend an item to the beginning of the list
    void prepend(T item)
    {
        SharedPtr<Node<T>> newNode = SharedPtr<Node<T>>(new Node<T>());
        newNode->item = item;
        newNode->next = this->head; // Move current head to newNode's next
        this->head = newNode;       // Move newNode to head

        if (listSize == 0)
        {
            tail = head.get(); // Only update tail if list was empty
        }
        listSize++;
    }

    // Insert an item at a specific index
    void insertAt(T item, int index)
    {
        if (index < 0 || index > this->listSize)
        {
            throw std::out_of_range("Invalid index.");
        }
        SharedPtr<Node<T>> newNode = SharedPtr<Node<T>>(new Node<T>());
        newNode->item = item;

        if (index == 0)
        {
            newNode->next = this->head; // Move head to newNode's next
            this->head = newNode;       // Move newNode to head
        }
        else
        {
            Node<T> *currentNode = this->head.get();
            for (int i = 0; i < index - 1; ++i)
            {
                currentNode = currentNode->next.get();
            }

            newNode->next = currentNode->next; // Move current node's next to newNode's next
            currentNode->next = newNode;       // Move newNode to current node's next

            if (index == listSize)
            {
                tail = currentNode->next; // Update tail if new node is added at the end
            }
        }

        listSize++;
    }

    void set(int index, T value)
    {
        if (index < 0 || index >= listSize)
        {
            throw std::invalid_argument("Error: Index out of range");
        }

        SharedPtr<Node<T>> current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        current->item = value;
    }

    void removeAt(int index)
    {
        if (index < 0 || index >= listSize)
        {
            throw std::out_of_range("Invalid index.");
        }

        if (index == 0)
        {
            head = head->next;
            if (listSize == 1)
            {
                tail = SharedPtr<Node<T>>();
            }
        }
        else
        {
            Node<T> *current = head.get();
            for (int i = 0; i < index - 1; ++i)
            {
                current = current->next.get();
            }

            current->next = current->next->next;
            if (index == listSize - 1)
            {
                tail = SharedPtr<Node<T>>(current);
            }
        }

        listSize--;
    }

    UniquePtr<LinkedList<T>> copy()
    {
        LinkedList<T> *newList = new LinkedList<T>();
        newList->listSize = this->listSize;
        SharedPtr<Node<T>> transferNode1 = this->head;

        newList->head = SharedPtr<Node<T>>(new Node<T>());
        newList->head->item = this->head->item;
        SharedPtr<Node<T>> newListTransferNode = newList->head;

        for (int i = 0; i < listSize - 1; i++)
        {
            transferNode1 = transferNode1->next;
            newListTransferNode->next = SharedPtr<Node<T>>(new Node<T>());
            newListTransferNode->next->item = transferNode1->item;
            newListTransferNode = newListTransferNode->next;
        }

        return UniquePtr(newList);
    }

    // Concatenate two linked lists
    UniquePtr<LinkedList<T>> concat(LinkedList<T> *other)
    {
        LinkedList<T> *newList = new LinkedList<T>();
        newList->listSize = this->listSize + other->listSize;

        SharedPtr<Node<T>> transferNode1 = this->head;

        newList->head = SharedPtr<Node<T>>(new Node<T>());
        newList->head->item = this->head->item;
        SharedPtr<Node<T>> newListTransferNode = newList->head;

        for (int i = 0; i < listSize - 1; i++)
        {
            transferNode1 = transferNode1->next;
            newListTransferNode->next = SharedPtr<Node<T>>(new Node<T>());
            newListTransferNode->next->item = transferNode1->item;
            newListTransferNode = newListTransferNode->next;
        }

        SharedPtr<Node<T>> transferNode2 = other->head;
        for (int i = 0; i < other->listSize; i++)
        {
            newListTransferNode->next = SharedPtr<Node<T>>(new Node<T>());
            newListTransferNode->next->item = transferNode2->item;
            newListTransferNode = newListTransferNode->next;
            transferNode2 = transferNode2->next;
        }
        newList->tail = newListTransferNode;

        return UniquePtr(newList);
    }
};