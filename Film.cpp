//
// Created by julia on 4/10/2025.
//

#include "Film.h"

Film::Film(int ID) {
    this->id=ID;
    castSize = 0;
    cast = {};
}

void Film::addActor(Actor* actor) {
    cast.insert(actor); //Adds the actor to the cast of this film. Does nothing if actor is already in cast
    actor->addFilmCredit(*this); //Adds a film credit to the actor object
    for (Actor* a : cast) { //Iterates through actors in the cast
        a->addEdge(actor);
        actor->addEdge(a);
    }
}

