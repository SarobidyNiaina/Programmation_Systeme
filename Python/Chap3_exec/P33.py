import sys
import shutil
import os

if len(sys.argv) < 2:
    print("Usage : python script.py dossier_destination")
    sys.exit(1)

destination = sys.argv[1]

for fichier in os.listdir("."):
    if fichier != os.path.basename(__file__):  # éviter de copier le script lui-même
        if os.path.isdir(fichier):
            shutil.copytree(fichier, os.path.join(destination, fichier))
        else:
            shutil.copy2(fichier, destination)

print("copie terminée...")
