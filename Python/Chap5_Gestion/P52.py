import threading 
import random 

def afficher_tab( t ):
	print("tableau reçu : ");	
	for x in t:
		print(x, end=" ")
		print( )
def main():
	#tab = [0]*5
	#for i in range(5):
	#	tab[i] = random.randint(0, 100)
	tab = [ random.randint(0,99) for  _ in range(5)]
	print(tab)
	t = threading.Thread(target=afficher_tab, args=(tab,))
	t.start()
	t.join()

	print("fin du programme principal")

if __name__=="__main__":
	main()
