import threading
import socket
import datetime

class Produit:
    def __init__(self, nom, prix):
        self.nom = nom
        self.prix = float(prix)


def charger_produits(fichier):
    produits = []
    with open(fichier, "r") as f:
        for ligne in f:
            nom, prix = ligne.strip().split()
            produits.append(Produit(nom, prix))
    return produits

def trouver_produit(nom, produits):
    for p in produits:
        if p.nom == nom:
            return p
    return None


def serveur(produits):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("0.0.0.0", 5000))
    s.listen(1)

    print("Serveur en attente...")

    conn, addr = s.accept()
    print("Client connecté :", addr)

    conn.send(b"Nom du produit : ")
    nom = conn.recv(1024).decode().strip()

    conn.send(b"Quantite : ")
    qte = int(conn.recv(1024).decode().strip())

    p = trouver_produit(nom, produits)

    if p:
        total = p.prix * qte
        conn.send(f"Prix total = {total}\n".encode())
    else:
        conn.send(b"Produit introuvable\n")

    conn.close()

def gestion_commande(conn, produits):
    total = 0

    conn.send(b"Entrez produit et quantite (ex: pomme 2), 'fin' pour terminer\n")

    while True:
        conn.send(b"> ")
        data = conn.recv(1024).decode().strip()

        if data == "fin":
            break

        nom, qte = data.split()
        qte = int(qte)

        p = trouver_produit(nom, produits)

        if p:
            total += p.prix * qte
        else:
            conn.send(b"Produit introuvable\n")

    conn.send(f"Total = {total}\n".encode())


def sauvegarder_commande(nom_client, total):
    nom_fichier = f"commande_{datetime.datetime.now().timestamp()}.txt"

    with open(nom_fichier, "w") as f:
        f.write(f"Client: {nom_client}\n")
        f.write(f"Total: {total}\n")

#import threading

def client_thread(conn, produits):
    conn.send(b"Nom du client : ")
    nom_client = conn.recv(1024).decode().strip()

    total = 0

    conn.send(b"Commande (nom qte) ou 'fin'\n")

    while True:
        conn.send(b"> ")
        data = conn.recv(1024).decode().strip()

        if data == "fin":
            break

        nom, qte = data.split()
        qte = int(qte)

        p = trouver_produit(nom, produits)

        if p:
            total += p.prix * qte
        else:
            conn.send(b"Produit introuvable\n")

    conn.send(f"Total = {total}\n".encode())

    sauvegarder_commande(nom_client, total)

    conn.close()


def serveur_multi(produits):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("0.0.0.0", 5000))
    s.listen(5)

    print("Serveur prêt...")

    while True:
        conn, addr = s.accept()
        t = threading.Thread(target=client_thread, args=(conn, produits))
        t.start()
def main():
    produits = charger_produits("produits.txt")
    serveur_multi(produits)

if __name__ == "__main__":
    main()
