#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

void pickRandomWord(char *word, const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[100];
    char *wordList[100];
    int wordCount = 0;

    if (file == NULL) {
        perror("Unable to open the file");
        exit(1);
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        wordList[wordCount] = strdup(line);
        wordCount++;
    }

    strcpy(word, wordList[rand() % wordCount]);

    // Free the memory allocated for wordList
    for (int i = 0; i < wordCount; i++) {
        free(wordList[i]);
    }

    fclose(file);
}

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address, client_addr;
    int opt = 1;
    int addrlen = sizeof(client_addr);
    char buffer[1024] = {0};
    char word[100], hiddenWord[100];
    int i, correct;

    srand(time(0));

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            continue; // Continue to the next iteration to keep listening
        }

        printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

        pickRandomWord(word, "mots.txt");
        printf("Word to guess: %s\n", word);

        for(i = 0; word[i] != '\0'; i++) {
            hiddenWord[i] = '_';
        }
        hiddenWord[i] = '\0';

        while(strcmp(hiddenWord, word) != 0) {
            send(new_socket, hiddenWord, strlen(hiddenWord), 0);
            valread = read(new_socket, buffer, 1024);
            if (valread <= 0) {
                printf("Client disconnected\n");
                break; // Break out of the loop if client disconnects
            }
            buffer[valread] = '\0';

            correct = 0;
            for(i = 0; word[i] != '\0'; i++) {
                if(word[i] == buffer[0]) {
                    hiddenWord[i] = buffer[0];
                    correct = 1;
                }
            }
        }

        if (strcmp(hiddenWord, word) == 0) {
            send(new_socket, "You've guessed the word!\n", strlen("You've guessed the word!\n"), 0);
            close(new_socket); // Close the connection once the game is over
        }
    }

    // close(server_fd); // This line is unreachable due to the infinite loop
    return 0;
}