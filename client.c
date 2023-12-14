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

        int gameFinished = 0;

        while (!gameFinished) {
            int valread = read(sock, buffer, 1024);
            if (valread <= 0) {
                printf("Erreur de connexion avec le serveur.\n");
                close(sock);
                return -1;
            }

            buffer[valread] = '\0';

            // Check if the game is finished
            if (strcmp(buffer, "You've guessed the word!\n") == 0) {
                printf("%s", buffer);
                gameFinished = 1;
                break;
            } else {
                // Print the updated word or response from server
                printf("%s\n", buffer);
            }

            if (!gameFinished) {
                printf("Entrez une lettre: ");
                scanf(" %c", &guess[0]); // Using %c to read a single character
                send(sock, guess, 1, 0); // Sending only one character
            }
        }

        close(sock);

        if (gameFinished) {
            printf("Voulez-vous jouer une autre partie? (y/n): ");
            scanf(" %c", &choice[0]); // Using %c to read a single character
        }
    } while (choice[0] == 'y' || choice[0] == 'Y');

    return 0;
}