#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
using namespace std;

// User Contact Info
typedef struct node {
    int UserID;
    struct node* next;
} node;

// Defining User Structure
typedef struct Users {
    int id;
    char Name[50];
    struct Users* next;
} user;

// Defining entire Networking
typedef struct Graph {
    user users[MAX_USERS];
    node* adjlist[MAX_USERS];
    int numUsers;
} graph;

// Initializing Graph
void inGraph(Graph* g) {
    g->numUsers = 0;
    for (int i = 0; i < MAX_USERS; i++) {
        g->adjlist[i] = NULL; 
    }
}

// Function for adding a user
void addUser(Graph* g, int id) {
    if (g->numUsers < MAX_USERS) {
        // Create a new user node
        user newUser;
        newUser.id = id;
        cout << "Enter Your Name: ";
        cin >> newUser.Name;

        // Add the new user to the user array
        g->users[g->numUsers] = newUser;
        g->numUsers++; 

        // Initialize adjacency list for the new user
        g->adjlist[g->numUsers - 1] = NULL; 
    } else {
        cout << "User limit reached!" << endl;
    }
}

// Function for creating friendships
void addFriendship(Graph* g, int userId1, int userId2) {
    if (userId1 < g->numUsers && userId2 < g->numUsers) {
        // Add userId2 to userId1's adjacency list
        node* newNode1 = (node*)malloc(sizeof(node));
        newNode1->UserID = userId2;
        newNode1->next = g->adjlist[userId1];
        g->adjlist[userId1] = newNode1;

        // Add userId1 to userId2's adjacency list (undirected)
        node* newNode2 = (node*)malloc(sizeof(node));
        newNode2->UserID = userId1;
        newNode2->next = g->adjlist[userId2];
        g->adjlist[userId2] = newNode2;
    } else {
        cout << "Invalid user IDs for friendship." << endl;
    }
}

// Function for displaying users
void displayUsers(Graph* g) {
    for (int i = 0; i < g->numUsers; i++) {
        printf("User ID: %d, Name: %s\n", g->users[i].id, g->users[i].Name);
    }
}

// Function for displaying friendships
void displayFriendships(Graph* g) {
    for (int i = 0; i < g->numUsers; i++) {
        printf("%s's friends: ", g->users[i].Name);
        node* temp = g->adjlist[i];
        while (temp != NULL) {
            printf("%s ", g->users[temp->UserID].Name);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Function to search for a direct friend
void searchFriend(Graph* g, int userId, int friendId) {
    if (userId < 0 || userId >= g->numUsers || friendId < 0 || friendId >= g->numUsers) {
        cout << "Invalid user ID(s)." << endl;
        return;
    }
    node* temp = g->adjlist[userId];
    while (temp != NULL) {
        if (temp->UserID == friendId) {
            cout << g->users[friendId].Name << " is a direct friend of " << g->users[userId].Name << "." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << g->users[friendId].Name << " is not a direct friend of " << g->users[userId].Name << "." << endl;
}


int main() {
    Graph socialNetwork;
    inGraph(&socialNetwork);

    int choice, userId1, userId2, id;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add User\n";
        cout << "2. Add Friendship\n";
        cout << "3. Display Users\n";
        cout << "4. Display Friendships\n";
        cout << "5. Search for a Friend\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter User ID: ";
                cin >> id;
                addUser(&socialNetwork, id);
                break;
            case 2:
                cout << "Enter User ID 1: ";
                cin >> userId1;
                cout << "Enter User ID 2: ";
                cin >> userId2;
                addFriendship(&socialNetwork, userId1, userId2);
                break;
            case 3:
                cout << "Users in the network:\n";
                displayUsers(&socialNetwork);
                break;
            case 4:
                cout << "Friendships:\n";
                displayFriendships(&socialNetwork);
                break;
            case 5:
                cout << "Enter User ID: ";
                cin >> userId1;
                cout << "Enter Friend ID: ";
                cin >> userId2;
                searchFriend(&socialNetwork, userId1, userId2);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
