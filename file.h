//
// Created by dando on 25/05/22.
//

#ifndef NUOVO_FILE_H
#define NUOVO_FILE_H

#endif //NUOVO_FILE_H


#include "main.h"









void leggi_giocatori(FILE *file, int num, ProfiloGiocatore *player) {

    for(int i = 0; i < num; i++) {
        fread(&player[i].index, sizeof(int), 1, file);
        fread(&player[i].nome, sizeof(char), 64, file);
        fread(&player[i].spr1d_game_giocati, sizeof(int), 1, file);
        fread(&player[i].spr1d_game_vinti, sizeof(int), 1, file);
        fread(&player[i].finali_giocate, sizeof(int), 1, file);
        fread(&player[i].giochi_giocati, sizeof(int), 1, file);
        fread(&player[i].giochi_vinti, sizeof(int), 1, file);
    }
}



//void leggi_file(char *filename, char *mode, )




void scrivi_giocatori(int num, ProfiloGiocatore giocatore, FILE *file) {

    fwrite(&giocatore, sizeof(ProfiloGiocatore), num, file);
}




void scrivi_file(int num, ProfiloGiocatore players, bool game, FILE *file) {

    fwrite(&num, sizeof(int), 1, file);
    scrivi_giocatori(num, players, file);
    fwrite(&game, sizeof(int), 1, file);

    //comtinuare in caso game sia positivo
}





void aggiorna_lista_file(char *filename, int size, int num, bool game) {

    FILE *lista = NULL;
    lista = fopen("../cmake-build-debug/Save_Files/savegame_files.txt", "a");
    if(lista == NULL) {
        printf("\nERRORE! Impossibile aprire il file!\n");
        exit(-1);
    }

    fprintf(lista, "\n");
    fwrite(filename, sizeof(char), size, lista);
    fprintf(lista, " (%d giocatori, ", num);
    if(game) {
        fprintf(lista, "partita in corso)");
    } else {
        fprintf(lista, "niente partita)");
    }

    fclose(lista);
}




char *make_path(char filename[], char extention[]) {

    char *path = NULL;

    path = (char *) calloc(63, sizeof(char));
    if(path == NULL) {
        printf("\n\nERRORE! Allocazione fallita!");
        exit(-1);
    }

    strcpy(path, "../cmake-build-debug/Save_Files/");
    strcat(path, filename);
    strcat(path, extention);

    return path;
}


