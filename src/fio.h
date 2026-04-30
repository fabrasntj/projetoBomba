#ifndef FIO_H
#define FIO_H

#include <Arduino.h>
#include "timer.h"

class Fio {
private:
    int pinos[4] = {13, 12, 25, 27};
    bool statusFios[4] = {false, false, false, false};

    Timer *timer; // ponteiro pro Timer

    void checarFio(int indice);

public:
    void inicializar(Timer *t);
    void atualizar();
};

#endif