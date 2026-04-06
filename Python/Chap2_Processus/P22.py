import os
import sys

print("creation de processus")

# premier fork
F1 = os.fork()

if F1 == 0:
    print(f"je suis le fils 1 mon pid={os.getpid()} / {os.getppid()}..")
    sys.exit(0)

# deuxième fork (exécuté seulement par le père)
F2 = os.fork()

if F2 == 0:
    print(f"je suis le fils 2 mon pid={os.getpid()} / {os.getppid()}..")
    sys.exit(0)

# le père attend ses deux fils
os.wait()
os.wait()

print(f"je suis le père.. pid={os.getpid()}")
