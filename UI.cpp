//
// Created by Ana Petrela on 4/17/25.
//

#include "UI.h"
#include <iostream>
#include <chrono>
using namespace std;

UI::UI(Graph &g) : graph(g) {}

void UI::run() {
    while (true) {
        showMenu();
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            findShortestPath();
        }
        else if (choice == "2") {
            showActorFilms();
        }
        else if (choice == "3") {
            showCoStars();
        }
        else if (choice == "4") {
            cout << "Byeeeeeee!" << endl;
            break;
        }
        else {
            cout << "You done goofed up on the spelling!" << endl;
        }
    }
}

void UI::showMenu() {
    cout << "+++ Star Fishing +++" << endl;
    cout << "1. Find shortest path between two actors" << endl;
    cout << "2. Show all films an actor was in" << endl;
    cout << "3. Show all co-stars of an actor" << endl;
    cout << "4. Quit" << endl;
}

void UI::findShortestPath() {
    string a,b;
    cout <<"Enter the first actor's name: ";
    getline(cin,a);
    cout <<"Enter the second actor's name: ";
    getline(cin,b);

    Actor* begin = graph.findByActorName(a);
    Actor* end = graph.findByActorName(b);

    if (!begin) {
        cout << "Couldn't find " << a << " in list." << endl;
        return;
    }

    if (!end) {
        cout << "Couldn't find " << b << " in list." << endl;
        return;
    }

    cout << "Choose search algorithm: (1) BFS  (2) Dijkstra: ";
    string algo;
    getline(cin, algo);

    vector<Actor*> path;
    auto start = chrono::steady_clock::now();

    if (algo == "1") {
        path = graph.BFSPath(a, b);
    }
    else if (algo == "2") {
        path = graph.DijkstrasPath(begin, end);
    }
    else {
        cout << "Alright buddy choose for real this time." << endl;
        return;
    }

    auto finish = chrono::steady_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "Search took " << elapsed.count() << " seconds." << endl;

    if (path.empty()) {
        cout << "No path found." << endl;
    } else {
        cout << "** Shortest path: ";
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i]->getName();
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

void UI::showActorFilms() {
    string name;
    cout << "Enter the actor's name: ";
    getline(cin, name);

    if (!graph.isActor(name)) {
        cout << "Actor not found." << endl;
    } else {
        cout << "Films for " << name << ":" << endl;
        graph.printFilms(name);
    }
}

void UI::showCoStars() {
    string name;
    cout << "Enter the actor's name: ";
    getline(cin, name);

    if (!graph.isActor(name)) {
        cout << "Actor not found." << endl;
    }
    else {
        cout << "Co-Stars for " << name << ":" << endl;
        graph.printAdjacent(name);
    }
}