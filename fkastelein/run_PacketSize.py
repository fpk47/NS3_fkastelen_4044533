#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import os

# Erase file
open('packetSizeTotal.txt', 'w').close()
open('packetSizePerNode.txt', 'w').close()

# Run the experiments
print 'executing PacketSize experiment...'
os.chdir("..");
for x in range(1, 11):
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=500 --mode=1 --dataRateSetting=11 --fileName='packetSizeTotal.txt'\"")
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=500 --mode=2 --dataRateSetting=11 --fileName='packetSizePerNode.txt'\"")

for x in range(1, 11):
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=1 --dataRateSetting=11 --fileName='packetSizeTotal.txt'\"")
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1024 --mode=2 --dataRateSetting=11 --fileName='packetSizePerNode.txt'\"")

for x in range(1, 11):
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1472 --mode=1 --dataRateSetting=11 --fileName='packetSizeTotal.txt'\"")
    os.system("./waf --run \"fkastelein_script --nWifi=" +str(x) + "  --packetSize=1472 --mode=2 --dataRateSetting=11 --fileName='packetSizePerNode.txt'\"")

os.chdir("fkastelein")