#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import os

# Erase file
open('distanceStandingTotal.txt', 'w').close()
open('distanceMovingTotal.txt', 'w').close()

# Run the experiments
print 'executing Distance experiment...'
os.chdir("..");
for x in range(1, 11):
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --movingNodes=false --initialRadius=60 --fileName='distanceStandingTotal.txt'\"")
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --movingNodes=true  --initialRadius=60 --fileName='distanceMovingTotal.txt'\"")

for x in range(1, 11):
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --movingNodes=false --initialRadius=65 --fileName='distanceStandingTotal.txt'\"")
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --movingNodes=true  --initialRadius=65 --fileName='distanceMovingTotal.txt'\"")

for x in range(1, 11):
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --movingNodes=false --initialRadius=70 --fileName='distanceStandingTotal.txt'\"")
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --movingNodes=true  --initialRadius=70 --fileName='distanceMovingTotal.txt'\"")

for x in range(1, 11):
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --movingNodes=false --initialRadius=75 --fileName='distanceStandingTotal.txt'\"")
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --movingNodes=true  --initialRadius=75 --fileName='distanceMovingTotal.txt'\"")

os.chdir("fkastelein")