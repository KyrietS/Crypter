# Crypter
Konsolowa aplikacja do szyfrowania plików podanym przez użytkownika hasłem.

`help` wyświetla listę dostępnych poleceń. Na tę chwilę to:

```
Crypter version 1.0 (work-in-progress)

CRYPTER> help

ANALYZE      - Displays information about given files. Checks if file is encrypted.
AUTO         - Decrypts if file is encrypted and encrypts if file is not encrypted.
DECRYPT      - Decrpts files with a specified password.
ENCRYPT      - Encrypts files with a specified password.
EXIT         - Exit Crypter.
HELP         - Displays help for specified command
```

Program do każdego zaszyfrowanego pliku dodaje nagłówek specyficzny dla tego programu wraz z sumą kontrolną. 

Obecny algorytm sortowania opiera się na operacji XOR poszczególnych bitów z pliku i hasła. Algorytm można jednak bardzo łatwo podmienić na inny nie naruszając innych funkcjonalności programu. 

Suma kontrolna jest wyliczana jako negacja sumy wszystkich bajtów z pliku (jeśli plik jest duży i suma bajtów przekroczy zakres typu `unsigned long long`, to nadal otrzymamy poprawną sumę kontrolna)
