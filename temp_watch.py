import os
import csv
import time

with open('temp_record.csv','w') as f:
    writer=csv.writer(f,delimiter=',')
    writer.writerow(['time','temp','RAM'])
    
# Return RAM information (unit=kb) in a list                                       
# Index 0: total RAM                                                               
# Index 1: used RAM                                                                 
# Index 2: free RAM                                                                 
def getRAMinfo():
    p = os.popen('free')
    i = 0
    while 1:
        i = i + 1
        line = p.readline()
        if i==2:
            return(line.split()[1:4])
    
def getCPUtemperature():
    res = os.popen('vcgencmd measure_temp').readline()
    return(res.replace("temp=","").replace("'C\n",""))

def main(intermitten):
    while True:
        tm='{}.{}.{} {}:{}:{}'.format(
            time.localtime()[0],
            time.localtime()[1],
            time.localtime()[2],
            time.localtime()[3],
            time.localtime()[4],
            time.localtime()[5],
            )
        print(tm)
        cputemp=getCPUtemperature()
        print(cputemp)
        RAMusage=getRAMinfo()
        print(RAMusage)
        time.sleep(intermitten)
        with open('temp_record.csv','w+') as f:
            writer=csv.writer(f,delimiter=',')
            writer.writerow([tm,cputemp,str(RAMusage+'%')])
            
main(3)

    
    