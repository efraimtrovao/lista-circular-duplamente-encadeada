#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char artist[100];
    char song[100];
    struct Node *prev;
    struct Node *next;
} Node;

Node *head = NULL;
Node *tail = NULL;

void readFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        Node *newNode = (Node *) malloc(sizeof(Node));
        sscanf(line, "%[^;];%[^\n]", newNode->artist, newNode->song);
        newNode->prev = NULL;
        newNode->next = head;

        if (head != NULL) {
            head->prev = newNode;
        }

        head = newNode;

        if (tail == NULL) {
            tail = newNode;
        }
    }

    fclose(file);
}

void printMenu() {
    printf("1. Exibir playlist por ordem de cadastro\n");
    printf("2. Exibir playlist ordenadas pelo nome das músicas\n");
    printf("3. Inserir nova música\n");
    printf("4. Remover música\n");
    printf("5. Buscar música\n");
    printf("6. Avançar para próxima música\n");
    printf("7. Retornar a música anterior\n");
    printf("0. Sair\n");
}

void insertSong(char *artist, char *song) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    strcpy(newNode->artist, artist);
    strcpy(newNode->song, song);
    newNode->prev = tail;
    newNode->next = NULL;

    if (tail != NULL) {
        tail->next = newNode;
    }

    tail = newNode;

    if (head == NULL) {
        head = newNode;
    }
}

void removeSong(char *song) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->song, song) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }

            free(current);
            break;
        }

        current = current->next;
    }
}

void searchSong(char *song) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->song, song) == 0) {
            printf("Encontrado: %s - %s\n", current->artist, current->song);
            break;
        }

        current = current->next;
    }
}

void playNextSong() {
    if (head != NULL) {
        head = head->next;
    }
}

void playPreviousSong() {
    if (tail != NULL) {
        tail = tail->prev;
    }
}

int main() {
    char fileName[] = "songs.txt";
    readFile(fileName);

    int option;
    while (1) {
        printMenu();
        printf("Digite a opção desejada: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                Node *current = head;
                while (current != NULL) {
                    printf("%s - %s\n", current->artist, current->song);
                    current = current->next;
                }
                break;
            }
            case 2: {
                // TODO: Implement sorting
                break;
            }
            case 3: {
                char artist[100];
                char song[100];
                printf("Digite o nome do artista: ");
                scanf("%s", &artist);
                printf("Digite o nome da música: ");
                scanf("%s", &song);
                insertSong(artist, song);
                break;
            }
            case 4: {
                char song[100];
                printf("Digite o nome da música: ");
                scanf("%s", &song);
                removeSong(song);
                break;
            }
            case 5: {
                char song[100];
                printf("Digite o nome da música: ");
                scanf("%s", &song);
                searchSong(song);
                break;
            }
            case 6: {
                playNextSong();
                break;
            }
            case 7: {
                playPreviousSong();
                break;
            }
            case 0: {
                return 0;
            }
            default: {
                printf("Opção inválida.\n");
                break;
            }
        }
    }

    return 0;
}