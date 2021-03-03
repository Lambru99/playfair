# playfair
Playfair è un programma di criptaggio di messaggi basato su alfabeto, chiave, carattere speciale e carattere sostitutivo. L'algoritmo è possibile trovarlo [qui](https://en.wikipedia.org/wiki/Playfair_cipher). Il programma è stato sviluppato in C per l'esame di [Laboratorio di sistemi operativi](http://didattica.cs.unicam.it/doku.php?id=didattica:triennale:so:ay_2021:lab) presso l'università du [Unicam](https://www.unicam.it/).


# Come usarlo

Comando di esempio per eseguire il programma:

playfair encode|decode keyfile outputdir file1 ... filen



playfair	=	Eseguibile del programma a cui passare paramentri.

encode,decode	=	Parametro per codificare,decodificare un messaggio.

keyfile	=	Percorso della file chiave contenente alfabeto, carattere sostitutivo, carattere speciale e chiave di cifratura.

outputdir	=	Percorso della cartella di destinazione del file cifrato/decifrato con estenzione ".pf/.dec".

file1...filen	=	Percorsi dei file da codificare/decodificare.

-h,	--help	=	Stampa delle informazioni.
