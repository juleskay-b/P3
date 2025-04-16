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
using namespace std;

int main() {
    //Build graph from CSV
    Graph g;

    //Vector to keep track of films and film indices

    string filename = "Datasets/actors.csv";
    ifstream data(filename);
    string line;

    if (!data.is_open()) {
        cout << "Could not open file" << endl;
    }

    while (getline(data, line)) {
        stringstream ss(line);
        string value;
        vector<string> values;

        while (getline(ss, value, ',')) {
            values.push_back(value);
        }

        // Create Film object and add it to the vector
        if (values.size() == 3) {
            int filmID = stoi(values[0]);
            string name = values[1];
            cout << filmID << " " << name << endl;
            Film* f = nullptr;
            Actor* a = nullptr;

            if (!g.isFilm(filmID)) {
                f = new Film(filmID);
                g.addFilm(f);
            }

            if (!g.isActor(name)) {
                a = new Actor(name);
                g.addActor(a);
            }

            if (f && a) {
                f->addActor(a);
            }

        } else {
            std::cerr << "Error: Invalid CSV format in line: " << line << std::endl;
        }
    }

    g.printActors();

    return 0;
}