/* DESCRIZIONE ESERCIZIO ↓ 
   # Questo programma ci consente di simulare la gestione di un hotel (privo di sistema prenotativo). Presenta la possibilità di inserire e gestire variabili come:
        1] Nome struttura ,
        2] Numero di piani di cui la struttura dispone ,
        3] Numero delle stanze occupate ,
        4] Numero di stanze ancora disponibili ,
        5] Codice della stanza ,
        X] etc....
    È disponibile inoltre la possibilità di salvare e caricare i propri dati in modo da poter riprendere il proprio lavoro da dove lo si aveva lasciato.

    ~Carlo Persini , 1995178
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ~ DICHIARAZIONI STRUTTURE ~ */

struct infoStanza {
   int codiceStanza; /* codice identificativo della stanza [variabile primaria] */
   int pianoStanza; /* indica il piano in cui si trova la stanza */
   int statoStanza; /* indica se la stanza, nel momento della visualizzazione, è occupata o meno  ::  1 -> occupata | 0 -> libera */
};
typedef struct infoStanza TipoElem; 

struct Hotel {
   TipoElem infoStanzaSingola; /* conterrà le informazioni della stanza (vedi struct infoStanza) */
   struct Hotel *next; /* puntatore ricorsivo || conterrà l'indirizzo (se presente) del nodo successivo */
};
typedef struct Hotel TipoNodo;
typedef TipoNodo *TipoLista;

/* DICHIARAZIONE FUNZIONI */

void initLista(TipoLista *); /* inizializzazione lista a NULL*/
void stampaMenu(); /* stampa il menu' con le opzioni fra cui scegliere */
void addStanzaToHotel(TipoLista * , int * , int); /* permette l'aggiunta di stanze alla struttura */
void addOccupazione(TipoLista *); /* cambia lo stato della stanza da 0 ad 1, cioè da libera ad occupata */
void removeOccupazione(TipoLista *); /* opposto della funzione addOccupazione() : modifica lo stato della stanza per impostarla da occupata (1) a libera (0) */
void stampaStanze(TipoLista , int); /* stampa le stanze presenti in struttura con la possibilità d'applicare dei filtri (come ad esempio: stampare solo stanze libere, solo occupate etc) */
void modStanza(TipoLista * , int); /* permette al cliente di modificare le informazioni riguardo le stanze presenti in struttura */
void removeStanza(TipoLista *); /* consente l'eliminazione di stanze dalla struttura (stanza non più disponibile per lavori o qualsiasi altra evenienza) */
void buildFromFile(TipoLista * , const char * , char * , int *); /* carica le informazioni dal file e le inserisce nella lista || parametri:: (&lista , nomefile , nomeHotel , numPianiHotel)  */
int checkFile(const char *); /* verifica l'esistenza del file in modo da evitare che il programma si chiuda successivamente al tentativo d'apertura */
 /* void readSettingsFromFile(FILE * , char * , int *);  legge dal file informazioni come il nome e di quanti piani dispone l'hotel [RIMOSSA]*/ 
 /* void readFromFile(FILE * , TipoElem *); legge dal file le informazioni riguardo le stanze presenti sul file [RIMOSSA] */
void addElemFromFileToLista(TipoLista * , TipoElem ); /* prende gli elementi dal file e li carica sulla lista (tramite inserimento in coda) */
/* 
   ~~~ riguardo la funzione [ addElemFromFileToLista() ] :: ho deciso di utilizzare l'inserimento in coda in quanto ritengo renda l'applicazione più similare ad un software lavorativo reale;
   Difficilemente  infatti ho visto applicazioni in cui l'ultimo elemento inserito diviene il primo ad essere stampato, ci sono sicuramente degli scenari in cui questa soluzione risulta comoda e 
   più immediata, ma ho reputato che questo non fosse uno di quelli. ~~~

*/
void saveOnFile(TipoLista , const char * , char * , int); /* salva i dati presenti sulla lista all'interno del file */
int checkEsisteCodice(TipoLista , int); /* controlla l'effettiva esistenza di una camera avendo ricevuto il codice di quest'ultima */


/* ~~~ FUNZIONE MAIN ~~~ */

int main() {
 
   /* const */
   const char nomeFile[9] = "save.txt"; /* auto esplicativo */

   /* int */
   int condLoop = 1, /* variabile di ciclo */
      condScelta = 0, /* variabile di scelta per lo switch */
      numStanzeTot = 0, /* numero totale di cui la struttura è dotata */
      condRisp = 0, /* [condizioneRisposta] contiene alcuni valori utili a definire le "intenzioni" del cliente durante l'utilizzo dell'applicazione */
      numStanzeOccupate = 0, /* numero delle stanze attualmente occupate */
      numPianiHotel = 0; /* numero di piani di cui la struttura è effettivamente dotata */

   /* char *var || string || char */
   char nomeHotel[20];
   char condSave = ' '; /* conterrà la 'risposta' alla domanda "Hai dei salvataggi precedenti?"  */
   

   /* TipoLista */
   TipoLista lista;
   initLista(&lista); /* inizializzazione della lista a NULL */

   printf("\n\tSalve! Ha dei salvataggi precedenti [s/n]? ->  ");
   scanf(" %c" , &condSave);
   condSave = tolower(condSave); /* in questo modo se l'utente scriverà 'S' anziché 's' il programma non incapperà in degli errori || porta il parametro a lowercase  */
   if ( condSave == 's' && checkFile(nomeFile) == 0) {
      buildFromFile(&lista, nomeFile , nomeHotel , &numPianiHotel);
   }
   else{

      printf("\n\tInserisca nome struttura -> ");
      scanf(" %s" , nomeHotel );

      printf("\n\tDi quanti piani dispone la struttura? -> ");
      scanf("%d" , &numPianiHotel);
      if (numPianiHotel <= 0) { printf("\n\tMi spiace ma non è possibile.\n"); exit(-1); }
   
   }
   printf("\n\tPerfetto %s! Procediamo ... " , nomeHotel);

   do {

      stampaMenu(); /* auto esplicativo */
      scanf("%d" , &condScelta);

      switch (condScelta) 
      {
         case 1: /* aggiorna lo stato della stanza [ libera -> occupata e viceversa ] */
            printf("\n\t1] Qualcuno desidera occupare una stanza.\n\t2] Qualcuno desidera lasciare la sua stanza.\n\t-> ");
            scanf("%1d" , &condRisp);
            if (condRisp == 1) {
               addOccupazione(&lista); 
            }
            else if (condRisp == 2) {
               removeOccupazione(&lista);
            }
            else { /* se viene inserito un valore diverso da 1 o 2 */
               printf("\n\tScusami, non ho capito!\n");
            }
            condLoop = 1;
            break;

         case 2: /* stampa le stanze della struttura */
            condRisp = 0;
            printf("\n\tDesideri visualizzare tutte le stanze, solo quelle occupate o solo quelle libere [0 , 1 , 2]? -> ");
            scanf("%d" , &condRisp);
            stampaStanze(lista , condRisp);
            condLoop = 1;
            break;

         case 3: /* modifica le informazioni della stanza scelta dal cliente */
            modStanza(&lista , numPianiHotel);
            condLoop = 1;
            break;
         
         case 4: /* aggiungi stanza alla struttura */
            addStanzaToHotel(&lista , &numStanzeTot , numPianiHotel);
            condLoop = 1;
            break;
         
         case 5: /* rimuovi stanza dalla struttura */
            removeStanza(&lista);
            condLoop = 1;
            break;

         case 6: /* salva su file e chiudi app */
            saveOnFile(lista , nomeFile , nomeHotel , numPianiHotel);
            condLoop = 0;
            break;
            
         case 7: /* chiudi app senza salvare */
            condLoop = 0;
            break;
            
         default:
            printf("\n\tDevi aver sbagliato a scrivere! Scegli fra le opzioni presenti per favore!\n");
            condLoop = 1;
            break;
      } /* fine switch */

   }while(condLoop == 1);

} /* ~~~ FINE FUNZIONE MAIN ~~~ */


/* ~~ CODICE FUNZIONI ↓ ~~ */
void initLista(TipoLista *lista)
{
   *lista = NULL;
}


void stampaMenu() 
{
   printf("\n\n\t 1- Aggiorna stato stanza\n");
   printf("\n\t 2- Visualizza stanze\n");
   printf("\n\t 3- Modifica informazioni stanza\n");
   printf("\n\t 4- Aggiungi stanza alla tua struttura\n");
   printf("\n\t 5- Rimuovi stanza dalla tua struttura\n");
   printf("\n\t 6- Salva e chiudi\n");
   printf("\n\t 7- Chiudi senza salvare\n\n");
   printf("\t-> ");
}

int checkEsisteCodice(TipoLista lista , int codice) 
{
   int bool = 0;
   TipoNodo *paux = NULL;
   paux = lista;

   while (paux != NULL) {
      if (paux->infoStanzaSingola.codiceStanza == codice ) {
         bool = 1; /* 1 se è stato trovato */
         return bool;
      }
      else {
         paux = paux->next; /* se non è stato trovato scorre al prossimo nodo */
      }
   }

   return bool; /* 0 se non è stato trovato */
}

void addStanzaToHotel(TipoLista *lista , int *stanze , int numPiani )
{
   int statostanza = 0; /* 0 -> stanza libera */
   int codstanza = 0; /* codice della stanza da aggiungere */
   int pianostanza = 0; /* il piano in cui si trova la stanza */
   int condLoop = 1; /* variabile di ciclo */


   TipoNodo *ultimo;
   TipoNodo *newnode = NULL;
   newnode = malloc(sizeof(TipoNodo));
   if (newnode == NULL) { printf("\n\tQualcosa è andato storto!\n"); exit(-1); }

   while (condLoop == 1) {
      printf("\n\tInserisci codice nuova stanza: ");
      scanf("%d" , &codstanza);

      if (checkEsisteCodice(*lista , codstanza) == 1) {  /* se il codice stanza esista già */
         printf("\n\tMi spiace ma questo codice esiste gia'! Usane un altro cortesemente ... \n");
         condLoop = 1;
      }
      else { condLoop = 0; }
   }

   condLoop = 1;
   while (condLoop == 1) { 
      printf("\n\tA che piano si trova questa stanza? (Il piano terra vale come 1 ) -> ");
      scanf("%d" , &pianostanza);
      if (pianostanza <= 0 || pianostanza > numPiani) { printf("\n\tMi spiace ma non è possibile! Riprova cortesemente\n"); condLoop = 1; }
      else { condLoop = 0; }
   }

   /* inserimento dei dati all'interno del nuovo nodo */
   newnode->infoStanzaSingola.codiceStanza = codstanza;
   newnode->infoStanzaSingola.pianoStanza = pianostanza;
   newnode->infoStanzaSingola.statoStanza = 0;
   newnode->next = NULL;

   if ( *lista == NULL ) { /* se la lista non ha elementi il nuovo nodo viene aggiunto come primo elemento */
      *lista = newnode;
   }
   else { /* se, invece, all'interno della lista son presente >= 1 elementi il nuovo nodo viene aggiunto al termine della lista (inserimento in coda) */
      ultimo = *lista;
      while (ultimo->next != NULL) { ultimo = ultimo->next; } /* scorre la lista sino ad arrivare all'ultimo elemento */
      ultimo->next = newnode;
   }

   *stanze += 1;

}

void addOccupazione(TipoLista *lista)
{
   int codStanza = 0 , condLoop = 1;

   stampaStanze(*lista , 2); /* stampa tutte le stanze libere grazie all'argomento '2' */
   printf("\n\t []Inserisci codice stanza -> "); /* il codice della stanza che sta per essere occupata */
   scanf("%d" , &codStanza);

   if (checkEsisteCodice( *lista , codStanza ) == 0 ) { /* se non esiste alcuna stanza con il codice dal cliente inserito */
      printf("\n\tMi spiace ma non risulta alcuna stanza con questo codice!\n");
   }
   else 
   {
      /* se il codice inserito effettivamente esiste e corrisponde ad una camera */
      while ( (*lista) != NULL && condLoop == 1) {
         /* se il codice dato corrisponde al nodo puntato allora cambia lo stato della stanza da 0 ad 1 */
         if ( (*lista)->infoStanzaSingola.codiceStanza == codStanza) { (*lista)->infoStanzaSingola.statoStanza = 1; condLoop = 0;}
         /* altrimenti il puntatore passa al successivo */
         else { (*lista) = (*lista)->next; }
      }
   }
}

void removeOccupazione(TipoLista *lista)
{
   int codStanza = 0 , condLoop = 1;

   stampaStanze(*lista , 1); /* stampa tutte le stanze occupate grazie all'argomento '1' */
   printf("\n\t []Inserisci codice stanza -> ");
   scanf("%d" , &codStanza);

   if (checkEsisteCodice( *lista , codStanza ) == 0 ) { /* se non esiste alcuna stanza con il codice dal cliente inserito */
      printf("\n\tMi spiace ma non risulta alcuna stanza con questo codice!\n");
   }
   else 
   {
      /* se il codice inserito effettivamente esiste e corrisponde ad una camera */
      while ( (*lista) != NULL && condLoop == 1) {
         /* se il codice dato corrisponde al nodo puntato allora cambia lo stato della stanza da 1 ad 0 */
         if ( (*lista)->infoStanzaSingola.codiceStanza == codStanza) { (*lista)->infoStanzaSingola.statoStanza = 0; condLoop = 0;}
         /* altrimenti il puntatore passa al successivo */
         else { (*lista) = (*lista)->next; }
      }
   }
}


void stampaStanze(TipoLista lista , int condStampa)
{
   TipoNodo *newnode = lista;
   int i = 1 , codStanza = 0;

   if ( !lista ) { printf("\n\tNon ci sono stanze da mostrare!");  return ;}

   if (condStampa == 0) {  /* stampa TUTTE le stanze */
      while (newnode != NULL) {
         /* stampa in modo ordinato le stanze secondo il filtro applicato */
         codStanza = newnode->infoStanzaSingola.codiceStanza;
         printf("\n\t%d] Stanza [ %d ]" , i , codStanza);     
         i += 1;
         newnode = newnode->next;
      }
   }
   else if (condStampa == 1) { /* stampa SOLO le stanze occupate */
      while (newnode != NULL) {
         /* stampa in modo ordinato le stanze secondo il filtro applicato */
         codStanza = newnode->infoStanzaSingola.codiceStanza;
         if (newnode->infoStanzaSingola.statoStanza == 1) { printf("\n\t%d] Stanza [ %d ]" , i , codStanza); }
         i += 1;
         newnode = newnode->next;
      }
   }
   else if (condStampa == 2) { /* stampa SOLO le stanze libere */
      while (newnode != NULL) {
         /* stampa in modo ordinato le stanze secondo il filtro applicato*/
         codStanza = newnode->infoStanzaSingola.codiceStanza;
         if (newnode->infoStanzaSingola.statoStanza == 0) { printf("\n\t%d] Stanza [ %d ]" , i , codStanza); }      
         i += 1;
         newnode = newnode->next;
      }
   }
} 

void removeStanza(TipoLista *lista) {

   TipoNodo *prec; /* nodo precedente */
   TipoNodo *corr; /* nodo corrente */

   int coderemove = 0; /* codice della stanza che l'utente vuole eliminare */
   int condLoop = 1; /* variabile utile per uscire dal ciclo while */
   int foundCond = 0; /* condizione che ci indicherà se la stanza è stata trovata o meno */

   if (*lista == NULL) { /* se la lista risulta vuota */
      printf("\n\t ~~~ Non ci sono stanze da rimuovere! ~~~");
   }
   else if (*lista != NULL) { /* se la lista contiene elementi */

      printf("\n\t[] Stampa in corso delle stanze in questo momento libere: ");
      stampaStanze((*lista) , 2); /* il '2' indica che stamperemo solo le stanze libere */

      while (condLoop == 1) {
         printf("\n\t[] Inserisci codice della stanza che desideri rimuovere: ");
         scanf("%d" , &coderemove);   

         if (checkEsisteCodice(*lista, coderemove) == 0) { /* se viene inserito un codice che in realtà non esiste */
            printf("\n\tIl codice da te inserito non esiste! Controlla bene!\n");
            condLoop = 1;
         }
         else  /* se il codice inserito esiste */
            condLoop = 0;
      }
      

      if ( (*lista)->infoStanzaSingola.codiceStanza == coderemove ) {
         /* se il codice corrisponde al primo nodo in lista evitiamo di scorrere tutta la lista "inutilmente"  */
         prec = *lista;
         corr = (*lista)->next;
         free(prec); /* "liberazione" della zona di memoria occupata */
         *lista = corr;
      }
      else { /* se il codice non corrisponde a quello del primo nodo in lista */
         prec = *lista; /* prec punta al primo elemento */
         corr = (*lista)->next; /* corr punta al secondo */
         foundCond = 0;

         while( corr != NULL && foundCond == 0) { /* finchè son presenti elementi nella lista E finchè foundCond equivale a 0 */
            
            if ( coderemove == corr->infoStanzaSingola.codiceStanza ) { /* se il codice viene trovato */
               prec->next = corr->next; /* il nodo che contiene il codice da eliminare viene "scollegato" dal resto della lista */
               free(corr); /* l'allocazione di memoria occupata da corr viene cancellata in modo che possa essere riutilizzata */
               foundCond = 1; /* condizione per uscire dal ciclo */
            }
            else { /* se il codice non corrisponde a quello contenuto nel nodo a cui corr punta */
               /* vengono mandati al nodo successivo entrambi i puntatori */
               prec = prec->next;  
               corr = prec->next;
            }

         } /* fine while */
      
      } /* fine else */

   } /* fine else if (se la lista contiene elementi) */

}


void modStanza(TipoLista *lista , int numPiani)
{
   int mod_stanza = 0; /* codice della stanza da modificare */
   int foundCond = 0 , condLoop = 1; /* variabile di ciclo */
   int newcode = 0 , newpiano = 0;

   TipoNodo *prec = NULL;
   TipoNodo *corr = NULL;

   if (*lista == NULL) { /* se la lista è vuota */
      printf("\n\t ~~~ Non c'è alcuna stanza da modificare! ~~~ ");
   }
   else if ( *lista != NULL ) { /* se nella lista son presenti dei nodi || se esistono delle stanze */
      
      while ( condLoop == 1 ) {
         printf("\n\tInserisci il codice della stanza che desideri modificare:");
         stampaStanze(*lista , 0);
         printf("\n\t -> ");
         scanf("%d" , &mod_stanza);
         if ( checkEsisteCodice(*lista , mod_stanza) == 0 ) { printf("\n\t ~~~ Non esiste alcuna stanza registrata con questo codice\n"); condLoop = 1; }
         else { condLoop = 0; }
      }

      if ( (*lista)->infoStanzaSingola.codiceStanza == mod_stanza ) { /* se la stanza da modificare è il primo elemento della lista */
         /* il ciclo while viene utilizzato per assicurarci che il nuovo codice non sia già presente assegnato ad un'altra stanza */
         condLoop = 1;
         while ( condLoop == 1 ) {
            printf("\n\tInserisci il nuovo codice: ");
            scanf("%d" , &newcode);
            if ( checkEsisteCodice(*lista , newcode) == 1) { printf("\n\tQuesto codice esiste già, inseriscine un altro per favore"); }
            else { condLoop = 0; }
         }
         condLoop = 1;
         while (condLoop == 1) {
            printf("\n\tInserisci il nuovo piano: ");
            scanf("%d" , &newpiano);
            if ( newpiano > numPiani ) { printf("\n\t[] La tua struttura dispone di %d piano/i ... inserisci un dato corretto per favore" , numPiani); condLoop = 1; }
            else { condLoop = 0; }
         }

         (*lista)->infoStanzaSingola.codiceStanza = newcode;
         (*lista)->infoStanzaSingola.pianoStanza = newpiano;

      }else { /* se la stanza da modificare non è il primo nodo presente nella lista */

         prec = *lista;
         corr = (*lista)->next;
         foundCond = 0;

         while ( corr != NULL && foundCond == 1 ) { /* scorre fino all'ultimo nodo */

            if ( mod_stanza == corr->infoStanzaSingola.codiceStanza ) {
               
               condLoop = 0;
               while ( condLoop == 1 ) {
                  printf("\n\tInserisci il nuovo codice: ");
                  scanf("%d" , &newcode);
                  if ( checkEsisteCodice(*lista , newcode) == 1) { printf("\n\tQuesto codice esiste già, inseriscine un altro per favore"); }
                  else { condLoop = 0; }
               }
            
               condLoop = 0;
               while (condLoop == 1) {
                  printf("\n\tInserisci il nuovo piano: ");
                  scanf("%d" , &newpiano);
                  if ( newpiano > numPiani ) { printf("\n\t[] La tua struttura dispone di %d piano/i ... inserisci un dato corretto per favore" , numPiani); condLoop = 1; }
                  else { condLoop = 0; }
               }

               corr->infoStanzaSingola.codiceStanza = newcode;
               corr->infoStanzaSingola.pianoStanza = newpiano;

            } /* fine if || stanza trovata  */
            else { /* se la stanza non è stata trovata allora si passerà al nodo successivo */
               prec = prec->next;
               corr = prec->next;
            }

         } /* fine while || arrivati all'ultimo nodo oppure se la stanza è stata trovata */

      } /* fine else || se la stanza non si trova al primo nodo */
      
   }/* fine else || se la lista presenta elementi al suo interno */

} /* fine funzione modStanza() */

/* void readSettingsFromFile(FILE *fin , char nomeHotel[20] , int *numpiani) {
   fscanf(fin, "%s %d" , nomeHotel , numpiani);
}

void readFromFile(FILE *fin , TipoElem *elem) {
   
}*/

void addElemFromFileToLista(TipoLista *lista , TipoElem elem) {
   TipoNodo *newnode = malloc(sizeof(TipoNodo));
   TipoNodo *last;

   if (!newnode) { printf("\n\t ~~~ Errore allocazione memoria ~~~\n");  exit(-1);}
   newnode->infoStanzaSingola = elem;
   newnode->next = NULL;

   if (!(*lista)) { *lista = newnode; } /* se la lista non contiene elementi */
   else { /* se all'interno della lista ci sono già altri elementi */
      last = *lista;
      while (last->next) {
         last = last->next;
      }
      last->next = newnode;
   }
}

void buildFromFile(TipoLista *lista , const char nomeFile[8] , char *nomeHotel , int *numpiani) {
   TipoElem elem;
   FILE *fin = fopen(nomeFile , "r");
      if (!fin) { printf("\n\t ~~~ Errore apertura file ~~~\n"); exit(-1); }
   int count = 1;

   while (!feof(fin)) {
      if (count == 1) {
         fscanf(fin , "%s %d\n" , nomeHotel , numpiani);
         printf(" ~~~~ %s %d ~~~~\n" , nomeHotel , *numpiani);
      }
      else { 
         fscanf(fin , "%d %d %d\n" , &(elem.codiceStanza) , &(elem.pianoStanza) , &(elem.statoStanza) ) ;
         printf(" ~~~~ %d %d %d ~~~~\n " , elem.codiceStanza , elem.pianoStanza , elem.statoStanza);
         addElemFromFileToLista(lista , elem);
      }
      count += 1;
   }
   fclose(fin);
}

int checkFile(const char nomeFile[8]) {
   FILE *fin = fopen(nomeFile , "r");
      if (!fin) { printf("\n\t ~~~ Errore apertura file || Sei sicuro di averne? :p ~~~\n"); return -1; }
      else { return 0; }
}


void saveOnFile(TipoLista lista , const char nomeFile[8] , char nomeHotel[20] , int numPiani) {
   FILE *fout = fopen(nomeFile , "w");
   TipoNodo *node;
   TipoElem info;
   int count = 1;


   if (!fout) { printf("\n\tErrore nell'apertura del file in scrittura!\n"); exit(-1);}

   fprintf(fout , "%s %d\n" , nomeHotel , numPiani);
   node = lista;
   while (node) {
      info.codiceStanza = node->infoStanzaSingola.codiceStanza;
      info.pianoStanza = node->infoStanzaSingola.pianoStanza;
      info.statoStanza = node->infoStanzaSingola.statoStanza;

      fprintf(fout , "%d %d %d\n" , info.codiceStanza , info.pianoStanza , info.statoStanza);

      node = node->next;
   }

   fclose(fout);

}