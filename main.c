#include "file.h"



int main() {



    //TESTING
    int i, j, k;
    char f;

    int numero_giocatori, numero_giocatori_veri;
    Elenco *giocatori = NULL;
    bool *giocatori_vivi = NULL;
    ProfiloGiocatore *giocatori_veri;
    FILE *file = NULL;

    bool nuovo, esistente;
    int scelta, prosegui;
    char nome[30];
    char opzioni[2][10] = {"carica", "inserisci"};
    char scelte[4][10] = {"continua", "salva", "inizia", "esci"};
    char filename[31] = "savegame_twoPlayers_noGame.bin\0";
    char *file_path = NULL;
    char **files = NULL;
    int numero_profili;

    int id;
    bool *gia_scelti = NULL;






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

                strcpy(giocatori_veri[numero_profili - 1].nome, nome);


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
                // aggiungere un messaggio di inizio
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
        // parte dal presupposto che il file sia già stato scelto, da cambiare in futuro
        // inoltre non legge se la partita è in corso
        /*file_path = make_path(filename, "");


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


        fclose(file);*/
    }



    // INIZIO PARTITA

    numero_giocatori = get_int("\n\nNumero giocatori: ", 16, 999);

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


    /*printf("\n\nQuanti di questi %d profini vuoi usare: ", numero_profili);
    numero_giocatori_veri = get_int("", 0, numero_profili);


    // scelta del profilo al quale assegnare il giusto indice
    for(i = 0; i < numero_giocatori_veri; i++) {

        // il giocatore seleziona i profili da usare e gli assegna un id
        // code
    }*/




    printf("\n\n");
    for(i = 0; i < numero_giocatori; i++) {
        printf("\n[%d] -> ", giocatori[i].id);
        if(giocatori[i].p == NULL) {
            printf("CPU");
        } else {
            printf("%s", giocatori[i].p->nome);
        }
        if(giocatori[i].vivo == true) {
            printf(" <vivo>");
        } else {
            printf(" <morto>");
        }
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




