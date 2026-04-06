import threading 
import random

class type_tab:
	def __init__(self,n):
		self.tab1 = [0] * 2
		self.tab2 = [0] * 20
		self.n = n
		self.x = None
		
def rechercher(obj):
	#for i in range(10):
	for j in range(2):
		if obj.tab1[j] in obj.tab2:
			continue
		else:
			print("T1 n'est pss inclut dans T2..")
			exit(0)
	print("T1 inclut T2")

	print("T1 est inclus dans T2..")
def genere_tab(obj):
	obj.tab1 = [random.randint(0,40) for _ in range(2)]
	obj.tab2 = [random.randint(0,40) for _ in range(20)]
	print("1:", obj.tab1)
	print("2:", obj.tab2)
	print("tableau generée..");

def main():
	n = int(input("entrez la taille du tableau "))
	
	obj = type_tab(n)
	t1 = threading.Thread(target=genere_tab, args=(obj,))
	t1.start()

	#obj.x = int(input("donner x : "))
	t1.join()
	
	t2 = threading.Thread(target=rechercher, args=(obj,))
	t2.start()
	t2.join()

if __name__ == "__main__":
	main()
