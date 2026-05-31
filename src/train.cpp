// Copyright 2022 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car* last = first->prev;
        newCar->next = first;
        newCar->prev = last;
        last->next = newCar;
        first->prev = newCar;
    }
}

int Train::getOpCount() {
    return countOp;
}

int Train::getLength() {
    if (!first) return 0;

    countOp = 0; 
    Car* current = first;

    current->light = true;

    int length = 0;
    while (true) {
        do {
            current = current->next;
            countOp++;
            length++;
        } while (!current->light);

        current->light = false;

        for (int i = 0; i < length; ++i) {
            current = current->prev;
            countOp++;
        }

        if (!current->light) {
            // Свет выключен -> мы обошли весь круг
            return length;
        }

        for (int i = 0; i < length; ++i) {
            current = current->next;
            countOp++;
        }
    }
}
