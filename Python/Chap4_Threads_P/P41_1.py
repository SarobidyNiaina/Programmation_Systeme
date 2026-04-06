import os
import sys

fd_r, fd_w = os.pipe()
fd1_r, fd1_w = os.pipe()

f = os.fork()

if f == -1:
    print("erreur dans le fork..")
    sys.exit(1)

# ---------- FILS ----------
if f == 0:
    os.close(fd_r)
    os.close(fd1_w)

    # lire le résultat envoyé par le père
    check_bytes = os.read(fd1_r, 4)
    check = int.from_bytes(check_bytes, byteorder='little', signed=True)

    if check == 1:
        print("mot trouvé ....")
    elif check > -1:
        print("non trouvé..")

    # saisir le mot
    R = input("entrez le mot à rechercher: ")

    os.write(fd_w, R.encode() + b'\0')

    os.close(fd1_r)
    os.close(fd_w)

    sys.exit(0)

# ---------- PÈRE ----------
else:
    os.close(fd_w)

    # lire le mot envoyé par le fils
    bufferW = os.read(fd_r, 50).decode().strip('\x00')

    print(f"je suis le nouveau /{bufferW}/")

    check = -1

    try:
        with open("text.txt", "r") as fp:
            for mot in fp.read().split():
                if mot == bufferW:
                    print("mot trouvé")
                    check = 1
                    break
    except FileNotFoundError:
        print("erreur d'ouverture du fichier !!")
        sys.exit(1)

    os.close(fd1_r)

    # envoyer le résultat au fils
    os.write(fd1_w, check.to_bytes(4, byteorder='little', signed=True))

    os.close(fd_r)
    os.close(fd1_w)

    os.wait()
