#include <stdbool.h>
#include<stdio.h>
#include"spectacle.h"
#include "response.h"
#include"bridge.h"


int main(int argc, char** argv) 
{
	printf("Test encode un spectacle \n\n");

	struct spectacle spec = spectacle_creer("Le chat beaute", 2);

	struct response resp;
	 response_init(&resp, 200);
bridge_encodeUnSpectacle(&resp, spec);
response_afficher(&resp);

		printf("\n Encoder plusieur spectacles\n\n");







	    
	return 0;
	}
 