#include <stdlib.h> 
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define MAXLIBRI 10 /* ovviamente è stato inserito un numero agevolativo, potrebbe essere qualsiasi valore reale */


struct libro {
    int codice; /* codice identificativo del libro */
    int numPagine; /* autoesplicativo */
    int annoPub; /* anno in cui il libro è stato pubblicato */    
    char titolo[20]; /* nome del libro */
	char autore[40]; /* autoesplicativo :: nome - e cognome, se lo si vuole- dell'autore */
};
typedef struct libro Libro;

struct libreria {
    char nomeLibreria[20]; /* nome libreria */
    Libro libroVect[MAXLIBRI];
    int numLibri; /* numero di libri che possiede || numero massimo: 10 */
};
typedef struct libreria TipoLibreria; /* array di strutture || Tabella dei libri */

void stampaMenu(); /* semplicemente stampa il menu che consente all'utente di scegliere l'azione che desidera compiere */
void stampaLibri(TipoLibreria); /* permette la stampa dei libri di cui la libreria dispone */
void addLibro(TipoLibreria *); /* funzione che permette l'aggiunta di un libro alla libreria */
void removeLibro(TipoLibreria *); /* funzione che permette la rimozione di un libro dalla libreria */
void modificaLibro(TipoLibreria *); /* funzione che consente la modifica dei valori di un libro contenuto nella libreria */
void apriLib(); /* È ora di aprire! Buongiorno! C: */
void closeLib(); /* È ora di andare a dormire! Buonanotte C: */
int checkEsisteCodice(int); /* se il codice passato come parametro è già stato utilizzato allora returna 1, altrimenti 0 */


void builFromFile(); /* acquisisce i dati dal file di testo */
void saveOnFile(); /* salva i dati acquisiti durante l'esecuzione dell'app all'interno del file di testo 'save.txt' */

int main() {
    
    /* TipoLibreria */
    TipoLibreria Libreria;

    /* INT */
    int condLoop = 1;
    int condOpz = 0;

    /* CHAR */
    char condSave = ' ';
    /* CHAR * || CHAR[] */
    const char nomeFile[] = "save.txt";
    char nomeLib[20];
    
    while (condLoop == 1) { /* qui l'utente sceglie se caricare salvataggi precendentemente salvati su file, oppure se, non dovesse averne, sceglie il nome della libreria */
        printf("\n\tSalve! Ha dei salvataggi precedenti da file? (s/n) ->  ");
        scanf("%c" , &condSave);
        condSave = tolower(condSave); /* porta a lower case l'inserimento dell'utente in modo che char come 'S' o 'N' non creino problemi al nostro programma */
        if ( condSave == 's' ) { 
            /* builFromFile(); 
            condLoop = 0;*/ 
        }
        else if ( condSave == 'n' ) {  /* se l'utente non ha salvataggi precedenti */
            printf("\n\tD'accordo! Piacere di conoscerti!\n\t[] Inserisci il nome della libreria per favore! ->  ");
            scanf("%s" , nomeLib);
            strcpy(Libreria.nomeLibreria , nomeLib);
            printf("\n\t {} Fantastico nome! ~~ Procediamo!\n\n");
            condLoop = 0;
        } 
        else if ( condSave != 's' && condSave != 'n' ) { printf("\n\tDevi aver sbagliato a scrivere!\n"); condLoop = 1;} /* se l'utente non ha inserito nè 's' e nè 'n' */
    }


    condLoop = 1;
    while (condLoop == 1) {

        stampaMenu();
        scanf("%d" , &condOpz);

        switch (condOpz) {

            case 1: /* Visualizza i libri che la libreria contiene */
                stampaLibri(Libreria);
                condLoop = 1;
                break;
            case 2: /* Aggiunge un libro alla libreria */
                addLibro(&Libreria);
                condLoop = 1;
                break;
            case 3: /* Rimuove un libro dalla libreria */
                //removeLibro(&Libreria);
                condLoop = 1;
                break;
            case 4: /* Modifica le informazioni di un libro contenuto nella libreria */
                //modificaLibro(&Libreria);
                condLoop = 1;
                break;
            case 5: /* Salva e poi termina il programma */
                //saveOnFile();
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
    printf("\n\n\t 1- Visualizza i libri presenti in catalogo\n");
    printf("\n\t 2- Aggiungi un libro al catalogo\n");
    printf("\n\t 3- Rimuovi un libro dal catalogo\n");
    printf("\n\t 4- Modifica le informazioni di un libro\n");
    printf("\n\t 5- Salve e chiudi l'applicazione\n");
    printf("\n\t 6- Chiudi l'applicazione senza salvare\n\n");
    printf("\t-> ");
}

void stampaLibri(TipoLibreria Lib) {
	
	int numlibri = Lib.numLibri; /* in questo modo possiamo rendere più leggibile il codice, senza dover ogni volta riscrivere Lib.numLibri  */
	int count = 1; /* ci permette di numerare durante il for la stampa dei vari libri, senza dover scrivere i++ */

	if (numlibri <= 0) {
		printf("\n\t ~~~ Non c'è alcun libro da stampare! ~~~\n\n");
		return ;
	}
	printf("\n\t ~~~ Stampa dei libri presenti in corso ...\n\n");
	 
	for (int i = 0 ; i < numlibri ; i++ , count++) /* numero pagine e anno pubblicato */ 
	{
		
		printf("\n\t %d] Nome libro: %s" , count ,  Lib.libroVect[i].titolo);
		printf("\n\t] Autore libro: %s" , Lib.libroVect[i].autore);
		printf("\n\t] Codice libro: %d" , Lib.libroVect[i].codice);
		printf("\n\t] Anno pubblicazione: %d" , Lib.libroVect[i].annoPub);
		printf("\n\t] Numero pagine: %d\n" , Lib.libroVect[i].numPagine);
	}
	
}

int checkEsisteCodice( int code ) {
	
	/* se il codice è presente nel vettore allora returna 1 altrimenti 0 */
	return 0;

}

void addLibro(TipoLibreria *Lib) { /* puntatore a Lib perché passiamo Libreria per indirizzo (&) */
	int annopub = 0; /* anno di pubblicazione del libro */
	int numpagine = 0; /* numero di pagine che il libro contiene */
	int condLoop = 1; /* condizione di loop */
	int code = 0; /* codice del libro inserito dall'utente */	
	int indexArray; /* ci permette di inserire il libro esattamente all'ultimo spazio libero nell'array */
	char nomelibro[20]; /* nome/titolo del libro inserito */
	char autorelibro[40]; /* autore del libro inserito */	
	if ( (*Lib).numLibri == 0 ) { indexArray = 0; }
	else if ( (*Lib).numLibri > 0 ) { indexArray = (*Lib).numLibri; }
	else if ( (*Lib).numLibri < 0){ printf("\n\tErrore nel programma! Ci scusiamo per il disagio!\n"); exit(-1); }

	printf("\n\t[] Inserisci il nome del libro -> ");
	scanf("%s" , nomelibro);
	
	printf("\n\t[] Inserisci autore del libro -> ");
	scanf("%s" , autorelibro);

	while (condLoop == 1) {
		printf("\n\t[] Inserisci il codice del libro -> ");
		scanf("%d" , &code);
		if ( checkEsisteCodice(code) == 0 ) { condLoop = 0; } /* se il codice non esiste */
		else { printf("\n\t ~~~ Attenzione! Hai inserito un codice che già esiste!\n~~~ "); } /* se il codice è già stato utilizzato per un altro libro */
	}

	printf("\n\t[] Inserisci l'anno di pubblicazione -> ");
	scanf("%d" , &annopub);
	if (annopub > 2022) { printf("\n\tMhh.. un libro dal futuro... intrigante!\n"); }
	else if (annopub < 1950) { printf("\n\tWow! Un vero reperto storico!\n"); }
	
	printf("\n\t[] Inserisci il numero di pagine -> ");
	scanf("%d" , &numpagine);

	
	strcpy( (*Lib).libroVect[indexArray].titolo , nomelibro);
	strcpy( (*Lib).libroVect[indexArray].autore , autorelibro);
	(*Lib).libroVect[indexArray].codice = code;
	(*Lib).libroVect[indexArray].annoPub = annopub;
	(*Lib).libroVect[indexArray].numPagine = numpagine; 

	(*Lib).numLibri += 1;
}











