#!/usr/bin/bash

#Supprime les test précédents
#on utilise .exe pour mieux discriminer  les exécutables et avoir une règle dans le git ignore
rm test/*.exe

#compilation

#test des fonctions spectacles
gcc testSpectacle.c -o test/spectacle.exe
#test descle valeur
gcc testClefValeur.c -o test/cleValeur.exe

#teste dus protocoles de communication
gcc testRequest.c  -o test/request.exe
gcc testResponse.c -o test/response.exe

#test du bridge de donnees
gcc testBridge.c -o test/bridge.exe

