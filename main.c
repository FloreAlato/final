#include "file.h"


void scrematura(Elenco *);



int main() {



    //TESTING
    int i, j, k;

    int numero_giocatori, numero_giocatori_veri;
    Elenco *giocatori = NULL;
    ProfiloGiocatore *giocatori_veri;
    FILE *file = NULL;

    bool nuovo, esistente, scelto;
    int scelta, prosegui;
    char nome[30];
    char opzioni[2][10] = {"carica", "inserisci"};
    char scelte[4][10] = {"continua", "salva", "inizia", "esci"};
    char **files = NULL;
    int numero_files;
    int numero_profili;

    int id;
    Elenco *prov = NULL;






    // SCELTA DELL'OPERAZIONE DA SVOLGERE: INSERIRE UN PROFILO O CARICARE UNA PARTITA

    //carica una partita o inserisci un nuovo profilo giocatore
    //se inserisci il profilo, mettine un altro o salva / inizia / esci

    // carica o inserisci
    nuovo = (bool)choice_string("\nCosa vuoi fare? (carica / inserisci)\n[Tu]: ", 2, opzioni);

    // se sceglie di inserire un nuovo profilo
    if(nuovo) {

        numero_profili = 1;
        giocatori_veri = (ProfiloGiocatore *) calloc(numero_profili, sizeof(ProfiloGiocatore));

        do {
            giocatori_veri = (ProfiloGiocatore *) realloc(giocatori_veri, sizeof(ProfiloGiocatore) * numero_profili);   // rivedere, fa un passaggio inutile

            do {
                esistente = false;

                printf("\nNome: ");
                scanf (" %[^\n]%*c", nome);

                for(i = 0; i < numero_profili; i++) {
                    if(strcmp(giocatori_veri[i].nome, nome) == 0) {
                        esistente = true;
                        printf("\n\nHai gia' inserito questo nome\n\n");
                        break;
                    }
                }

                // azzera tutti i valori del giocatore e assegna il nome
                strcpy(giocatori_veri[numero_profili - 1].nome, nome);
                giocatori_veri[numero_profili - 1].index = 0;
                giocatori_veri[numero_profili - 1].spr1d_game_giocati = 0;
                giocatori_veri[numero_profili - 1].spr1d_game_vinti = 0;
                giocatori_veri[numero_profili - 1].finali_giocate = 0;
                giocatori_veri[numero_profili - 1].giochi_giocati = 0;
                giocatori_veri[numero_profili - 1].giochi_vinti = 0;


            } while(esistente == true);

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
                printf("\nALLORA COMINCIAMO!!!!!\n");
                break;
            case 3:
                printf("\nBene, allora alla prossima!");
                exit(0);
            default:
                printf("\nERRORE! Scelta non valida!\n");
                break;
        }

        // per caricare da un file esistente
    } else {

        // cominciamo
        printf("\nQuesti sono i file disponibili:\n");

        file = fopen(make_path("savegame_files", ".bin"), "rb");
        if(file == NULL) {
            printf("\n\nERRORE! Impossibile aprire file!");
            exit(-1);
        }

        fread(&numero_files, sizeof(int), 1, file);

        files = (char **) calloc(sizeof(char *), numero_files);
        if(files == NULL) {
            printf("\n\nERRORE! Allocazione fallita!");
            exit(-1);
        }

        for(k = 0; k < numero_files; k++) {
            files[k] = (char *) calloc(sizeof(char), 32);
            if(files[k] == NULL) {
                printf("\n\nERRORE! Allocazione fallita!");
                exit(-1);
            }

            fread(files[k], sizeof(char), 32, file);
        }

        fclose(file);

        for(k = 0; k < numero_files; k++) {
            printf("\n[%d] -> %s", k, files[k]);
        }

        // scegliere il file e recuperare le info
        scelta = get_int("\n\n[Tu]: ", 0, numero_files - 1);

        file = fopen(make_path(files[scelta], ".bin"), "rb");
        if(file == NULL) {
            printf("\n\nERRORE! Impossibile aprire file!");
            exit(-1);
        }

        fread(&numero_profili, sizeof(int), 1, file);

        giocatori_veri = (ProfiloGiocatore *) calloc(sizeof(ProfiloGiocatore), numero_profili);

        leggi_giocatori(file, numero_profili, giocatori_veri);

        fclose(file);


        // finire, se la partita e' iniziata bisognera' agire di conseguenza


        free(files);
    }





    // INIZIO PARTITA

    numero_giocatori = get_int("\n\nNumero giocatori: ", 16, 1000);

    giocatori = (Elenco *) calloc(numero_giocatori, sizeof(Elenco));

    if(giocatori == NULL) {
        printf("\nERRORE! Allocazione fallita!\n");
        exit(-1);
    }

    for(i = 0; i < numero_giocatori; i++) {
        giocatori[i].id = i;
        giocatori[i].p = NULL;
        giocatori[i].vivo = true;
    }


    printf("\n\nQuanti di questi %d profini vuoi usare: ", numero_profili);
    numero_giocatori_veri = get_int("", 0, numero_profili);

    prov = (Elenco *) calloc(sizeof(Elenco), numero_profili);
    if(prov == NULL) {
        printf("\nERRORE! Allocazione fallita!\n");
        exit(-1);
    }

    for(k = 0; k < numero_profili; k++) {
        prov[k].id = k;
        prov[k].p = &giocatori_veri[k];
    }


    // scelta del profilo al quale assegnare il giusto indice
    for(j = 0; j < numero_giocatori_veri; j++) {





        // stampa ancora tutti i profili, da correggere

        printf("\nProfili a disposizione:");

        for(i = 0; i < numero_profili; i++) {

            if(prov[i].p != NULL) {
                printf("\n[%d] -> %s", i, prov[i].p->nome);
            }
        }




        // deebuggato, non puoi scegliere due volte lo stesso profilo

        do {
            scelta = get_int("\n\n[Tu]: ", 0, numero_giocatori_veri);
            if(prov[scelta].p == NULL) {
                printf("\nQuesto giocatore e' gia' stato scelto!");
            }
        } while(prov[scelta].p == NULL);




        // debuggato, non puoi inserire lo stesso id per due profili
        do {
            scelto = false;
            printf("\nId di %s: ", prov[scelta].p->nome);
            id = get_int("", 0, numero_giocatori);
            if(giocatori[id].p == NULL) {
                giocatori_veri[scelta].index = id;
                giocatori[id].p = &giocatori_veri[scelta];
            } else {
                printf("\nQuesto id e' gia' preso, inseriscine un altro...");
                scelto = true;
            }
        } while(scelto == true);

        prov[scelta].p = NULL;
    }

    free(prov);








    // stampa la lista dei giocatori

    printf("\n\n");
    for(i = 0; i < numero_giocatori; i++) {
        printf("\n[");
        print_player(giocatori[i]);
        printf("] -> ");

        if(giocatori[i].vivo == true) {
            printf(" <vivo>");
        } else {
            printf(" <morto>");
        }
    }

    // stampa i profili giocatore

    printf("\n\n");
    for(i = 0; i < numero_profili; i++) {

        printf("\n[%d] -> %s", giocatori_veri[i].index, giocatori_veri[i].nome);
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
    free(giocatori_veri);

    return 0;
}







void scrematura(Elenco *giocatori) {

    // ridurre il numero dei giocatori

}

