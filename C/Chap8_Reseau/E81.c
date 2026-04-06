#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define PORT 8080
#define MAX_PRODUITS 100
#define MAX_NAME 50

typedef struct {
    char name[MAX_NAME];
    float price;
} Produit;

int charger_produits(const char *filename, Produit *tab, int max);
Produit* trouver_produit(Produit *tab, int n, const char *nom);
void enregistrer_commande(const char *data);

int charger_produits(const char *filename, Produit *tab, int max) 
{
    FILE *f = fopen(filename, "r");
    if (!f) 
    {
        perror("Erreur ouverture fichier");
        return -1;
    }

    int i = 0;
    while (i < max && fscanf(f, "%s %f", tab[i].name, &tab[i].price) == 2) {
        i++;
    }

    fclose(f);
    return i;
}

Produit* trouver_produit(Produit *tab, int n, const char *nom) 
{
    for (int i = 0; i < n; i++) 
    {
        if (strcmp(tab[i].name, nom) == 0) 
        {
            return &tab[i];
        }
    }
    return NULL;
}

void enregistrer_commande(const char *data) 
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    char filename[100];
    strftime(filename, 100, "commande_%Y%m%d_%H%M%S.txt", tm_info);

    FILE *f = fopen(filename, "w");
    if (f) 
    {
        fprintf(f, "%s\n", data);
        fclose(f);
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addrlen = sizeof(client_addr);

    Produit produits[MAX_PRODUITS];

    int n = charger_produits("produits.txt", produits, MAX_PRODUITS);
    if (n < 0) {
        printf("Erreur chargement base\n");
        return 1;
    }

    /* Création socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    printf("Serveur en attente...\n");

    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);

    char buffer[200];

    while (1) {
        send(client_fd, "Commande (nom qte ...): ", 25, 0);

        int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) break;

        buffer[bytes] = '\0';

        char copie[200];
        strcpy(copie, buffer);

        char *token = strtok(buffer, " ");
        float total = 0;

        while (token != NULL) {
            char nom[50];
            int qte;

            strcpy(nom, token);

            token = strtok(NULL, " ");
            if (!token) break;

            qte = atoi(token);

            Produit *p = trouver_produit(produits, n, nom);

            if (p != NULL) {
                total += p->price * qte;
            }

            token = strtok(NULL, " ");
        }

        char msg[200];
        sprintf(msg, "Total commande: %.2f\n", total);
        send(client_fd, msg, strlen(msg), 0);

        enregistrer_commande(copie);
    }

    close(client_fd);
    close(server_fd);

    return 0;
}
