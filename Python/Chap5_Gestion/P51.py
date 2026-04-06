import threading

def afficher_tableau(tab):
    print("Tableau reçu par le thread :")
    for x in tab:
        print(x, end=" ")
    print()

def main():
    tableau = [1, 2, 3, 4, 5]
    t = threading.Thread(target=afficher_tableau, args=(tableau,))
    t.start()
    t.join()

    print("Fin du programme principal")

if __name__ == "__main__":
    main()
