import sys
import subprocess

if len(sys.argv) < 2:
    print("Usage : python script.py dossier_destination")
    sys.exit(1)

destination = sys.argv[1]

commande = ["cp", "-r", "*", destination]

subprocess.run("cp -r * " + destination, shell=True)

print("exécution de la commande...")
