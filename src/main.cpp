#include <Arduino.h>
// #include "Labirinto.h"
#include "timer.h"
#include "labirinto.h"
#include "fio.h"

// Labirinto labirinto;
Labirinto labirinto;
Timer timer;
Fio fio;

void setup() {
    // labirinto.inicializar();
    timer.inicializar();
    labirinto.inicializar();
    fio.inicializar(&timer);
}

void loop() {
    timer.atualizar();
    labirinto.atualizar(&timer);
    fio.atualizar();
    // labirinto.atualizar();
}