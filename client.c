#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char guess[2];
    char choice[2];

    do {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return -1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("\nConnection Failed \n");
            return -1;
        }

        while (1) {
            int valread = read(sock, buffer, 1024);
            if (valread <= 0) {
                printf("Connection closed by the server.\n");
                break;
            }

            buffer[valread] = '\0';
            printf("Mot à trouver: %s\n", buffer);

            if (strcmp(buffer, "You've guessed the word!\n") == 0) {
                break;
            }

            printf("Entrez une lettre: ");
            scanf(" %c", &guess[0]);
            send(sock, guess, 1, 0);
        }

        printf("Voulez-vous jouer une autre partie? (y/n): ");
        scanf(" %c", &choice[0]);

        close(sock); // Fermeture du socket

    } while (choice[0] == 'y' || choice[0] == 'Y');

    return 0;
}
