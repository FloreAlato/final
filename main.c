#include "indovina_il_numero.h"
#include "additional.h"


Elenco *scrematura(int, Elenco *);


//TESTING
int i, j, k, l, counter;

int numero_giocatori, numero_giocatori_veri;
Elenco *giocatori = NULL;
ProfiloGiocatore *giocatori_veri;
FILE *file = NULL;

bool nuovo, esistente, scelto, game = false;
int scelta, prosegui;
char nome[32];
char opzioni[2][10] = {"carica", "inserisci"};
char scelte[4][10] = {"continua", "salva", "inizia", "esci"};
char **files = NULL;
int numero_files;
int numero_profili;

int id, segnaposto;
Elenco *prov = NULL;

Elenco **groups = NULL;
Elenco *new = NULL;
bool *pla = NULL;
int target, group_size, size, winner;



int main() {





    // TESTING

    /*srand(time(NULL));

    // code
    ProfiloGiocatore pop[2] = {

            {13,
             "Luigi Il Bello",
             0,
             0,
             0,
             0,
             0},

             {
                15,
                "Davide Cartello",
                0,
                0,
                0,
                0,
                0
            }
    };

    Elenco gam[4] = {
            {
                13,
                true,
                &pop[0]
            },
            {
                14,
                true,
                NULL
            },
            {
                15,
                true,
                &pop[1]
            },
            {
                16,
                true,
                NULL
            }
    };

    return 0;*/









    //restore();
    //add_file("Dai_Riproviamo");
    srand(time(NULL));






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
                printf("\nInserisci il nome del file nel quale vorresti salvare i profili");
                printf("\n(ATTENZIONE! Se inserirai il nome di un file esistente, questo verrà sovrascritto!)");

                printf("\n\n[Tu]: ");
                scanf(" %s", nome);

                // salva la partita in un file senza gioco
                save(&numero_profili, giocatori_veri, false, nome);
                add_file(nome);
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

        // rifare

        file = fopen_secure(make_path("savegame_files", ".bin"), "rb");

        // il programma legge quanti file sono disponibili
        // e usa questo dato per allocare la matrice con i nomi da mostrare all'utente
        // se l'apertura del file dovesse fallire, il programma si arresterebbe
        // (darò per scontato anche questo passaggio)

        fread(&numero_files, sizeof(int), 1, file);

        // rifare

        files = list_files(file, numero_files);

        fclose(file);



        // i nomi letti vengono poi stampati perché l'utente possa scegliere

        for(k = 0; k < numero_files; k++) {
            printf("\n[%d] -> %s", k, files[k]);
        }

        // la scelta è salvata nell'omonima variabile intera
        // per fare ciò, si usa la funzione apposita get_int()
        // get_int() -> main.h

        scelta = get_int("\n\n[Tu]: ", 0, numero_files - 1);

        // rifare

        file = fopen_secure(make_path(files[scelta], ".bin"), "rb");

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

        // se il file contiene una partita già in corso, le seguenti operazioni vengono svolte:

        if(game == true) {

            // si leggono dal file il numero di giocatori totali e utente partecipanti alla partita

            fread(&numero_giocatori, sizeof(int), 1, file);
            fread(&numero_giocatori_veri, sizeof(int), 1, file);

            // l'array dei giocatori totali viene riempita grazie all'apposita funzione componi_elenco()
            // in questo modo, i campi vivo e p sono inizializzati a true e NULL
            // questo ci semplificherà le cose più tardi
            // componi_elenco() -> main.h

            giocatori = componi_elenco(numero_giocatori);

            // una volta fatto ciò, vengono abbinati i posti nella lista totale dei giocatori ai giusti profili
            // questo viene fatto recuperando l'indice del profilo giocatore indicato

            for(j = 0; j < numero_giocatori_veri; j++) {

                fread(&segnaposto, sizeof(int), 1, file);
                giocatori[giocatori_veri[segnaposto].index].p = &giocatori_veri[segnaposto];
            }

            // come ultimo passaggio, il programma recupera dal file l'array dello "stato vitale" dei giocatori
            // e lo salva nell'elenco correggendo il valore del campo vivo
            // basta correggere il valore per i giocatori morti, in quanto sono tutti vivi di default

            for(j = 0; j < numero_giocatori; j++) {

                fread(&segnaposto, sizeof(int), 1, file);
                if(segnaposto == 0) {
                    giocatori[j].vivo = false;
                }
            }
        }

        fclose(file);

        // l'array con i nomi dei files disponibili è obsoleta, e va liberata

        free(files);
    }






    // INIZIO PARTITA



    // commentare

    if(game == false) {

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
    }








    // stampa la lista dei giocatori
    stampa_lista_giocatori(&giocatori[0], numero_giocatori);

    // stampa i profili giocatore

    printf("\n\n");
    for(i = 0; i < numero_profili; i++) {

        printf("\n[%d] -> %s", giocatori_veri[i].index, giocatori_veri[i].nome);
    }





    Elenco *nuov = scrematura(numero_giocatori, &giocatori[0]);



    printf("\n\n");
    for(k = 0; k < target; k++) {
        print_player(nuov[k]);
        printf("\n");
    }




    free(giocatori);
    free(giocatori_veri);

    return 0;
}










Elenco *scrematura(int totale, Elenco *participants) {

    // nuovo elenco
    new = (Elenco *) calloc(totale, sizeof(Elenco));
    if(new == NULL) {
        printf("ERRORE! Allocazione fallita!");
        exit(-1);
    }
    for(k = 0; k < totale; k++) {
        new[k] = participants[k];
    }

    // prendi l'elenco in entrata e calcola le nuove dimensioni
    // dividi in gruppetti casuali
    // calcola i vincitori con i giochi (ricorda frontman)
    // riunisci i rimanenti in un gruppo solo
    // ritorna questo gruppo

    // trasforma il numero
    i = 0;
    while(potenza(2, i) < totale) {
        i++;
    }

    target = potenza(2, i - 2);
    printf("\n\n\nTroppi! Facciamo %d?", target);

    // dividi in gruppetti
    group_size = totale / target;

    groups = (Elenco **) calloc(target, sizeof(Elenco *));
    if(groups == NULL) {
        printf("\n\nERRORE! Allocazione fallita!");
        exit(-1);
    }
    for(i = 0; i < target; i++) {
        groups[i] = (Elenco *) calloc(group_size + 1, sizeof(Elenco));
        if(groups[i] == NULL) {
            printf("\n\nERRORE! Allocazione fallita!");
            exit(-1);
        }
    }

    // riempi
    // target -> numero di gruppi, nuovo numero di giocatori totali
    // group_size -> numero di giocatori per ogni gruppo
    // groups[target][group_size + 1]

    // riempi i primi posti di ogni gruppetto
    // riempi i secondi posti di ogni qruppetto
    // continua fino alla fine degli elementi

    // randomizza (fatto, aggiungi commenti)

    pla = (bool *) calloc(target, sizeof(bool));
    if(pla == NULL) {
        printf("\n\nERRORE! Allocazione fallita!\n\n");
        exit(-1);
    }
    for(i = 0; i < target; i++) {
        pla[i] = false;
    }


    counter = totale - 1;
    for(i = 0; i <= group_size; i++) {
        for(j = 0; j < target; j++, counter--) {
            if(counter >= 0) {
                segnaposto = rand_int(0, counter);
                groups[j][i] = new[segnaposto];

                // salva i gruppi che contengono giocatori
                if(is_player(groups[j][i])) {
                    pla[j] = true;
                }

                new[segnaposto] = new[counter];
            } else {
                groups[j][i].id = -1;
            }
        }
    }



    for(i = 0; i < target; i++) {
        printf("\n%do gruppo: ", i + 1);
        for(j = 0; j <= group_size; j++) {
            print_player(groups[i][j]);
            printf("    ");
        }
    }




    // stampa un elenco ordinato
    // migliorare per i nomi dei giocatori (fatto!!)

    printf("\n\n\n");

    // stampa i gruppetti in modo ordinato

    stampa_gruppetti(&groups[0], target, group_size, 5);
    getchar();
    getchar();


    printf("\n\n");




    // gioca a indovina il numero e componi l'elenco da ritornare

    // alloca elenco
    new = (Elenco *) realloc(new, sizeof(Elenco) * target);
    if(new == NULL) {
        printf("ERRORE! Rillocazione fallita!");
        exit(-1);
    }


    // controlla la fine
    // controlla se ci sono giocatori
    i = 0, segnaposto = 0;
    while(i < target) {

        // controlla lunghezza
        if(groups[i][group_size].id == -1) {
            size = group_size - 1;
        } else {
            size = group_size;
        }


        if(pla[i] == false) {
            new[i] = groups[i][rand_int(0, size)];
        }

        // correggere gli errori

        if(pla[i] == true || i == target - 1) {

            if(i > 0 && segnaposto != i) {
                printf("\nI seguenti gruppi hanno ottenuto i seguenti risultati:\n");
            }

            // stampa i precedenti
            for(j = segnaposto; j < i; j++) {
                printf("%do gruppo: ", j);
                print_player(new[j]);
                printf("\n");
            }
            getchar();

            if(pla[i] == true) {

                printf("\n\nSI GIOCAAA");

                printf("\n\n");

                winner = indovina_il_numero(groups[i], size);

                for(k = 0; k <= size; k++) {
                    if(is_player(groups[i][k]) && strcmp(groups[i][k].p->nome, "Riccardo Scateni") == 0) {
                        winner = k;
                        break;
                    }
                }

                new[i] = groups[i][winner];
                getchar();

                segnaposto = i + 1;

            } else {
                printf("%do gruppo: ", i);
                print_player(new[i]);
            }

            printf("\n");
        }

        i++;
    }



    free(groups);

    return new;
}