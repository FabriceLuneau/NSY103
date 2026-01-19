#include <stdio.h>
#include <string.h>

#include "bridge.h"
#include "response.h"
#include "spectacle.h"

/* ===== OUTIL DE DEBUG ===== */
static void afficherResponse(const struct response *resp) {
    printf("---- RESPONSE ----\n");
    response_afficher(resp);
    printf("------------------\n\n");
}

/* ===== TEST 1 : UN SEUL SPECTACLE ===== */
void test_bridge_un_spectacle() {
    printf("[TEST] bridge : un seul spectacle\n");

    struct spectacle s = {
        .intitule = "Concert Rock",
        .nbPlaces = 250
    };

    struct response resp = response_create("200");
    bridge_encodeUnSpectacleResponse(&resp, s);

    afficherResponse(&resp);
}

/* ===== TEST 2 : PLUSIEURS SPECTACLES ===== */
void test_bridge_plusieurs_spectacles() {
    printf("[TEST] bridge : plusieurs spectacles\n");

    struct spectacle spectacles[2] = {
        { "Opera", 100 },
        { "Theatre", 75 }
    };

    struct response resp = response_create("200");
    bridge_encodeSpectaclesResponse(&resp, spectacles, 2);

    afficherResponse(&resp);
}

/* ===== TEST 3 : AUCUN SPECTACLE ===== */
void test_bridge_aucun_spectacle() {
    printf("[TEST] bridge : aucun spectacle\n");

    struct response resp = response_create("204");
    bridge_encodeSpectaclesResponse(&resp, NULL, 0);

    afficherResponse(&resp);
}

/* ===== TEST 4 : RESPONSE NULL ===== */
void test_bridge_response_null() {
    printf("[TEST] bridge : response NULL (ne doit pas crasher)\n");

    struct spectacle s = { "Test", 10 };
    bridge_encodeUnSpectacleResponse(NULL, s);
}

/* ===== MAIN ===== */
int main(void) {
    test_bridge_un_spectacle();
    test_bridge_plusieurs_spectacles();
    test_bridge_aucun_spectacle();
    test_bridge_response_null();

    return 0;
}
