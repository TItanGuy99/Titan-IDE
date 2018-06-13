#! /usr/bin/env python

import os, sys, string

def help():
	print "Usage: %s <filename>.kdelnk ..." % sys.argv[0]

if len(sys.argv) < 2:
	help()
	sys.exit()

for fn in sys.argv[1:]:
	print "Doing %s ..." % fn
	f = open(fn, 'r').readlines()

	if string.find(f[0], "# KDE Config") == 0:
		p = open(fn, 'w')
		p.writelines(f[1:])
		p.close()

	os.rename(fn, fn[:-6]+'desktop')
