#include "file.h"



int main() {



    //TESTING
    int i, j, d;
    char f;

    int numero_giocatori, numero_giocatori_veri;
    int *giocatori = NULL;
    bool *giocatori_vivi = NULL;
    ProfiloGiocatore *giocatori_veri;
    FILE *file = NULL;

    bool nuovo;
    int scelta, prosegui;
    char opzioni[2][10] = {"carica", "inserisci"};
    char scelte[4][10] = {"continua", "salva", "inizia", "esci"};
    char filename[31] = "savegame_twoPlayers_noGame.bin\0";
    char *file_path = NULL;
    char **files = NULL;
    int numero_profili;

    int id;






    // SCELTA DELL'OPERAZIONE DA SVOLGERE: INSERIRE UN PROFILO O CARICARE UNA PARTITA

    //carica una partita o inserisci un nuovo profilo giocatore
    //se inserisci il profilo, mettine un altro o salva / inizia / esci

    nuovo = (bool)choice_string("\nCosa vuoi fare? (carica / inserisci)\n[Tu]: ", 2, opzioni);

    if(nuovo) {

        numero_profili = 1;
        giocatori_veri = (ProfiloGiocatore *) calloc(numero_profili, sizeof(ProfiloGiocatore));

        do {
            giocatori_veri = (ProfiloGiocatore *) realloc(giocatori_veri, sizeof(ProfiloGiocatore) * numero_profili);   // rivedere, fa un passaggio inutile

            printf("\nNome: ");
            // debugga questa parte, il nome deve essere univoco
            scanf (" %[^\n]%*c", giocatori_veri[numero_profili - 1].nome);

            prosegui = choice_string("\nScegli l'operazione: (continua / salva / inizia / esci)\n[Tu]: ", 4, scelte);

            numero_profili++;

        } while(prosegui == 0);

        numero_profili--;

        switch(prosegui) {
            case 1:
                // salva la partita in un file senza gioco
                printf("");
                //finire
                break;
            case 2:
                break;
            case 3:
                printf("\nBene, allora alla prossima!");
                exit(0);
            default:
                printf("\nERRORE! Scelta non valida!\n");
                break;
        }

    } else {
        // parte dal presupposto che il file sia già stato scelto, da cambiare in futuro
        // inoltre non legge se la partita è in corso
        file_path = make_path(filename, "");


        file = fopen(file_path, "rb");
        if(file == NULL) {
            printf("\n\nERRORE! Impossibile aprire file!");
            exit(-1);
        }

        fread(&numero_profili, sizeof(int), 1, file);

        giocatori_veri = (ProfiloGiocatore *) calloc(numero_profili, sizeof(ProfiloGiocatore));
        leggi_giocatori(file, numero_profili, giocatori_veri);

        for(i = 0; i < numero_profili; i++) {
            printf("\n%s", giocatori_veri[i].nome);
        }


        fclose(file);
    }



    // INIZIO PARTITA

    numero_giocatori = get_int("\n\nNumero giocatori: ", 16, 999);

    giocatori = (int *) calloc(numero_giocatori, sizeof(int));
    giocatori_vivi = (bool *) calloc(numero_giocatori, sizeof(bool));

    if(giocatori == NULL || giocatori_vivi == NULL) {
        printf("\nERRORE! Allocazione fallita!\n");
        exit(-1);
    }

    for(i = 0; i < numero_giocatori; i++) {
        giocatori[i] = i;
        giocatori_vivi[i] = true;
    }


    numero_giocatori_veri = get_int("\n\nQuanti di questi profini vuoi usare: ", 0, numero_profili);

    for(i = 0; i < numero_giocatori_veri; i++) {
        printf("\nScegli un profilo: ");
        for(j = 0; j < numero_profili; j++) {
            printf("\n[%d]: %s", j, giocatori_veri[j].nome);
        }
        // debuggare la scelta, per evitare che scelga due volte lo stesso
        // e togli quelli già scelti dalla lista
        scelta = get_int("\n\nScelta: ", 0, numero_profili);

        printf("\nE quale id avra' %s?", giocatori_veri[scelta].nome);
        id = get_int("\nId: ", 0, numero_giocatori - 1);

        giocatori[id] = -(id + 1);
    }

    printf("\n\n");
    for(i = 0; i < numero_giocatori; i++) {
        printf("\nGiocatore: %d", giocatori[i]);
    }


    /*open file template
    file = fopen("", "");
    if(file == NULL) {
        printf("\n\nERRORE! Impossibile aprire file!");
        exit(-1);
    }


    fclose(file);*/








    /*ProfiloGiocatore man = {
            3,
            "Mario",
            4,
            5,
            6,
            7,
            8
    };*/







    free(giocatori);
    free(giocatori_vivi);
    free(giocatori_veri);

    return 0;
}




