#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define MAX_LINE 100

typedef struct 
{
    char ip[INET_ADDRSTRLEN];
    char name[50];
} User;

int verifier_ip(const char *ip, User *tab, int n, User *result);
int charger_user(const char *filename, User *tab, int max);

int charger_user(const char *filename, User *tab, int max) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Erreur fichier");
        return -1;
    }

    int i = 0;
    while (i < max && fscanf(f, "%s %s", tab[i].ip, tab[i].name) >= 1) 
    {
        i++;
    }

    fclose(f);
    return i;
}

int verifier_ip(const char *ip, User *tab, int n, User *result) 
{
    for (int i = 0; i < n; i++) 
{
        if (strcmp(tab[i].ip, ip) == 0) 
        {
            *result = tab[i];
            return 1;
        }
    }
    return 0;
}

int main() 
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addrlen = sizeof(client_addr);

    User users[100];
    int n = charger_user("add_autoris.txt", users, 100);

    if (n < 0) {
        printf("Erreur chargement fichier\n");
        return 1;
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    printf("Serveur en attente...\n");

    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);

    char client_ip[INET_ADDRSTRLEN];
    getpeername(client_fd, (struct sockaddr*)&client_addr, &addrlen);

    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));

    printf("Client connecté: %s\n", client_ip);

    User u;

    if (verifier_ip(client_ip, users, n, &u)) {
        char msg[200];

        sprintf(msg, "Bienvenue %s !\n", u.name);
        send(client_fd, msg, strlen(msg), 0);

        printf("Accès autorisé pour %s (%s)\n", u.name, client_ip);
    } else {
        char *msg = "Accès refusé\n";
        send(client_fd, msg, strlen(msg), 0);

        printf("Accès refusé pour %s\n", client_ip);
    }

    close(client_fd);
    close(server_fd);

    return 0;
}
