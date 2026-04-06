import os
import sys

print("creation de processus")

for i in range(5):
    F1 = os.fork()

    if F1 == 0:
        print(f"{i+1} : je suis le fils. pid={os.getpid()} / ppid={os.getppid()}")
        sys.exit(0)

# attendre les 5 fils
for _ in range(5):
    os.wait()

print(f"je suis le père.. pid={os.getpid()}")
