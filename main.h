//
// Created by dando on 25/05/22.
//

#ifndef NUOVO_MAIN_H
#define NUOVO_MAIN_H

#endif //NUOVO_MAIN_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>



typedef struct {
    int index;
    char nome[64];
    int spr1d_game_giocati;
    int spr1d_game_vinti;
    int finali_giocate;
    int giochi_giocati;
    int giochi_vinti;
} ProfiloGiocatore;








int potenza(int x, int y) {

    int r = x;

    if(y == 0) {
        return 1;
    } else {
        for(int i = 1; i < y; i++) {
            r *= x;
        }
        return r;
    }
}





// non riconosce i numeri negatibi

bool is_numeric(char *num) {

    for(int i = 0; i < strlen(num); i++) {
        if(num[i] < 48 || num[i] > 57) {
            return false;
        }
    }

    return true;
}




















/*controlla che una stringa contenga solo caratteri numerici
//prende un puntatore a stringa e ritorna un booleano

bool check_num(char *p) {

    bool correct = true;

    //itera fra i caratteri della stringa
    for(int i = 0; i < strlen(p); i++) {

        //controlla che sia un numero nella tabella ascii
        if(p[i] < 48 || p[i] > 57) {
            printf("\nQuesto non e' un numero\n");
            printf("Dai, ritenta...\n\n");
            correct = false;
            break;
        }
    }

    return correct;
}



*/
//converte una stringa in un intero
//prende un puntatore a stringa e ritorna un intero

int string_to_int(char *str) {

    int k, p, total = 0;

    //itera per la stringa da destra verso sinistra escludendo il carattere di fine stringa
    for(k = (int)strlen(str) - 1, p = 0; k >= 0; k--, p++) {

        //calcola il calore di ogni cifra e lo aggiunde al risultato
        total += ((int) str[k] - 48) * potenza(10, p);
    }

    return total;
}








//raccoglie un numero compreso in un intervallo
//prende un puntatore a stringa e due interi e restituisce un intero

int get_int(char *query, int min, int max) {

    char num[4];
    int number = 0;
    bool check = true;

    do {
        //pone la domanda e raccoglie la risposta sotto forma di stringa
        printf("%s", query);
        scanf(" %s", num);

        //controlla che la stringa sia numerica con una funzione apposita
        if(is_numeric(num) == true) {
            //se lo è, la converte in un intero con una funzione apposita
            number = string_to_int(num);
            check = true;
            //poi controlla che sia incluso nell'intervallo
            if(number < min) {
                printf("\nIl numero deve essere maggiore di o uguale a %d\n", min);
                printf("Dai, ritenta...\n\n");
                check = false;
            } else if(number > max) {
                printf("\nIl numero deve essere maggiore di o uguale a %d\n", max);
                printf("Dai, ritenta...\n\n");
                check = false;
            }
        } else {
            printf("\nnon numero!!\nRitenta...\n\n");
            check = false;
        }
        //in ogni altro caso ripete il loop
    } while(check == false);

    return number;
}






int choice_string(char *query, int num, char options[num][10]) {

    int answer = num + 2;
    bool check = true;

    char choice[20];

    do {
        check = true;
        printf("%s", query);
        scanf("%s", choice);

        for(int i = 0; i < num; i++) {
            if(strcmp(choice, options[i]) == 0) {
                answer = i;
            }
        }
        if(answer > num) {
            printf("\nSBAGLIATO! Scegli una delle opzioni!");
            check = false;
        }
    } while(check == false);

    return answer;
}





char *print_player(int num, ProfiloGiocatore *players) {

    //rimuove il controllo giocatore
    int player = num;
    if(player < 0) {
        return players[player].nome;
    }

    //alloca dinamicamente una stringa per poterla restituire
    char *name = NULL;

    name = (char *)malloc(sizeof(char) * 4);
    if(name == NULL) {
        return "nul\0";
    }

    name[0] = name[1] = name[2] = '0';
    name[3] = '\0';


    //assegna ad ogni carattere della stringa le rispettive cifre tramite divisioni, resti, e conversione ascii
    if(player > 99) {
        name[0] = (char)((player / 100) + 48);
        name[1] = (char)(((player % 100) / 10) + 48);
        name[2] = (char)(((player % 100) % 10) + 48);
    } else if(player > 9) {
        name[1] = (char)((player / 10) + 48);
        name[2] = (char)((player % 10) + 48);
    } else {
        name[2] = (char)(player + 48);
    }

    return name;
}