//
// Created by julia on 4/10/2025.
//

#ifndef FILM_H
#define FILM_H

#include <string>
#include <set>
#include <unordered_map>
class Actor;
using namespace std;

struct Film {
    int id; //An ID assigned by the dataset, 10000001, 10000002, etc.
    string name; //The name of the film
    int year; //The year of the film's release
    int castSize; //The number of credited actors for the film for sorting purposes
    set<Actor*> cast; //A vector of the actors credited in the film, sorted by number of credits

    Film(int ID); //Consructor
    void addActor(Actor*); //Adds an actor to the cast list
};

class Actor {
    string name;
    int numFilms; //The number of films the actor has appeared in for sorting purposes
    unordered_map<string, int> adjacent; //List of actors that have starred in a movie with this actor plus a weight
    set<Film*> films; //List of films this actor has starred in
public:
    Actor(const string& name); //Constructor
    void addFilmCredit(Film *film); //Adds a credit to the actor's list, and increases num films by 1
    void addEdge(Actor* actor);

    //Getters
    string getName();
    unordered_map<string, int>& getAdjacent();
    set<Film*>& getFilms();
};



#endif //FILM_H
