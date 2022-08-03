//
// Created by dando on 21/07/2022.
//

#ifndef NUOVO_INDOVINA_IL_NUMERO_H
#define NUOVO_INDOVINA_IL_NUMERO_H

#endif //NUOVO_INDOVINA_IL_NUMERO_H

#include "file.h"




// rivedere

int indovina_il_numero(Elenco *gruppetto, int size) {

    int min = 0, max = 999;
    int numero, scelta, i;

    printf("\n\nSI COMINCIA! Ora scegliero' un numero da 1 a 999 e tutti voi dovrete indovinarlo!");

    numero = rand_int(min, max);

    while(true) {
        for(i = 0; i < size; i++) {
            if(is_player(gruppetto[i])) {
                printf("\n[");
                print_player(gruppetto[i]);
                scelta = get_int("]: ", 0, 999);
                getchar();
            } else {
                printf("\n[");
                print_player(gruppetto[i]);
                scelta = rand_int(min, max);
                printf("]: %d", scelta);
            }

            if(scelta > numero) {
                printf("\n\nTroppo grande!\n");
                max = scelta;
                wait();
            } else if(scelta < numero) {
                printf("\n\nTroppo piccolo!\n");
                min = scelta;
                wait();
            } else {
                printf("\n\nHai vinto!!!");
                return i;
            }
        }
    }
}





