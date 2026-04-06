import threading 
import random

class type_tab:
	def __init__(self,n):
		self.tab = [0] * n
		self.n = n
		self.x = None
		
def rechercher(obj):
	if obj.x in obj.tab:
		print(1)
	else:
		print(0)
def genere_tab(obj):
	obj.tab = [random.randint(0,99) for _ in range(obj.n)]
	print(obj.tab)
	print("tableau generée..");

def main():
	n = int(input("entrez la taille du tableau "))
	
	obj = type_tab(n)
	t1 = threading.Thread(target=genere_tab, args=(obj,))
	t1.start()

	obj.x = int(input("donner x : "))
	t1.join()
	
	t2 = threading.Thread(target=rechercher, args=(obj,))
	t2.start()
	t2.join()

if __name__ == "__main__":
	main()
