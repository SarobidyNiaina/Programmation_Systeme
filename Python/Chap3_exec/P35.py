import os
import sys

while True:
    commande = input("veuillez entrer le nom du fichier : ")

    if commande == "exit":
        break

    f = os.fork()

    if f == 0:
        # processus fils
        try:
            os.execv("/usr/bin/emacs", ["/usr/bin/emacs", commande])
        except OSError:
            print("Erreur d'exécution...")
            sys.exit(1)

    elif f > 0:
        # processus père
        os.wait()

    else:
        print("erreur du fork")
