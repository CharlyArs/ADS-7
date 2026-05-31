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
    
    countOp = 0; // Сбрасываем счетчик для чистоты эксперимента
    Car* current = first;
    
    // 1. Включаем свет в текущем (первом) вагоне
    current->light = true; 
    
    int length = 0;
    while (true) {
        // 2. Идем вперед, пока не встретим вагон с включенным светом
        do {
            current = current->next;
            countOp++;
            length++;
        } while (!current->light);
        
        // 3. Выключаем найденный свет
        current->light = false;
        
        // 4. Возвращаемся назад на length шагов к стартовому вагону
        for (int i = 0; i < length; ++i) {
            current = current->prev;
            countOp++;
        }
        
        // 5. Проверяем свет в стартовом вагоне
        if (!current->light) {
            // Свет выключен -> мы обошли весь круг
            return length;
        }
        
        // Свет включен -> это был не наш стартовый вагон. 
        // Возвращаемся туда, где были, и продолжаем поиск.
        for (int i = 0; i < length; ++i) {
            current = current->next;
            countOp++;
        }
    }
}
