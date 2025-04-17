//
// Created by julia on 4/10/2025.
//

#include "Graph.h"
#include "Film.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

//Trim string - helps remove '' and # from CSV
//From https://gist.github.com/letiantian/a51003ae3f9896ee68d8c51f26c9312f

int main() {
    //Build graph from CSV
    Graph g;

    string filename = "Datasets/actors.csv";
    ifstream data(filename);
    string line;

    if (!data.is_open()) {
        cout << "Could not open file" << endl;
        return 0;
    }

    getline(data, line);

    while (getline(data, line)) {
        string stringID, actorName;
        stringstream ss(line);

        if (getline(ss, stringID, ',') && getline(ss, actorName, ',')) {

        try {
            int filmID = stoi(stringID);

            Film* f = nullptr;
            Actor* a = nullptr;

            if (!g.isFilm(filmID)) {
                f = new Film(filmID);
                g.addFilm(f);
            } else {
                f = g.findByID(filmID);
            }

            if (!g.isActor(actorName)) {
                a = new Actor(actorName);
                g.addActor(a);
            } else {
                a = g.findByActorName(actorName);
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

    g.printAdjacent("Zendaya");

    return 0;
}