import random 
import threading 
import time
import sys
	
x = 0
lock = threading.Lock()

def iteration(tab):
	while(1):
		sec = random.randint(1,3)
		with lock:
			new_tab = [(tab[i-1]+tab[i]+tab[i+1])/3	for i in range(1,99)]
			for i in range(1,99):
				tab[i] = new_tab[i-1]
		time.sleep(sec)

def afficher(tab):
	u = 0
	while(1):
		with lock:
			print(tab)
		print("fin tab:",u+1)
		time.sleep(4)
def main ():

	tab = [random.randint(0,100) for _ in range(100)]
	tab[0] = 0
	tab[-1] = 0


	t1 = threading.Thread(target=iteration, args=(tab,))
	t2 = threading.Thread(target=afficher, args=(tab,))

	t1.start()
	t2.start()

	t1.join()
	t2.join()

if __name__ == "__main__":
	main()
