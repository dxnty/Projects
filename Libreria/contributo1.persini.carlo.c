/* ESERCIZIO N.1 : "Libreria" 
	In questo programma si potrà gestire il catalogo di una libreria, le varie funzioni inserite ci permettono di:
	- Visualizzare i libri presenti
	- Aggiungere libri al catalogo
	- Rimuovere libri dal catalogo
	- Modificare libri già inseriti all'interno del catalogo
	- Salvare l'intero catalogo di libri all'interno di un file di salvataggio esterno
	- Caricare i dati dal file di salvataggio esterno 

	Carlo Persini , 1995178
*/

#include <stdlib.h> 
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#define MAXLIBRI 10 /* ovviamente è stato inserito un numero agevolativo, potrebbe essere qualsiasi valore reale */


struct libro {
    int codice; /* codice identificativo del libro */
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
int checkEsisteCodice(TipoLibreria , int); /* se il codice passato come parametro è già stato utilizzato allora returna 1, altrimenti 0 */


void builFromFile(TipoLibreria * , const char *); /* acquisisce i dati dal file di testo */
void saveOnFile(TipoLibreria , const char *); /* salva i dati acquisiti durante l'esecuzione dell'app all'interno del file di testo 'save.txt' */

int main() {
    
    /* TipoLibreria */
    TipoLibreria Libreria;

    /* INT */
    int condLoop = 1;
    int condOpz = 0;

    /* CHAR */
    char condSave = ' ';
	
    /* CHAR * || CHAR[] */
    const char nomeFile[10] = "save.txt";
    char nomeLib[40];
    
    while (condLoop == 1) { /* qui l'utente sceglie se caricare salvataggi precendentemente salvati su file, oppure se, non dovesse averne, sceglie il nome della libreria */
        printf("\n\tSalve! Ha dei salvataggi precedenti da file? (s/n) ->  ");
        scanf("%c" , &condSave);
        condSave = tolower(condSave); /* porta a lower case l'inserimento dell'utente in modo che char come 'S' o 'N' non creino problemi al nostro programma */
        if ( condSave == 's' ) { 
            builFromFile(&Libreria , nomeFile); 
            condLoop = 0; 
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
				printf("\n\t\t (()) ~~ Prova -> %s \n\n" , Libreria.libroVect[0].titolo );
                condLoop = 1;
                break;
            case 3: /* Rimuove un libro dalla libreria */
                removeLibro(&Libreria);
                condLoop = 1;
                break;
            case 4: /* Modifica le informazioni di un libro contenuto nella libreria */
                modificaLibro(&Libreria);
                condLoop = 1;
                break;
            case 5: /* Salva e poi termina il programma */
                saveOnFile(Libreria , nomeFile);
                condLoop = 0;
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
		printf("\n\t] Anno pubblicazione: %d\n" , Lib.libroVect[i].annoPub);
	}
	
}

int checkEsisteCodice( TipoLibreria Lib , int codeFound ) {
	
	/* se il codice è presente nel vettore allora returna 1 altrimenti 0 */
	int codeact = 0; /* assumerà il codice dell'array durante lo scorrimento del vettore */
	for ( int i = 0 ; i < Lib.numLibri ; i++ ) {
		codeact = Lib.libroVect[i].codice;
		if ( codeFound == codeact ) { return 1; }
	}
	return 0;

}

void addLibro(TipoLibreria *Lib) { /* puntatore a Lib perché passiamo Libreria per indirizzo (&) */
	int annopub = 0; /* anno di pubblicazione del libro */
	int numpagine = 0; /* numero di pagine che il libro contiene */
	int condLoop = 1; /* condizione di loop */
	int code = 0; /* codice del libro inserito dall'utente */	
	int indexArray; /* ci permette di inserire il libro esattamente all'ultimo spazio libero nell'array */
	char nomelibro[40]; /* nome/titolo del libro inserito */
	char autorelibro[40]; /* autore del libro inserito */	
	if ( (*Lib).numLibri == 0 ) { indexArray = 0; }
	else if ( (*Lib).numLibri > 0 ) { indexArray = (*Lib).numLibri; }
	else if ( (*Lib).numLibri < 0){ printf("\n\tErrore nel programma! Ci scusiamo per il disagio!\n"); exit(-1); }

	printf("\n\t[] Inserisci il nome del libro -> ");
	scanf(" %[^\n]s" , nomelibro);
	
	printf("\n\t[] Inserisci autore del libro -> ");
	scanf(" %[^\n]s" , autorelibro);

	while (condLoop == 1) {
		printf("\n\t[] Inserisci il codice del libro -> ");
		scanf("%d" , &code);
		if ( checkEsisteCodice((*Lib),code) == 0 ) { condLoop = 0; } /* se il codice non esiste */
		else { printf("\n\t ~~~ Attenzione! Hai inserito un codice che già esiste!\n~~~ "); } /* se il codice è già stato utilizzato per un altro libro */
	}

	printf("\n\t[] Inserisci l'anno di pubblicazione -> ");
	scanf("%d" , &annopub);
	if (annopub > 2022) { printf("\n\tMhh.. un libro dal futuro... intrigante!\n"); }
	else if (annopub < 1950) { printf("\n\tWow! Un vero reperto storico!\n"); }
	
	
	strcpy( (*Lib).libroVect[indexArray].titolo , nomelibro);
	strcpy( (*Lib).libroVect[indexArray].autore , autorelibro);
	(*Lib).libroVect[indexArray].codice = code;
	(*Lib).libroVect[indexArray].annoPub = annopub;

	(*Lib).numLibri += 1;
} /* fine funzione addLibro() */

void removeLibro(TipoLibreria *Lib) {
	int posremove = 0; /* codice del libro che l'utente desidera rimuovere || preso in input tramite scanf */
	int cond = 1;

	printf("\n\tStampa in corso dei libri attualmente in catalogo:	\n");
	while ( cond == 1 ) { 
		printf("\n\t [ inserisci il numero del libro che desideri rimuovere ]\n");
		stampaLibri( (*Lib) );
		printf("\n\t ->  ");
		scanf("%d" , &posremove);
		/* 0 -> il numero inserito è più piccolo del numero di libri presenti | 1 -> il numero è maggiore --> l'utente ha sbagliato ad inserire il numero */
		cond = ( posremove <= (*Lib).numLibri ) ? 0 : 1 ; 
	}
	
	for ( int i = posremove-1 ; i < ((*Lib).numLibri)-1 ; i++ ) {
		(*Lib).libroVect[i] = (*Lib).libroVect[i+1];
	}

	(*Lib).numLibri -= 1;
	printf("\n\t{} Rimozione effettuata con successo!\n");

} /* fine funzione removeLibro() */

void modificaLibro(TipoLibreria *Lib) {
	int poscond = 0; /* posizione da modificare */
	int cond = 1;

	char nomelibro[40]; /* nuovo nome libro */
	char autore[40]; /* nome del nuovo autore */
	int newcode = 0; /* nuovo codice */
	int newanno = 0; /* nuovo anno di pubblicazione */
	
	printf("\n\tStampa in corso dei libri attualmente in catalogo:	\n");
	
	while ( cond == 1 ) { 

		printf("\n\t [ inserisci il numero del libro che desideri modificare ]\n");
		stampaLibri( (*Lib) );
		printf("\n\t ->  ");
		scanf("%d" , &poscond);
		/* 0 -> il numero inserito è più piccolo del numero di libri presenti | 1 -> il numero è maggiore --> l'utente ha sbagliato ad inserire il numero */
		cond = ( poscond <= (*Lib).numLibri ) ? 0 : 1 ; 
	
	} /* fine while */

	poscond -= 1; /* se l'utente ha scelto il secondo libro, dovremo andare a modificare l'indirizzo [1], dato che i vettori partono da 0 */
	
	printf("\n\t[] Inserisci il nuovo nome -> ");
	scanf(" %s" , nomelibro);

	printf("\n\t[] Inserisci il nuovo autore -> ");
	scanf(" %s" , autore);
	
	cond = 1;
	while (cond == 1) {
		printf("\n\t[] Inserisci il codice del libro -> ");
		scanf("%d" , &newcode);
		if ( checkEsisteCodice((*Lib),newcode) == 0 ) { cond = 0; } /* se il codice non esiste */
		else { printf("\n\t ~~~ Attenzione! Hai inserito un codice che già esiste!\n~~~ "); } /* se il codice è già stato utilizzato per un altro libro */
	}

	printf("\n\t[] Inserisci il nuovo anno di pubblicazione -> ");
	scanf("%d" , &newanno);

	strcpy( (*Lib).libroVect[poscond].titolo , nomelibro);
	strcpy( (*Lib).libroVect[poscond].autore , autore);
	(*Lib).libroVect[poscond].codice = newcode;
	(*Lib).libroVect[poscond].annoPub = newanno;

	printf("\n\t{} Inserimento effettuato con successo!\n");

}

void saveOnFile(TipoLibreria Lib , const char nomeFile[10]) {
	FILE *fout = fopen( nomeFile , "w" );
	char nomeautore[40];
	char nomelibro[40];
	int code = 0 , anno = 0;

	if ( !fout ) { printf("\n\t ~~~ Errore nell'apertura del file!\n"); }
	else { 
		fprintf(fout , "%s\n" , Lib.nomeLibreria);
		for ( int i = 0 ; i < Lib.numLibri ; i++ ) {
			strcpy(nomelibro, Lib.libroVect[i].titolo);	
			strcpy(nomeautore, Lib.libroVect[i].autore);
			code = Lib.libroVect[i].codice;
			anno = Lib.libroVect[i].annoPub;

			fprintf(fout , "%s %s %d %d\n" , nomelibro , nomeautore , code , anno);
		}
	}
	fclose(fout);
}

void builFromFile(TipoLibreria *Lib , const char nomeFile[10]) {
	FILE *fin = fopen(nomeFile, "r");
	char nomeautore[40];
	char nomelibro[40];
	int code = 0 , anno = 0 , count = 1 , index = 0;
	
	if ( !fin ) { printf("\n\t ~~~ Errore nell'apertura del file!\n"); }
	else { 
		while (!feof(fin)) {
			if (count == 1) { 
				fscanf(fin , "%s\n" , (*Lib).nomeLibreria);
			}
			else{ 
				fscanf(fin , "%s %s %d %d\n" , nomelibro , nomeautore , &code , &anno);	
				
				strcpy( (*Lib).libroVect[index].titolo , nomelibro);
				strcpy( (*Lib).libroVect[index].autore , nomeautore );
				(*Lib).libroVect[index].codice = code;
				(*Lib).libroVect[index].annoPub = anno;
				(*Lib).numLibri += 1;
				index += 1;
			}
			count += 1;
		} /* fine while */
		
	} /* fine else -> file aperto con successo */	
	fclose(fin);
}

