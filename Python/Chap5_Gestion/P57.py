import random 
import threading 
import time
import sys
comp = 0	
u = 1
lock = threading.Lock()

def iteration():
	global u, comp
	while(1):
		sec = random.randint(1,5)
		with lock:
			u = (u-1)*(u-1)/4
			comp+=1
			print("(i=",comp,")dans T1 = ", u)
		time.sleep(sec)

def afficher():
	global u, comp
	while(1):
		with lock:
			u = (u-2)*(u-2)/6
			comp+=1
			print("(i=", comp,")dans T2 :",u)
		time.sleep(random.randint(1,5))
def main ():
	global u
	u = 1


	t1 = threading.Thread(target=iteration)
	t2 = threading.Thread(target=afficher)

	t1.start()
	t2.start()

	t1.join()
	t2.join()

if __name__ == "__main__":
	main()
