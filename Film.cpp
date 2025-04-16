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
        a->addEdge(actor);
        actor->addEdge(a);
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
    adjacent.insert(actor);
}

string Actor::getName() {
    return name;
}





