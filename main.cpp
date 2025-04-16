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
    fstream data(filename);
    string line;

    int index = 0; //Counter to track film index

    while (std::getline(data, line)) {
        stringstream ss(line);
        string value;
        vector<string> values;

        while (getline(ss, value, ',')) {
            values.push_back(value);
        }

        // Create Film object and add it to the vector
        if (values.size() == 3) {
            int filmID = stoi(values[0]);
            string lastName = values[1].substr(values[1].find(' '));
            string firstName = values[1].substr(0, values[1].find(' '));
            string actorName = lastName + ", " + firstName;
            Film* f = g.findByID(filmID);

            if (f == nullptr) {
                f = new Film(filmID);
                g.addFilm(filmID, f);
            }

            Actor* a = g.findByActorName(actorName);

            if (a == nullptr) {
                a = new Actor(lastName, firstName);
                g.addActor(actorName, new Actor(lastName, firstName));
            }


            f->addActor(a);

        } else {
            std::cerr << "Error: Invalid CSV format in line: " << line << std::endl;
        }
    }

    return 0;
}