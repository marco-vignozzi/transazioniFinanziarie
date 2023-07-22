## Transazioni finanziarie su conto corrente

### Introduzione

Questo progetto permette di creare utenti e conti corrente ad essi associato con il quale eseguire delle transazioni in ingresso e in uscita.

### Struttura

Le classi principali sono:
- `Utente`: classe che definisce l'utente a cui è possibile assegnare un conto corrente.
- `ContoCorrente`: classe che definisce il conto corrente. 
Ad esso è associato un utente, rappresentato attraverso il suo ID (`idUtente`), ed un vettore `storicoTransazioni` che contiene tutte le Transazioni effettuate con quel conto.
- `Transazione`: classe astratta che rappresenta la transazione e viene derivata nelle classi `TransazioneIngresso` e `TransazioneUscita`.

### Classe ContoContorrente

Questa è la classe principale del progetto. Viene utilizzata per effettuare le transazioni tra utenti attraverso i metodi `invia`, `deposita` e `preleva`. I metodi creano transazioni, le eseguono e le aggiungono allo `storicoTransazioni`. 
Per visualizzare il contenuto dello storico sotto forma di stringa è possibile chiamare il metodo `getStoricoToString`. Le classi permettono inoltre di salvare e caricare dati da _file_ attraverso i metodi `salvaDati` e `caricaDati`, con cui è possibile specificare il 
