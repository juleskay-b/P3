//
// Created by julia on 4/10/2025.
//

#include "Graph.h"
#include "Film.h"
#include "UI.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

void readFilmData(Graph& g) {
    string filename = "Datasets/movies.csv";
    ifstream filmData(filename);
    string line;

    if (!filmData.is_open()) {
        cout << "Could not open file" << endl;
        return;
    }

    getline(filmData, line);

    while (getline(filmData, line)) {
        string stringID, filmName, year;
        stringstream ss(line);

        if (getline(ss, stringID, ',') && getline(ss, filmName, ',') && getline(ss, year, ',')) {
            try {
                int filmID = stoi(stringID);

                Film* f = g.findByID(filmID);
                if (f) {
                    filmName.erase(0, filmName.find_first_not_of(" \t"));
                    filmName.erase(filmName.find_last_not_of(" \t") + 1);

                    year.erase(0, year.find_first_not_of(" \t"));
                    year.erase(year.find_last_not_of(" \t") + 1);

                    f->name = filmName;
                    f->year = year;
                } else {
                    break; // IDs are in order; can exit early
                }

            } catch (const invalid_argument& e) {
                cerr << "Invalid ID: " << stringID << endl;
            }
        } else {
            cerr << "Error: Invalid CSV format in line: " << line << endl;
        }
    }
}

//Main function: Make a separate function to read file and create objects?
int main(int argc, char *argv[]) {
    //initialize the Qt application
    QApplication app(argc, argv);

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

    UI ui(g);
    ui.run();

    return app.exec();
}