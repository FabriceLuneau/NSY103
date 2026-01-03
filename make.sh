#!/usr/bin/bash

#Supprime les build précédents
#on utilise .exe pour ignorerfereencierdifférencier les fichiers et pour le git ignore
rm build/*.exe

#compilation

#version standalone de l'aplication
gcc standalone.c -o build/standalone.exe 

#test des fonctions spectacles
gcc testSpectacle.c -o build/spectacle.exe

#version avec tubes anonymes
gcc q1-tube-anonyme.c -o build/server1.exe

#version avec tubes nommes
gcc q1b-client-tube-nomme.c -o build/client2.exe

gcc  q1b-server-tube-nomme.c -o build/server2.exe


