#!/usr/bin/env python2
# -*- coding: utf-8 -*-

i = 0
data = []

for line in open('dataRateTotal.txt'):
    data.append(float(line))
    i = i + 1

import matplotlib.pyplot as plt
y1 = plt.plot([1,2,3,4,5,6,7,8,9,10], data[0:10], 'r-+', label='1 Mbps' )
y2 = plt.plot([1,2,3,4,5,6,7,8,9,10], data[10:20], 'g-+', label='2 Mbps' )
y3 = plt.plot([1,2,3,4,5,6,7,8,9,10], data[20:30], 'b-+', label='5.5 Mbps' )
y4 = plt.plot([1,2,3,4,5,6,7,8,9,10], data[30:40], 'y-+', label='11 Mbps' )
plt.ylabel('Throughput (kbps)')
plt.xlabel('Number of Nodes')
plt.legend()
plt.title("Data Rate vs (total) Throughput")
plt.show()