#include <stdio.h>
#include "request.h"
#include "response.h"

int main(void)
{
    /* ===== Tests request ===== */
    struct request req;

    printf("\n--- Test sans argument ---\n");
    createRequest("getSpectacle", &req);
    afficherRequest(&req);

    printf("\n--- Test 1 argument ---\n");
    createRequest("getSpectacle?id=1", &req);
    afficherRequest(&req);

    printf("\n--- Test plusieurs arguments ---\n");
    createRequest("reserver?id=1&nbPlaces=2", &req);
    afficherRequest(&req);

    /* ===== Test response ===== */
    struct response resp;
    resp.code = 201;
    resp.nbContent = 2;

    snprintf(resp.content[0].cle, 50, "id");
    snprintf(resp.content[0].valeur, 50, "1");

    snprintf(resp.content[1].cle, 50, "placesRestantes");
    snprintf(resp.content[1].valeur, 50, "48");

    printf("\n--- Test response ---\n");
    afficherResponse(&resp);

    return 0;
}
