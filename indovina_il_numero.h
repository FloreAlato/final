//
// Created by dando on 21/07/2022.
//

#ifndef NUOVO_INDOVINA_IL_NUMERO_H
#define NUOVO_INDOVINA_IL_NUMERO_H

#endif //NUOVO_INDOVINA_IL_NUMERO_H

#include "file.h"




// rivedere

int indovina_il_numero(Elenco *gruppetto, int size) {

    int numero, d, scelta;

    printf("\n\nSI COMINCIA! Osa scegliero' un numero da 1 a 999 e tutti voi dovrete indovinarlo!");

    numero = (rand() % 999) + 1;

    for(d = 0; d < size; d++) {

        if(is_player(gruppetto[d])) {

            scelta = get_int("\n[Tu]: ", 1, 999);
        } else {

            scelta = (rand() % 999) + 1;

            printf("[Giocatore ");
            print_player(gruppetto[d]);
            printf("]: %d", scelta);
        }

        if(scelta == numero) {
            printf("\n\nCORRETTO!!!! Hai vinto questa partita!");
            return gruppetto[d].id;
        } else if(scelta > numero) {
            printf("\nDi meno!");
        } else {
            printf("\nDi piu'!");
        }
    }

    return 0;
}





