#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "spectacle.h"
#include "request.h"
#include "response.h"

#define FIFO_IN  "incoming.fifo"
#define FIFO_OUT "outcoming.fifo"

/* fichier de log */
static FILE *log_file = NULL;

/* log vers fichier + ecran */
void log_msg(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    if (log_file) {
        va_start(args, fmt);
        vfprintf(log_file, fmt, args);
        fflush(log_file);
        va_end(args);
    }
}

int main(void)
{
    init();

    /* ouverture du fichier de log */
    log_file = fopen("server.log", "a");
    if (!log_file) {
        perror("fopen server.log");
        exit(EXIT_FAILURE);
    }

    /* creation des FIFO (si inexistants) */
    if (mkfifo(FIFO_IN, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo incoming");
        exit(EXIT_FAILURE);
    }

    if (mkfifo(FIFO_OUT, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo outcoming");
        exit(EXIT_FAILURE);
    }

    log_msg("Serveur demarre PID=%d\n", getpid());

    /* ouverture des FIFO */
    int fd_in = open(FIFO_IN, O_RDONLY);
    if (fd_in == -1) {
        perror("open incoming");
        exit(EXIT_FAILURE);
    }

    int fd_out = open(FIFO_OUT, O_WRONLY);
    if (fd_out == -1) {
        perror("open outcoming");
        exit(EXIT_FAILURE);
    }

    while (1) {
        struct request req;
        ssize_t n = read(fd_in, &req, sizeof(req));

        if (n == 0) {
            log_msg("Client deconnecte\n");
            break;
        }

        if (n != sizeof(req)) {
            log_msg("Requete incomplete recue\n");
            continue;
        }

        log_msg("Requete: id=%d nbPlaces=%d\n",
                req.idSpectacle, req.nbPlaces);

        struct response resp;

        if (req.idSpectacle < 0 || req.idSpectacle >= nbSpectacles) {
            resp.code = 404;
        } else if (!retirerPlaces(req.idSpectacle, req.nbPlaces)) {
            resp.code = 409;
        } else {
            resp.code = 200;
        }

        log_msg("Reponse envoyee: code=%d\n", resp.code);

        if (write(fd_out, &resp, sizeof(resp)) != sizeof(resp)) {
            perror("write response");
            break;
        }
    }

    close(fd_in);
    close(fd_out);
    fclose(log_file);

    unlink(FIFO_IN);
    unlink(FIFO_OUT);

    return 0;
}
