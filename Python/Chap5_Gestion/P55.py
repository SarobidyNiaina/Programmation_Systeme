import random 
import threading 
import time
import sys
	
x = 0
lock = threading.Lock()

def iteration():
	global x
	while(1):
		sec = random.randint(1,5);
		#global x
		time.sleep(sec)
		with lock:
			x += 1
		a = int(sys.argv[1])
		if x == a:
			exit(0)
		#time.sleep(sec)
	
def afficher():
	global x
	while(1):
		time.sleep(2)
		print("rapport T2 : ", x)
		a = int(sys.argv[1])
		if x == a:
			exit(0)
		#time.sleep(sec)

def main ():
	t1 = threading.Thread(target=iteration)
	t2 = threading.Thread(target=afficher)
	
	t1.start()
	t2.start()
	
	t2.join()
	t2.join()

if __name__ == "__main__":
	main()
