import os
import csv
import time
import sys
from getopt import getopt

if os.path.isfile('temp_record.csv'):
    pass
else:
    with open('temp_record.csv', 'w') as f:
            writer = csv.writer(f, delimiter=',')
            writer.writerow(['time', 'temp', 'RAM'])


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
        if i == 2:
            raws = line.split()[1:4]
            for i in range(len(raws)):
                raws[i] = int(raws[i])
            return raws[1] / raws[0]


def getCPUtemperature():
    res = os.popen('vcgencmd measure_temp').readline()
    return (res.replace("temp=", "").replace("'C\n", ""))


def main(intermitten,is_print):
    while True:
        tm = '{}.{}.{} {}:{}:{}'.format(
            time.localtime()[0],
            time.localtime()[1],
            time.localtime()[2],
            time.localtime()[3],
            time.localtime()[4],
            time.localtime()[5],
        )
        cputemp = getCPUtemperature()
        RAMusage = getRAMinfo()
        if is_print is True:
            print('time {} temp {} RAMusage {} '.format(tm,cputemp,'%.0f%%'%(RAMusage*100)))
        time.sleep(intermitten)
        with open('temp_record.csv', 'a+') as f:
            writer = csv.writer(f, delimiter=',')
            writer.writerow([tm, cputemp, '%.0f%%'%(RAMusage*100)])


if __name__=="__main__":
    try:
        opts,args=getopt(sys.argv[1:],'hpt:',['help'])
    except getopt.GetoptError:
        is_print = True
        intermitten = 15
        print('args not found,runs in default mode')
        print('Commands:python temp_watch.py [-t time] [-p] ')
    else:
        if opts is not None:
            is_print=True
            intermitten=15
        for opt in opts:
            if opt[0] == '-p':
                is_print = True
            elif opt[0] == '-t':
                intermitten = int(opt[1])
            elif opt[0] in ('-h','--help'):
		print('display and record Cpu tempature and RAM use percent at certain time interval')
		print('python temp_watch.py [-p] [-t] <interval>')
		sys.exit(0)
        
    main(intermitten,is_print)
