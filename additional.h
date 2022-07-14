//
// Created by dando on 14/07/2022.
//

#ifndef NUOVO_ADDITIONAL_H
#define NUOVO_ADDITIONAL_H

#endif //NUOVO_ADDITIONAL_H


#include <stdio.h>
#include <stdlib.h>







void write_file() {

    FILE *file = NULL;

    char names[4][32] = {
            "savegame_Nplayeres_game",
            "savegame_Nplayeres_noGame",
            "savegame_twoPlayers_game",
            "savegame_twoPlayers_noGame"
    };

    file = fopen("../cmake-build-debug/Save_Files/savegame_files.bin", "wb");
    if(file == NULL) {
        printf("\n\nERRORE! Impossibile aprire file!");
        exit(-1);
    }

    //


    fclose(file);
}
