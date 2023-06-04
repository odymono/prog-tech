#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Node {
    int value;
    char* str;
    Node* prev;
    Node* next;
};

Node* createNode(int value, const char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->str = (char*)malloc(strlen(str) + 1);
    strcpy(newNode->str, str);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertAfter(Node** headRef, Node* prevNode, Node* newNode) {
    if (prevNode == NULL) {
        return;
    }

    newNode->next = prevNode->next;
    newNode->prev = prevNode;
    prevNode->next = newNode;

    if (newNode->next != NULL) {
        newNode->next->prev = newNode;
    }
}

void insertBefore(Node** headRef, Node* nextNode, Node* newNode) {
    if (nextNode == NULL) {
        return;
    }

    newNode->prev = nextNode->prev;
    newNode->next = nextNode;
    nextNode->prev = newNode;

    if (newNode->prev != NULL) {
        newNode->prev->next = newNode;
    }
    else {
        *headRef = newNode;
    }
}

void insertAtHead(Node** headRef, Node* newNode) {
    newNode->next = *headRef;
    if (*headRef != NULL) {
        (*headRef)->prev = newNode;
    }
    *headRef = newNode;
}

void insertAtTail(Node** headRef, Node* newNode) {
    if (*headRef == NULL) {
        *headRef = newNode;
    }
    else {
        Node* current = *headRef;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}

void deleteNode(Node** headRef, Node* delNode) {
    if (*headRef == NULL || delNode == NULL) {
        return;
    }

    if (*headRef == delNode) {
        *headRef = delNode->next;
    }

    if (delNode->next != NULL) {
        delNode->next->prev = delNode->prev;
    }

    if (delNode->prev != NULL) {
        delNode->prev->next = delNode->next;
    }
    free(delNode->str);
    free(delNode);
}

void printList(Node* head) {
    Node* current = head;
    int count = 0;
    while (current != NULL) {
        cout << " " << endl;
        cout << count++ << "   " << current->value << " " << current->str << endl;
        current = current->next;
    }
    cout << " " << endl;
}

int main() {
    Node* head = NULL;

    while (true) {
        cout << "1. Insert At Tail\n2. Insert At Head\n3. Insert Before\n4. Insert After\n5. Delete\n6. Print\n0. Exit\n";
        int code;
        while (!(cin >> code)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (code == 1) {
            cout << "Enter integer value: ";
            int value;
            while (!(cin >> value)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Enter string value: ";
            char str[256]; cin >> str;
            Node* node = createNode(value, str);
            insertAtTail(&head, node);
        }
        else if (code == 2) {
            cout << "Enter integer value: ";
            int value;
            while (!(cin >> value)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Enter string value: ";
            char str[256]; cin >> str;
            Node* node = createNode(value, str);
            insertAtHead(&head, node);
        }
        else if (code == 3) {
            if (head == NULL) {
                cout << "List is empty.\n";
                continue;
            }

            cout << "Enter location number of the node to insert before: ";
            int value;
            while (!(cin >> value)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            Node* current = head;
            int i = 0;
            while (current != NULL) {
                if (i == value) {
                    cout << "Enter integer value: ";
                    int newValue;
                    while (!(cin >> newValue)) {
                        cout << "Invalid input. Please enter a number.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cout << "Enter string value: ";
                    char newStr[256]; cin >> newStr;
                    Node* newNode = createNode(newValue, newStr);
                    insertBefore(&head, current, newNode);
                    break;
                }
                current = current->next;
                i++;
            }
            if (current == NULL) {
                cout << "Invalid location number. Please try again.\n";
            }
        }

        else if (code == 4) {
            if (head == NULL) {
                cout << "List is empty.\n";
                continue;
            }

            cout << "Enter location number of the node to insert after: ";
            int locNumber;
            while (!(cin >> locNumber)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            int count = 0;
            Node* current = head;
            while (current != NULL) {
                if (count == locNumber) {
                    cout << "Enter integer value: ";
                    int newValue;
                    while (!(cin >> newValue)) {
                        cout << "Invalid input. Please enter a number.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cout << "Enter string value: ";
                    char newStr[256]; cin >> newStr;
                    Node* newNode = createNode(newValue, newStr);
                    insertAfter(&head, current, newNode);
                    break;
                }
                current = current->next;
                count++;
            }
            if (current == NULL) {
                cout << "Node not found at location number " << locNumber << ".\n";
            }
        }
        else if (code == 5) {
            if (head == NULL) {
                cout << "List is empty.\n";
                continue;
            }

            cout << "Enter location number of the node to delete: ";
            int location;
            while (!(cin >> location)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (location < 0) {
                cout << "Invalid location.\n";
                continue;
            }

            if (location == 0) {
                deleteNode(&head, head);
                continue;
            }

            int count = 1;
            Node* current = head;
            Node* prev = NULL;

            while (current != NULL && count != location) {
                prev = current;
                current = current->next;
                count++;
            }

            if (current == NULL) {
                cout << "Location exceeds the length of the list.\n";
                continue;
            }

            deleteNode(&head, current);
        }
        else if (code == 6) {
            if (head == NULL) {
                cout << "List is empty.\n";
                continue;
            }
            printList(head);
        }
        else if (code == 0) {
            break;
        }
        else
        {
            cout << "Invalid input. Try again.\n";
        }
    }

    // free memory
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->str);
        free(current);
        current = next;
    }

    return 0;
}