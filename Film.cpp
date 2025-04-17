//
// Created by julia on 4/10/2025.
//

#include "Film.h"

Film::Film(int ID) {
    this->id = ID;
    castSize = 0;
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

Actor::Actor(const string& name) {
    this->name = name;
    numFilms = 0;
    adjacent = {};
    films = {};
}

void Actor::addFilmCredit(Film *film) {
    films.insert(film);
    numFilms++;
}

void Actor::addEdge(Actor *actor) {
    string actorName = actor->getName();
    if (adjacent.find(actorName) != adjacent.end()) {
        adjacent[actorName]++;
    } else {
        adjacent[actorName] = 1;
    }
}

string Actor::getName() {
    return name;
}

unordered_map<string, int>& Actor::getAdjacent() {
    return adjacent;
}

set<Film *> &Actor::getFilms() {
    return films;
}




