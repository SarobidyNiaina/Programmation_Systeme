import signal
import time

def handler(sig, frame):
    try:
        with open("/tmp/entier.txt", "r") as f:
            x = f.read().strip()
            print("Valeur reçue :", x)
    except:
        print("Erreur lecture fichier")

def main():
    signal.signal(signal.SIGUSR1, handler)

    import os
    print("PID du programme affiche :", os.getpid())

    while True:
        time.sleep(1)  # attente

if __name__ == "__main__":
    main()
