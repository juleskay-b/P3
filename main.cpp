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

    //Open file
    string filename = "Datasets/actors.csv";
    ifstream data(filename);
    string line;

    if (!data.is_open()) {
        cout << "Could not open file" << endl;
        return 0;
    }

    //Remove first line of CSV
    getline(data, line);

    //Read the first two columns of CSV. Maybe add functionality for the third, but not a priority
    while (getline(data, line)) {
        string stringID, actorName;
        stringstream ss(line);

        if (getline(ss, stringID, ',') && getline(ss, actorName, ',')) {

            //Try to create an object for the film and actor, and creates edges between actors
        try {
            int filmID = stoi(stringID);

            Film* f = nullptr;
            Actor* a = nullptr;

            if (!g.isFilm(filmID)) { //If film does not already exist in the list
                f = new Film(filmID);
                g.addFilm(f);
            } else {
                f = g.findByID(filmID);
            }

            if (!g.isActor(actorName)) { //If actor does not already exist in the list
                a = new Actor(actorName);
                g.addActor(a);
            } else {
                a = g.findByActorName(actorName);
            }

            if (f && a) { //If both are successfully created, add the actor to the movie
                f->addActor(a);
            }
        } catch (const invalid_argument& e) {
            cerr << "Something went wrong with ID " << stringID << endl; //If the ID does not work for any reason
        }
        } else {
            std::cerr << "Error: Invalid CSV format in line: " << line << std::endl; //If line is incorrect/messed up
        }
    }

    //Close file
    data.close();

    //Add additional functionality here
    return 0;
}