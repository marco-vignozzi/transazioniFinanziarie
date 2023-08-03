# Transazioni finanziarie su conto corrente

## Introduzione

Questo progetto permette di creare utenti e conti corrente ad essi associati con il quale eseguire delle transazioni 
in ingresso e in uscita.

## Struttura

Le classi principali sono:
- `Utente`: classe che definisce l'utente a cui è possibile assegnare un conto corrente.
- `ContoCorrente`: classe che definisce il conto corrente. 
Ad esso è associato un utente, rappresentato attraverso il suo ID (`idUtente`), ed un vettore `storicoTransazioni` che 
contiene tutte le Transazioni effettuate con quel conto.
- `Transazione`: classe astratta che rappresenta la transazione e viene derivata nelle classi `TransazioneIngresso` e
`TransazioneUscita`.

### Classe _Utente_

Questa classe definisce un utente, identificato dall'attributo `idUtente`. Con il metodo `addConto` è possibile
assegnare un conto corrente all'utente.

### Classe _ContoContorrente_

Questa è la classe principale del progetto. 
I suoi attributi sono:
- `idUtente`: identifica l'utente associato al conto; se al conto non è stato associato un utente questo valore sarà 
uguale a "NULL".
- `saldo`: contiene il valore dei fondi presenti sul conto.
- `storicoTransazioni`: un vettore che contiene le transazioni effettuate su quel conto fino a quel momento.
- `percorsoFile`: contiene il percorso in cui vengono salvati e caricati i dati del conto.

Questa classe viene utilizzata per effettuare le transazioni tra utenti attraverso i metodi `invia`, `deposita` e `preleva`. 
Ciascuno di questi metodi ritorna un valore _booleano_ che stabilisce se è stato possibile eseguire l'operazione richiesto.

I metodi creano transazioni, le eseguono e le aggiungono allo `storicoTransazioni`.
Per visualizzare il contenuto dello storico sotto forma di stringa è possibile chiamare il metodo `getStoricoToString`. 

Le classi permettono inoltre di salvare e caricare dati da _file_ attraverso i metodi `salvaDati` e `caricaDati`, 
con cui è possibile specificare il percorso. 

**N.B.** Nel caso si carichino i dati da _file_ i dati eventualmente presenti su quel conto vengono sovrascritti.

### Classe _Transazione_

Come detto in precedenza questa è una classe astratta che viene poi derivata nelle classi `TransazioneIngresso` e
`TransazioneUscita`. 

Una transazione è caratterizzata dai seguenti attributi:
- `importo`: indica l'importo della transazione.
- `data`: la data in cui è avvenuta, sotto forma di stringa.
- `tipoTransazione`: inizializzato a "Ingresso" o "Uscita" dalle rispettive classi derivate.
- `mittente`/`destinatario`: contiene l'ID dell'utente con cui è avvenuta la transazione. In caso di semplice
prelievo o deposito questi attributi conterranno entrambi una stringa vuota, altrimenti solo uno dei due verrà modificato.
- `descrizione`: una descrizione della transazione.

E' poi presente un unico metodo `esegui`, puramente virtuale, che si occuperà di prelevare o depositare i soldi sul conto passato
come parametro.

## Unit Testing

Nella cartella `test` è presente un'unica _fixture_ relativa alla classe `ContoCorrente`. Questa contiene infatti quasi 
tutta la logica del programma.

Sono stati eseguiti test per verificare il corretto comportamento delle operazioni effettuabili sul conto (**invio**, 
**deposito** e **prelievo**), sia relativamente alle loro modifiche del **saldo** totale, sia al numero di **transazioni**
che vengono aggiunte al vettore `storicoTransazioni`.

In ultimo vengono anche testati i metodi `salvaDati` e `caricaDati`, verificando che un salvataggio immediatamente 
successivo ad un caricamento produca lo stesso contenuto del _file_ caricato. Si verifica anche che la sovrascrittura
di un conto a seguito di un caricamento venga effettuata correttamente.

**N.B.** l'eseguibile `runTests` deve essere eseguito dalla sottocartella "build/test" affinchè funzioni correttamente.
