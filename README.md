# Transazioni finanziarie su conto corrente

## Introduzione

Questo progetto permette di creare utenti con più conti corrente con i quali eseguire operazioni di invio, prelievo e 
deposito di denaro.

## Struttura

Sono state implementate le seguenti classi:
- `Utente`: classe che definisce l'utente a cui è possibile assegnare un conto corrente.
- `ContoCorrente`: classe che definisce il conto corrente. Ciascun conto è identificato dal suo attributo `id` e contiene 
un oggetto `StoricoTransazione` che tiene traccia delle transazioni avvenute su quel conto.
- `StoricoTransazione`: classe che contiene un vettore di transazioni. Fornisce operazioni quali ricerca e eliminazione.
- `Transazione`: classe che rappresenta la transazione. Contiene una funzione di modifica degli attributi `controparte` e 
`descrizione`.
- `Data`: classe che rappresenta una data.

### Classe _Utente_

Questa classe definisce un utente, identificato dall'attributo `id`.
La classe contiene un vettore `contiCorrente` che contiene gli oggetti `ContoCorrente` associati all'utente.

Con il metodo `aggiungiConto` è possibile aggiungere un conto corrente all'utente, identificato dal suo `id` che deve 
essere univoco, mentre con `eliminaConto` è possibile eliminare il conto con l'`id` passato come parametro.

La classe fornisce funzioni che permettono di scambiare denaro con altri utenti (`invia`) o di modificare il denaro 
presente sul conto (`deposita` e `preleva`).

### Classe _ContoContorrente_

Questa classe ha i seguenti attributi:
- `id`: stringa che identifica il conto.
- `saldo`: contiene il valore dei fondi presenti sul conto.
- `storico`: oggetto `StoricoTransazioni`. 
- `percorsoFile`: contiene il percorso in cui vengono salvati e caricati i dati del conto.

La classe fornisce funzioni permettono di aggiungere transazioni allo storico e verificare la disponibilità di denare, 
oltre che di salvare e caricare dati da _file_ attraverso i metodi `salvaDati` e `caricaDati`, con cui è possibile 
specificare il percorso. 

**N.B.** Nel caso si carichino i dati da _file_ i dati eventualmente presenti su quel conto vengono sovrascritti.

### Classe _StoricoTransazioni_
Questa classe ha come unico attributo un vettore di oggetti `Transazione`, ma fornisce diverse funzioni di ricerca e
eliminazione di una o più transazioni. Ciuscun metodo di ricerca restituisce un oggetto `StoricoTransazioni` 'fittizio'
permettendo di effettuare diversi tipi di ricerca a catena.

Le ricerche possibili sono:
- ricerca di transazioni in base all'`importo` all'interno di un certo _range_ di valori.
- ricerca di transazioni in base alla `data` all'interno di un certo _range_.
- ricerca di transazioni in base al `tipo` ('ingresso' o 'uscita').
- ricerca di transazioni in base a una stringa all'interno della `descrizione`.
- ricerca di transazioni avvenute con una specifica `controparte`.

Con i metodi di eliminazione è invece possibile eliminare una o più transazioni passate come parametri.

### Classe _Transazione_

Una transazione è caratterizzata dai seguenti attributi:
- `importo`: indica l'importo della transazione.
- `data`: oggetto Data che contiene la data in cui è avvenuta la transazione.
- `tipoTransazione`: inizializzato a 'ingresso' o 'uscita' al momento della creazione.
- `controparte`: contiene l'ID dell'utente con cui è avvenuta la transazione. In caso di semplice prelievo o deposito 
questo attributo contiene una stringa vuota.
- `descrizione`: una descrizione della transazione.

Per questa classe è stato effettuato l'_overload_ dell'operatore `==`.
E' poi presente un metodo `modifica` che permette di modificare gli attributi `descrizione` e `controparte`, oltre a un
metodo `toString` che restituisce una stringa con i dati della transazione.

### Classe _Data_

Questa classe contiene gli attributi di una data: `anno`, `mese`, `giorno`, `ora`, `minuto` e `secondo`.

Fornisce due costruttori: uno senza parametri che istanzia una data contenente la data di adesso, e uno che istanzia una
data a partire da una stringa nel formato `"AAAA-MM-GG OO:MM:SS"`.

In questa classe è stato effettuato l'_overload_ degli operatori `==`, `<` e `>`.

Vengono poi forniti metodi per verificare la legalità della data creata (`verificaData`) e per ritornare la data sotto
forma di stringa (`toString`).

## Unit Testing

Nella cartella `test` sono presenti due _test fixture_ relative alle classi `ContoCorrente` e `StoricoTransazioni`, e 
due _test suite_ per le classi `Transazione` e `Data`.

### _ContoCorrente Fixture_

Sono stati eseguiti test per verificare il corretto comportamento delle operazioni effettuabili dagli utenti sul conto
quali `aggiungiConto`, `eliminaConto`, `invia`, `deposita` e `preleva`.

Vengono anche testati i metodi `salvaDati` e `caricaDati` della classe `ContoCorrente`, verificando che un salvataggio 
immediatamente successivo ad un caricamento produca lo stesso contenuto del _file_ caricato. Si verifica anche che la 
sovrascrittura di un conto a seguito di un caricamento venga effettuata correttamente.

### _StoricoTransazioni Fixture_

Vengono eseguiti test sui metodi di ricerca e eliminazione. 

La ricerca viene provata per ogni tipo di ricerca possibile e si eseguono test anche per la ricerca a catena.

Sono presenti test per l'eliminazione di più transazioni (l'eliminazione di una singola transazione non viene testata
in quanto il metodo viene richiamato ogni volta che si elimina più di una transazione).

### _Transazione Suite_

In questa _suite_ si eseguono test su ogni tipo di modifica della transazione.

### _Data Suite_

In questa _suite_ si testa il corretto funzionamento del metodo `verficaData` con tante diverse combinazioni di valori.


**N.B.** l'eseguibile `runTests` deve essere eseguito dalla sottocartella "build/test" affinchè funzioni correttamente.
