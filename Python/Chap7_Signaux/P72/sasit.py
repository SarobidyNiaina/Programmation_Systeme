import os
import signal

def main():
    x = input("Entrer un entier : ")

    with open("/tmp/entier.txt", "w") as f:
        f.write(x)

    pid = int(input("Donner le PID de affiche.py : "))

    os.kill(pid, signal.SIGUSR1)

if __name__ == "__main__":
    main()
