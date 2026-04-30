#include <Arduino.h>
#include "timer.h"
#include "labirinto.h"

void Timer::inicializar(){
    Serial.begin(9600);
    delay(10000);
    Serial.println("Inicializando...");
    delay(5000);
    Serial.println("Desarme a bomba, 3 modulos para ser desarmados");
    Serial.println("Voce tem 5 minutos para desarmar a bomba,");
    Serial.println("Atente-se aos detalhes...");
    delay(5000);
    Serial.println("Boa sorte :)");
    delay(5000);
}

void Timer::acerto(){
    int melodia[] = {523, 659, 784, 1047}; // C5, E5, G5, C6
    int duracao[] = {150, 150, 150, 300};
    
    qtdVenceu++;
    
    for (int i = 0; i < 4; i++) {
        tone(pinBuzzer, melodia[i], duracao[i]);
        delay(duracao[i] * 1.3);
    }
    
    noTone(pinBuzzer);
    
    if(qtdVenceu == 3){
        printf("Parabens! Voce venceu o jogo!\n");
        printf("Tempo restante: %d:%d\n", tempoRes / 60, tempoRes % 60);
        while(1); //loop infinito para parar o código
    }
    
    printf("Voce acertou!\nModulos restantes: %d\n", 3 - qtdVenceu);  
}

void Timer::erro(){
    // Frequência: ~2000–3000 Hz
    // Padrão:
    // ligado 100 ms
    // desligado 100 ms
    // repetir 2 ou 3 vezes
    
    velocidadeAtual++;
    
    if(velocidadeAtual < 3){
        for(int i = 0; i < 3; i++){
            tone(pinBuzzer, 1500, 100);
            delay(200);
        }
        printf("Voce errou!\nErros restantes: %d\n", 3 - velocidadeAtual);
    } else {
        printf("EXPLODIU! O tempo acabou!");
        printf(":(((");
        tone(pinBuzzer, 3000);
        while(1);
    }
}

void Timer::fazerBip(){
    switch(velocidadeAtual){
        case 0:
        tone(pinBuzzer, 800, 100);
            break;
        case 1:
            tone(pinBuzzer, 1500 * 2, 100);
            break;
        case 2:
            tone(pinBuzzer, 2500 * 2, 100);
        break;
    }
}

void Timer::atualizar(){
    tempoAtual = millis();

    if(tempoAtual - tempoAnterior >= velocidades[velocidadeAtual]){
        tempoAnterior = tempoAtual;
        fazerBip();
        
        printf("Tempo restante: %d:%d\n", tempoRes / 60, tempoRes % 60);
        tempoRes--;
    }

    if(tempoRes < 0){
        erro();
    }
}