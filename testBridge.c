#include <stdio.h>
#include <string.h>

#include "bridge.h"
#include "response.h"
#include "spectacle.h"

int main(void)
{
    struct spectacle tabSpectaclesGlobal[2];

    strcpy(tabSpectaclesGlobal[0].intitule, "Concert");
    tabSpectaclesGlobal[0].nbPlaces = 100;

    strcpy(tabSpectaclesGlobal[1].intitule, "Theatre");
    tabSpectaclesGlobal[1].nbPlaces = 50;

    /* ===== Test avec plusieurs spectacles ===== */
    struct response resp1 = response_create(200);

    bridge_encodeSpectaclesResponse(
        &resp1,
        tabSpectaclesGlobal,
        2
    );

    response_print(&resp1);
    response_free(&resp1);

    /* ===== Test avec un seul spectacle ===== */
    struct response resp2 = response_create(200);

    bridge_encodeUnSpectacleResponse(
        &resp2,
        tabSpectaclesGlobal[0]
    );

    response_print(&resp2);
    response_free(&resp2);

    return 0;
}
