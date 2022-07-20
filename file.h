//
// Created by dando on 25/05/22.
//

#ifndef NUOVO_FILE_H
#define NUOVO_FILE_H

#endif //NUOVO_FILE_H


#include "main.h"



char names[4][32] = {
        "savegame_Nplayers_game",
        "savegame_Nplayers_noGame",
        "savegame_twoPlayers_game",
        "savegame_twoPlayers_noGame"
};









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

void scrivi_giocatori(FILE *file, int num, ProfiloGiocatore *giocatori) {

    for(int i = 0; i < num; i++) {
        fwrite(&giocatori[i].index, sizeof(int), 1, file);
        fwrite(&giocatori[i].nome, sizeof(char), 64, file);
        fwrite(&giocatori[i].spr1d_game_giocati, sizeof(int), 1, file);
        fwrite(&giocatori[i].spr1d_game_vinti, sizeof(int), 1, file);
        fwrite(&giocatori[i].finali_giocate, sizeof(int), 1, file);
        fwrite(&giocatori[i].giochi_giocati, sizeof(int), 1, file);
        fwrite(&giocatori[i].giochi_vinti, sizeof(int), 1, file);
    }
}







FILE *fopen_secure(char *filename, char *mode) {

    FILE *file = NULL;
    file = fopen(filename, mode);
    if(file == NULL) {
        printf("\n\nERRORE! Impossibile aprire file!");
        exit(-1);
    }

    return file;
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






char **list_files(FILE *file, int numero) {

    char **files = NULL;

    files = (char **) calloc(sizeof(char *), numero);
    if(files == NULL) {
        printf("\n\nERRORE! Allocazione fallita!");
        exit(-1);
    }

    // essendo una matrice, l'allocazione avviene in due parti, usando il seguente ciclo for
    // all'interno di questo avviene anche la lettura dei nomi dal file

    for(int k = 0; k < numero; k++) {
        files[k] = (char *) calloc(sizeof(char), 32);
        if(files[k] == NULL) {
            printf("\n\nERRORE! Allocazione fallita!");
            exit(-1);
        }

        fread(files[k], sizeof(char), 32, file);
    }

    return files;
}





void save(int *profili, ProfiloGiocatore *players, bool *game, char *filename) {

    FILE *file = NULL;

    file = fopen_secure(make_path(filename, ".bin"), "wb");

    fwrite(profili, sizeof(int), 1, file);
    scrivi_giocatori(file, *profili, players);
    fwrite(game, sizeof(int), 1, file);

    fclose(file);
}







void add_file(char *newname) {

    FILE *file = NULL;
    int many, n;
    char **filenames = NULL;

    file = fopen_secure(make_path("savegame_files", ".bin"), "rb");

    fread(&many, sizeof(int), 1, file);

    filenames = list_files(file, many);

    fclose(file);

    for(int d = 0; d < many; d++) {
        printf("\n%s", filenames[d]);
    }



    many++;


    file = fopen_secure(make_path("savegame_files", ".bin"), "wb");

    fwrite(&many, sizeof(int), 1, file);

    for(n = 0; n < many - 1; n++) {
        fwrite(filenames[n], sizeof(char), 32, file);
    }
    fwrite(newname, sizeof(char), 32, file);

    fclose(file);



    free(filenames);
}






void restore() {

    FILE *file = NULL;
    int i, num = 4;

    file = fopen_secure(make_path("savegame_files", ".bin"), "wb");

    fwrite(&num, sizeof(int), 1, file);
    for(i = 0; i < num; i++) {
        fwrite(&names[i], sizeof(char), 32, file);
    }

    fclose(file);
}


