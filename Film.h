//
// Created by julia on 4/10/2025.
//

#ifndef FILM_H
#define FILM_H

#include <string>
#include <vector>
class Film;
using namespace std;

struct Actor {
    string lastName;
    string firstName;
    int numFilms; //The number of films the actor has appeared in for sorting purposes
    vector<Film*> films; //The list of films the actor has appeared in

    Actor(string lastName, string firstName); //Constructor
    void addFilmCredit(Film& film); //Adds a credit to the actor's list, and increases num films by 1
};

class Film {
    int id; //An ID assigned by the dataset, 10000001, 10000002, etc.
    string name; //The name of the film
    int year; //The year of the film's release
    int castSize; //The number of credited actors for the film for sorting purposes
    vector<Actor*> cast; //A vector of the actors credited in the film, sorted by number of credits

public:
    Film(int ID); //Consructor
    void addActor(Actor*); //Adds an actor to the cast list

    //Getters
    string getName();
    int getYear();
    int getCastSize();
    vector<Actor*> getCast();
};



#endif //FILM_H
