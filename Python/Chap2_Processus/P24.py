import os
import time
import random
import sys

print("creation de processus")

start_time = time.time()

# FILS 1 
F1 = os.fork()

if F1 == 0:
    random.seed(time.time() ^ os.getpid())  # important
    seconde = random.randint(1, 10)

    print(f"Fils 1 pid={os.getpid()} dort {seconde} sec")
    time.sleep(seconde)

    sys.exit(0)

# f2 
F2 = os.fork()

if F2 == 0:
    random.seed(time.time() ^ os.getpid())  # important
    seconde = random.randint(1, 10)

    print(f"Fils 2 pid={os.getpid()} dort {seconde} sec")
    time.sleep(seconde)

    sys.exit(0)

#
os.waitpid(F1, 0)
os.waitpid(F2, 0)

end_time = time.time()

duree = end_time - start_time

print(f"Durée totale : {duree:.0f} secondes")
