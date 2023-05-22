'''
bash test - back to previous line, clear line
----------------
Sanghoon Lee (canplane@gmail.com)
2021-11-03
'''

import time
import sys 

for i in range(10):
    print(f"\r{i}", end="", flush=True)
    time.sleep(.25)
print("")

print("FAILED...")
print("foo", end="", flush=True)
time.sleep(.50)
sys.stdout.write("\033[F") #back to previous line
sys.stdout.write("\033[F") #back to previous line
sys.stdout.write("\033[K") #clear line 
print("SUCCESS!") 