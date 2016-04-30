#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import os

# Erase file
open('dataRateTotal.txt', 'w').close()
open('dataRatePerNode.txt', 'w').close()

# Run the experiments
print 'executing DataRate experiment...'
os.chdir("..");
for x in range(1, 11):
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --dataRateSetting=1 --fileName='dataRateTotal.txt'\"")
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=2 --dataRateSetting=1 --fileName='dataRatePerNode.txt'\"")

for x in range(1, 11):
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --dataRateSetting=2 --fileName='dataRateTotal.txt'\"")
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=2 --dataRateSetting=2 --fileName='dataRatePerNode.txt'\"")

for x in range(1, 11):
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --dataRateSetting=5.5 --fileName='dataRateTotal.txt'\"")
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=2 --dataRateSetting=5.5 --fileName='dataRatePerNode.txt'\"")

for x in range(1, 11):
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --dataRateSetting=11 --fileName='dataRateTotal.txt'\"")
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=2 --dataRateSetting=11 --fileName='dataRatePerNode.txt'\"")


os.chdir("fkastelein")