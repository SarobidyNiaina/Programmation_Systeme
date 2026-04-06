import threading
import time
import random
import sys

N = int(sys.argv[1])  # nombre de threads

compteur = 0
lock = threading.Lock()
sem = threading.Semaphore(0)

def travail(id):
    global compteur

    for i in range(10):
        t = random.randint(1, 5)
        print(f"Thread {id} travaille {t}s")
        time.sleep(t)

        print(f"Thread {id} arrive au rendez-vous")

        with lock:
            compteur += 1
            if compteur == N:
                print("Tous les threads sont arrivés !")
                for _ in range(N):
                    sem.release()

        sem.acquire()  # attendre les autres

        print(f"Thread {id} repart\n")

def main():
    threads = []

    for i in range(N):
        t = threading.Thread(target=travail, args=(i,))
        threads.append(t)
        t.start()

    for t in threads:
        t.join()

if __name__ == "__main__":
    main()
