//
// Created by julia on 4/10/2025.
//

#include "Film.h"

Film::Film(int ID) {
    this->id = ID;
    castSize = 0; //Might need this, idk though
    cast = {};
    //Add information like year, other stuff if possible
    year = 0;
    name = "";
}

void Film::addActor(Actor* actor) {
    cast.insert(actor); //Adds the actor to the cast of this film. Does nothing if actor is already in cast
    actor->addFilmCredit(this); //Adds a film credit to the actor object
    for (Actor* a : cast) { //Iterates through actors in the cast
        if (a->getName() != actor->getName()) {
            a->addEdge(actor);
            actor->addEdge(a);
        }
    }
    castSize++;
}

Actor::Actor(const string& name) { //Constructor
    this->name = name;
    numFilms = 0;
    adjacent = {};
    films = {};
}

//Adds a film to the films list
void Actor::addFilmCredit(Film *film) {
    films.insert(film);
    numFilms++;
}

//Adds a connection to another actor, and increases the connection weight if it already exists
void Actor::addEdge(Actor *actor) {
    string actorName = actor->getName();
    if (adjacent.find(actorName) != adjacent.end()) {
        adjacent[actorName]++; //Increase the number of films instead of adding a new actor
    } else {
        adjacent[actorName] = 1;
    }
}

//Getters
string Actor::getName() {
    return name;
}

unordered_map<string, int>& Actor::getAdjacent() {
    return adjacent;
}

set<Film *> &Actor::getFilms() {
    return films;
}




