//
// Created by dando on 25/05/22.
//

#ifndef NUOVO_FILE_H
#define NUOVO_FILE_H

#endif //NUOVO_FILE_H


#include "main.h"







void list_files() {

    FILE *file = NULL;
    char filename[40];

    file = fopen("../cmake-build-debug/Save_Files/savegame_files.txt", "r");

    if(file == NULL) {
        printf("\nERRORE! Il file non e' stato trovato!\n");
        return;
    }

    while(feof(file) == 0) {
        fgets(filename, 39, file);
        printf("File: %s", filename);
    }

    fclose(file);
}









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






void get_filenames() {

    char n;
    int num;
    char **filenames = NULL;
    FILE *file = NULL;

    file = fopen("../cmake-build-debug/Save_Files/savegame_files.txt", "r");
    if(file == NULL) {
        printf("\n\nERRORE! Impossibile aorire file!");
        exit(-1);
    }

    fread(&n, sizeof(char), 1, file);
    num = string_to_int(&n);

    printf("\n\n%d", num);


    //code



    fclose(file);
}

