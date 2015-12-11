# -*- coding:utf-8 -*-

import os
import random

f_name = "smallpoint.csv"
amount = 10
height = 100
width = 100
	
if os.path.exists(f_name):
	print "Exists"
else:
	f = open(f_name, 'w')
	for x in xrange(1,amount+1):
		f.write(str(x) + "," + str(random.randint(0, width)) + "," + str(random.randint(0, height)) + "\n")
print "finish"
