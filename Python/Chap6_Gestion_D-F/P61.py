import sys
import os

# taille limite (1 Mo)
LIMITE = 1_000_000

def traiter_repertoire(rep):
    try:
        for fichier in os.listdir(rep):
            chemin = os.path.join(rep, fichier)

            # vérifier que c'est un fichier
            if os.path.isfile(chemin):
                taille = os.path.getsize(chemin)

                if taille > LIMITE:
                    stat = os.stat(chemin)
                    uid = stat.st_uid

                    print(f"{chemin} | taille={taille} | uid={uid}")

    except Exception as e:
        print(f"Erreur avec {rep} : {e}")

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 script.py rep1 rep2 ...")
        sys.exit(1)

    for rep in sys.argv[1:]:
        traiter_repertoire(rep)

if __name__ == "__main__":
    main()
