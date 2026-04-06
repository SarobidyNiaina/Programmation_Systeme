import os

def rechercher_mot(fichier, mot):
    try:
        with open(fichier, 'r') as f:
            contenu = f.read().split()  # séparer en mots
            return 1 if mot in contenu else 0
    except FileNotFoundError:
        print("Fichier introuvable.")
        return 0


def main():
    pipe1_r, pipe1_w = os.pipe()
    pipe2_r, pipe2_w = os.pipe()

    pid = os.fork()

    if pid == 0:
 
        os.close(pipe1_r)  
        os.close(pipe2_w)  

        mot = input("Entrez un mot : ")
        os.write(pipe1_w, mot.encode()
       resultat = os.read(pipe2_r, 10).decode()

        print("Résultat :", resultat)

        os.close(pipe1_w)
        os.close(pipe2_r)

    else:
        os.close(pipe1_w) 
        os.close(pipe2_r)  

        fichier = "test.txt"  
        mot = os.read(pipe1_r, 100).decode()
        res = rechercher_mot(fichier, mot)
 
        os.write(pipe2_w, str(res).encode())

        os.close(pipe1_r)
        os.close(pipe2_w)

        os.wait()


if __name__ == "__main__":
    main()
