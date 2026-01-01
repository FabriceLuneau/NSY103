#!/usr/bin/bash

#Supprime les build précédents
#on utilise .exe pour ignorerfereencierdifférencier les fichiers et pour le git ignore
rm *.exe

#compilation

#version standalone de l'aplication
gcc test.c -o standalone.exe 

#test des fonctions spectacles
gcc testSpectacle.c -o spectacle.exe

#version avec tubes anonymes
gcc q1-tube-anonyme.c -o server1.exe

#version avec tubes nommes
gcc q1b-client-tube-nomme.c -o client2.exe

gcc  q1b-server-tube-nomme.c -o server2.exe


