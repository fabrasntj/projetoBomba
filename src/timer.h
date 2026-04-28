#ifndef TIMER_H
#define TIMER_H

#define pinBuzzer 32

class Timer {
    private:
        int tempoRes = 300;
        int qtdVenceu = 0;
        long unsigned int tempoAnterior = 0, tempoAtual = 0;
        int velocidades[3] = {1000, 600, 300};
        int velocidadeAtual = 0;

        void tocarSomErro();
        void fazerBip();
        
    public:
        void acerto();
        void erro();
        void inicializar();
        void atualizar();
};

#endif