#include "fio.h"

void Fio::inicializar(Timer *t){
    timer = t;

    for (int i = 0; i < 4; i++) {
        pinMode(pinos[i], INPUT_PULLUP);
    }
}

void Fio::checarFio(int indice){
    int correto = 1; // simplificado

    if(indice == correto){
        Serial.println("Fio correto!");
        timer->acerto();  // <-- AQUI
    } else {
        Serial.println("Fio errado!");
        timer->erro();    // <-- AQUI
    }
}

void Fio::atualizar(){
    for (int i = 0; i < 4; i++) {
        if (digitalRead(pinos[i]) == HIGH && !statusFios[i]) {
            statusFios[i] = true;
            checarFio(i);
        }
    }
}