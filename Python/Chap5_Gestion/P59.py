import threading
import time
import random

data = None
vide = threading.Semaphore(1)
plein = threading.Semaphore(0)

def emetteur():
    global data
    while True:
        time.sleep(random.randint(1, 3))

        vide.acquire()   # attendre que le buffer soit libre

        data = random.randint(0, 255)  # un octet
        print(f"Émetteur envoie : {data}")

        plein.release()  # signaler qu'il y a une donnée

def recepteur():
    global data
    while True:
        plein.acquire()  
        print(f"Récepteur lit : {data}")

        vide.release()   # signaler que le buffer est libre

        time.sleep(random.randint(1, 3))

def main():
    t1 = threading.Thread(target=emetteur)
    t2 = threading.Thread(target=recepteur)

    t1.start()
    t2.start()

    t1.join()
    t2.join()

if __name__ == "__main__":
    main()
