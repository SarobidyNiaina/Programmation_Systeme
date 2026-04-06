import os
import sys

print("creation de processus")

try:
    F = os.fork()
except OSError:
    print("Erreur dans le fork")
    sys.exit(1)

if F == 0:
    print("je suis le fils..")
    sys.exit(0)
else:
    print("je suis le père..")
    sys.exit(0)
