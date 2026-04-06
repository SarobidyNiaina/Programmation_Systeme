import os
import signal
import time

def fils():
    i = 0
    while True:
        i += 1
        print(f"Fils calcule : {i}")
        time.sleep(1)

def main():
    pid = os.fork()

    if pid == 0:
        # processus fils
        fils()
    else:
        # processus père
        while True:
            choix = input("s=stop, r=run, q=quit : ")

            if choix == 's':
                os.kill(pid, signal.SIGSTOP)
                print("Fils stoppé")

            elif choix == 'r':
                os.kill(pid, signal.SIGCONT)
                print("Fils relancé")

            elif choix == 'q':
                os.kill(pid, signal.SIGKILL)
                print("Fils tué")
                break

        print("Père termine")

if __name__ == "__main__":
    main()
