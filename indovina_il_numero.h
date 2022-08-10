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

    printf("\n\nSI COMINCIA! Ora scegliero' un numero da 1 a 999 e tutti voi dovrete indovinarlo!\n\n");
    for(i = 0; i < size; i++) {
        print_player(gruppetto[i]);
        printf(" -> ");
    }
    print_player(gruppetto[size]);
    printf("\n\n");

    numero = rand_int(min, max);


    // code
    while(true) {

        for(i = 0; i <= size; i++) {

            if(is_player(gruppetto[i])) {
                // gioca
                page_down();
                printf("[");
                print_player(gruppetto[i]);
                scelta = get_int("]: ", 0, 999);
                getchar();
            } else {
                // radom
                page_down();
                scelta = rand_int(min, max);
                printf("[");
                print_player(gruppetto[i]);
                printf("]: %d", scelta);
            }

            // controlla
            // interrompi
            if(scelta > numero) {
                printf("\nTroppo alto!");
                max = scelta;
                getchar();
            } else if(scelta < numero) {
                printf("\nTroppo basso!");
                min = scelta;
                getchar();
            } else {
                printf("\nEsatto!");
                return i;
            }
        }
    }



    return numero;
}





