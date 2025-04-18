//
// Created by julia on 4/10/2025.
//

#include "Graph.h"
#include "Film.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;

//Debug functions: run search from command line
int menu(Graph& g) {
    int option = -1;
    while (true) {
        cout << endl << "What would you like to do?" << endl;
        cout << "1. Search" << endl;
        cout << "0. Exit" << endl;
        cin >> option;
        cin.ignore();

        if (option == 1) {
            string a, b; //Name for start and finish on path

            cout << "Enter first actor name:" << endl;
            getline(cin, a);
            cout << "Enter second actor name:" << endl;
            getline(cin, b);

            Actor* begin = g.findByActorName(a);
            Actor* end = g.findByActorName(b);

            if (!begin) {
                cout << "Could not find " << a << " in list." << endl;
            }

            if (!end) {
                cout << "Could not find " << b << " in list." << endl;
                continue;
            }

            cout << endl << "Which search would you like to use?" << endl;
            cout << "1. BFS" << endl;
            cout << "2. Dijkstra's" << endl;
            cout << "0. Exit" << endl;
            cin >> option;

            if (option == 1) {
                auto start = chrono::steady_clock::now();

                vector<Actor*> path;

                if (begin && end) {
                    path = g.BFSPath(a, b);
                }

                auto finish = chrono::steady_clock::now();

                chrono::duration<double> elapsed_seconds{finish - start};

                cout << "Searched for " << elapsed_seconds.count() << " seconds." << endl;

                if (path.empty()) {
                    cout << "No path between actors." << endl;
                } else {
                    for (auto it : path) {
                        cout << it->getName() << endl;
                    }
                }
            } else if (option == 2) {
                auto start = chrono::steady_clock::now();

                vector<Actor*> path;

                if (begin && end) {
                    path = g.DijkstrasPath(begin, end);
                }

                auto finish = chrono::steady_clock::now();

                chrono::duration<double> elapsed_seconds{finish - start};

                cout << "Searched for " << elapsed_seconds.count() << " seconds." << endl;

                if (path.empty()) {
                    cout << "No path between actors." << endl;
                } else {
                    for (auto it : path) {
                        cout << it->getName() << endl;
                    }
                }
            } else {
                break;
            }
        }

    }
}

//Main function: Make a separate function to read file and create objects?
int main() {
    //Build graph from CSV
    auto start{chrono::steady_clock::now()}; //Timer for building graph - Starts here

    Graph g;

    string filename = "Datasets/actors.csv";
    ifstream data(filename);
    string line;

    int count = 0;

    if (!data.is_open()) {
        cout << "Could not open file" << endl;
        return 0;
    }

    getline(data, line);

    while (getline(data, line) && count <= 100000) {
        string stringID, actorName;
        stringstream ss(line);

        count++;

        if (getline(ss, stringID, ',') && getline(ss, actorName, ',')) {

        try {
            int filmID = stoi(stringID);

            Film* f = nullptr;
            Actor* a = nullptr;

            f = g.findByID(filmID);
            if (!f) {
                f = new Film(filmID);
                g.addFilm(f);
            }

            a = g.findByActorName(actorName);
            if (!a) {
                a = new Actor(actorName);
                g.addActor(a);
            }

            if (f && a) {
                f->addActor(a);
            }

        } catch (const invalid_argument& e) {
            cerr << "Something went wrong with ID " << stringID << endl;
        }
        } else {
            std::cerr << "Error: Invalid CSV format in line: " << line << std::endl;
        }
    }

    auto finish{chrono::steady_clock::now()};

    chrono::duration<double> elapsed_seconds{finish - start};

    cout << "Graph built in ";
    cout << elapsed_seconds.count();
    cout << " seconds." << endl;
    cout << "There are " << g.getActorNum() << " actors and " << g.getFilmNum() << " films." << endl;

    menu(g); //Displays a menu for searching - CLI testing, mostly

    return 0;
}