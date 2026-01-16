#!/usr/bin/bash

#Supprime les build précédents
#on utilise .exe pour mieux discriminer  les exécutables et avoir une règle dans le git ignore
rm test/*.exe

#compilation

#test des fonctions spectacles
gcc testSpectacle.c -o build/spectacle.exe
#test descle valeur
gcc testCleValeur.c -o build/cleValeur.exe

#teste dus protocoles de communication
gcc testRequest.c  -o build/request.exe
gcc testResponse.c -o build/response.exe

#test du bridge de donnees
gcc testBridge.c -o build/bridge.exe

