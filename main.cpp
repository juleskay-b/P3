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

int main() {
    //Build graph from CSV
    auto start{chrono::steady_clock::now()};

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

    string a, b; //Name for start and finish on path

    cout << "Enter first actor name:" << endl;;
    getline(cin, a);
    cout << "Enter second actor name:" << endl;
    getline(cin, b);

    start = chrono::steady_clock::now();

    vector<Actor*> path;

    Actor* begin = g.findByActorName(a);
    Actor* end = g.findByActorName(b);

    if (!begin) {
        cout << "Could not find " << a << " in list." << endl;
    }

    if (!end) {
        cout << "Could not find " << b << " in list." << endl;
    }

    if (begin && end) {
        path = g.BFSPath(a, b);
    }

    finish = chrono::steady_clock::now();

    elapsed_seconds = finish - start;

    cout << "Searched for " << elapsed_seconds.count() << " seconds." << endl;

    if (path.empty()) {
        cout << "No path between actors." << endl;
    } else {
        for (auto it : path) {
            cout << it->getName() << endl;
        }
    }

    return 0;
}