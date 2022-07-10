#include "file.h"


void scrematura(Elenco *);



int main() {



    //TESTING
    int i, j, k;

    int numero_giocatori, numero_giocatori_veri;
    Elenco *giocatori = NULL;
    ProfiloGiocatore *giocatori_veri;
    FILE *file = NULL;

    bool nuovo, esistente, scelto, game = false;
    int scelta, prosegui;
    char nome[30];
    char opzioni[2][10] = {"carica", "inserisci"};
    char scelte[4][10] = {"continua", "salva", "inizia", "esci"};
    char **files = NULL;
    int numero_files;
    int numero_profili;

    int id, segnaposto;
    Elenco *prov = NULL;

    // variabili utili se la partita è iniziata
    int *indici = NULL;
    int *vivi = NULL;






    // SCELTA DELL'OPERAZIONE DA SVOLGERE, SE CARICARE UN FILE DI SALVATAGGIO O INSERIRE UN PROFILO

    // prende un intero dall'utente e lo salva sotto forma di booleano usando la funzione choice_string()
    // choice_string() -> main.h
    // 0 per caricare una partita, 1 per inserire un profilo giocatore

    nuovo = (bool)choice_string("\nCosa vuoi fare? (carica / inserisci)\n[Tu]: ", 2, opzioni);

    if(nuovo) {

        // SE L'UTENTE SCEGLIE DI INSERIRE UN NUOVO PROFILO:

        // il numero_profili viene impostato a 1
        // poi viene allocato dinamicamente l'array di profili giocatore (per ora avrà un solo elemento)
        // se l'allocazione fallisce, il programma si arresta
        // (d'ora in poi darò per scontato questo passaggio, che avverrà dopo ogni allocazione dinamica)

        numero_profili = 1;

        giocatori_veri = (ProfiloGiocatore *) calloc(numero_profili, sizeof(ProfiloGiocatore));

        if(giocatori_veri == NULL) {
            printf("\n\nERRORE! Allocazione fallita!");
            exit(-1);
        }

        // INSERIMENTO DEI PROFILI UTENTE

        //

        do {
            // per ogni iterazione, realloca l'array dei profili per ospitare il nuovo inserimento
            // non è elegantissimo, ma questo if impedisce che si svolga un passaggio inutile alla prima iterazione

            if(numero_profili > 1) {
                giocatori_veri = (ProfiloGiocatore *) realloc(giocatori_veri, sizeof(ProfiloGiocatore) * numero_profili);
            }

            // nel ciclo seguente viene chiesto il nome del prossimo profilo e si controlla che questo sia univoco

            do {
                esistente = false;

                // inserimento del nome (accetta anche gli spazi)
                printf("\nNome: ");
                scanf (" %[^\n]%*c", nome);

                // la stringa inserita viene confrontata con tutte quelle inserite in precedenza
                // se ci sono istanze precedenti, l'utente è invitato a ripetere l'inserimento

                for(i = 0; i < numero_profili; i++) {
                    if(strcmp(giocatori_veri[i].nome, nome) == 0) {
                        esistente = true;
                        printf("\n\nHai gia' inserito questo nome\n\n");
                        break;
                    }
                }

            } while(esistente == true);

            // se il nome inserito risulta univoco, viene assegnato al rispettivo campo nell'array dei profili
            // come conseguenza della riallocazione, è buona misura azzerare i valori interi

            strcpy(giocatori_veri[numero_profili - 1].nome, nome);
            giocatori_veri[numero_profili - 1].index = 0;
            giocatori_veri[numero_profili - 1].spr1d_game_giocati = 0;
            giocatori_veri[numero_profili - 1].spr1d_game_vinti = 0;
            giocatori_veri[numero_profili - 1].finali_giocate = 0;
            giocatori_veri[numero_profili - 1].giochi_giocati = 0;
            giocatori_veri[numero_profili - 1].giochi_vinti = 0;

            // poi viene chiesto all'utente quale operazione vuole svolgere:
            // se vuole continuare a inserire profili, salvarli in un file, iniziare la partita o chiudere il programma
            // la scelta è salvata nell'intero prosegui, che farà da indice nella scelta della prossima operazione
            // viene usata la funzione choice_string()
            // choice_string -> main.h

            prosegui = choice_string("\nScegli l'operazione: (continua / salva / inizia / esci)\n[Tu]: ", 4, scelte);

            // il numero profili viene incrementato, e il ciclo si ripete se l'utente vuole continuare a inserire
            numero_profili++;

        } while(prosegui == 0);

        // ovviamente il nuemro_profili subisce un incremento di troppo, che è corretto qui

        numero_profili--;

        // SCELTA DELL'OPERAZIONE SUCCESSIVA

        // ora che abbiamo l'array completo dei profili inseriti, l'utente ha scelto la prossima operazione tramite prosegui
        // il programma scelgierà cosa fare con uno switch

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

    } else {

        // CARICARE UN FILE DI SALVATAGGIO

        // questa sezione viene eseguita se l'utente decide di caricare un file di salvataggio
        // viene presentata una lista dei file fisponibili, e si procede alla lettura di quello scelto

        printf("\nQuesti sono i file disponibili:\n");

        // i files tra cui scegliere sono salvati in un file apposito
        // vi si accede grazie alla funzione make_path()
        // make_path() -> file.h

        file = fopen(make_path("savegame_files", ".bin"), "rb");
        if(file == NULL) {
            printf("\n\nERRORE! Impossibile aprire file!");
            exit(-1);
        }

        // il programma legge quanti file sono disponibili
        // e usa questo dato per allocare la matrice con i nomi da mostrare all'utente
        // se l'apertura del file dovesse fallire, il programma si arresterebbe
        // (darò per scontato anche questo passaggio)

        fread(&numero_files, sizeof(int), 1, file);

        files = (char **) calloc(sizeof(char *), numero_files);
        if(files == NULL) {
            printf("\n\nERRORE! Allocazione fallita!");
            exit(-1);
        }

        // essendo una matrice, l'allocazione avviene in due parti, usando il seguente ciclo for
        // all'interno di questo avviene anche la lettura dei nomi dal file

        for(k = 0; k < numero_files; k++) {
            files[k] = (char *) calloc(sizeof(char), 32);
            if(files[k] == NULL) {
                printf("\n\nERRORE! Allocazione fallita!");
                exit(-1);
            }

            fread(files[k], sizeof(char), 32, file);
        }

        fclose(file);



        // i nomi letti vengono poi stampati perché l'utente possa scegliere

        for(k = 0; k < numero_files; k++) {
            printf("\n[%d] -> %s", k, files[k]);
        }

        // la scelta è salvata nell'omonima variabile intera
        // per fare ciò, si usa la funzione apposita get_int()
        // get_int() -> main.h

        scelta = get_int("\n\n[Tu]: ", 0, numero_files - 1);

        // viene aperto il file scelto grazie a make_path() e sono caricati i suoi dati

        file = fopen(make_path(files[scelta], ".bin"), "rb");
        if(file == NULL) {
            printf("\n\nERRORE! Impossibile aprire file!");
            exit(-1);
        }

        // sfruttando la struttura del file, il programma legge il numero_profili
        // poi alloca l'array che già conosciamo dalla sezione precedente

        fread(&numero_profili, sizeof(int), 1, file);

        giocatori_veri = (ProfiloGiocatore *) calloc(sizeof(ProfiloGiocatore), numero_profili);

        if(giocatori_veri == NULL) {
            printf("\n\nERRORE! Allocazione fallita!");
            exit(-1);
        }

        // l'array appena allocato viene riempito grazie all'apposita funzione leggi_giocatori()
        // leggi_giocatori() -> file.h

        leggi_giocatori(file, numero_profili, giocatori_veri);

        // poi viene letta la variabile contenente lo stato della partita, per capire se salvare altri dati

        fread(&game, sizeof(int), 1, file);

        if(game == true) {
            // finire la descrizione

            fread(&numero_giocatori, sizeof(char), 1, file);
            fread(&numero_giocatori_veri, sizeof(int), 1, file);

            // riempie la lista dei giocatori
            giocatori = componi_elenco(numero_giocatori);


            for(k = 0; k < numero_giocatori_veri; k++) {
                // mettere i giocatori al posto giusto
                // rileggere la consegna
            }
        }

        fclose(file);

        // l'array con i nomi dei files disponibili è obsoleta, e va liberata

        free(files);
    }





    // INIZIO PARTITA (correggere con un if game == false)

    numero_giocatori = get_int("\n\nNumero giocatori: ", 16, 1000);

    // riempie la lista dei giocatori
    giocatori = componi_elenco(numero_giocatori);


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


        // debuggato, lascia stampa solo i profili non ancora scelti

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
    stampa_lista_giocatori(&giocatori[0], numero_giocatori);

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





