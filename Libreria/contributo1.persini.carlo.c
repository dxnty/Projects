#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define MAXLIBRI 10 /* ovviamente è stato inserito un numero agevolativo, potrebbe essere qualsiasi valore reale */


struct libro {
    int codice; /* codice identificativo del libro */
    int numPagine; /* autoesplicativo */
    int annoPub; /* anno in cui il libro è stato pubblicato */    
    char titolo[20]; /* nome titolo */
};
typedef struct libro Libro;

struct libreria {
    char nomeLib[20]; /* nome libreria */
    Libro libro[MAXLIBRI];
    int numLibri; /* numero di libri che possiede */
};
typedef struct libreria * Libreria; /* array di strutture */

void stampaMenu(); /* semplicemente stampa il menu che consente all'utente di scegliere l'azione che desidera compiere */
void stampaLibri(Libreria); /* permette la stampa dei libri di cui la libreria dispone */
void addLibro(Libreria *); /* funzione che permette l'aggiunta di un libro alla libreria */
void removeLibro(Libreria *); /* funzione che permette la rimozione di un libro dalla libreria */
void modificaLibro(Libreria *); /* funzione che consente la modifica dei valori di un libro contenuto nella libreria */
void apriLib(); /* È ora di aprire! Buongiorno! C: */
void closeLib(); /* È ora di andare a dormire! Buonanotte C: */

void builFromFile(); /* crea il vettore partendo dai salvataggi presi dal file */

int main() {
    
    /* INT */
    int condLoop = 1;
    int condOpz = 0;

    /* CHAR */
    char condSave = ' ';
    /* CHAR * || CHAR[] */
    char nomeLib[20];
    
    while (condLoop == 1) { /* qui l'utente sceglie se caricare salvataggi precendentemente salvati su file, oppure se, non dovesse averne, sceglie il nome della libreria */
        printf("\n\tSalve! Ha dei salvataggi precedenti da file? (s/n) ->  ");
        scanf("%c" , &condSave);
        condSave = tolower(condSave);
        if ( condSave == 's' ) { /* builFromFile(); condLoop = 0;*/ }
        else if ( condSave == 'n' ) { 
            printf("\n\tD'accordo! Piacere di conoscerti!\n\t[] Inserisci il nome della libreria per favore! ->  ");
            scanf("%s" , nomeLib);
            printf("\n\t {} Fantastico nome! ~~ Procediamo!\n");
            condLoop = 0;
        } 
        else if ( condSave != 's' && condSave != 'n' ) { printf("\n\tDevi aver sbagliato a scrivere!\n"); condLoop = 1;}
    }


    condLoop = 1;
    while (condLoop == 1) {

        stampaMenu();
        scanf("%d" , &condOpz);

        switch (condOpz) {

            case 1: /* Visualizza i libri che la libreria contiene */
                stampaLibri();
                condLoop = 1;
                break;
            case 2: /* Aggiunge un libro alla libreria */
                addLibro();
                condLoop = 1;
                break;
            case 3: /* Rimuove un libro dalla libreria */
                removeLibro();
                condLoop = 1;
                break;
            case 4: /* Modifica le informazioni di un libro contenuto nella libreria */
                modificaLibro();
                condLoop = 1;
                break;
            case 5: /* Salva e poi termina il programma */
                saveOnFile();
                condLoop = 1;
                break;
            case 6: /* Termina il programma senza però prima salvare */
                printf("\n\tD'accordo! Arrivederci! C:\n");
                condLoop = 0;
                break;
            default:    
                printf("\n\tOps.. credo tu abbia sbagliato a digitare :s\n-Riprova:\n");
                condLoop = 1;
                break;

        } /* fine switch */
        
    } /* fine while di stampa menu */

} /* fine main */


void stampaMenu() {
    printf("\n\t");
}