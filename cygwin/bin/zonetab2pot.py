#!/usr/bin/env python
'''This script reads timezone list as its first argument
or from /usr/share/zoneinfo/zone.tab, and converts it
to a PO file template.

This is free software, released under GPL.
Author: Lukas Tinkl <lukas@kde.org>, 2002
'''

import sys
import fileinput
import string

def makePOT(_file):
  for line in fileinput.input(_file):
    if (line[0]=='#'): #skip comments
      continue
    section=string.split(string.strip(line), '\t')[2] #third field, tab separated
    newline='msgid \"' + section+ '\"\n' #msgid
    newline+='msgstr \"\"\n' #msgstr
    print(newline) #output to stdout

if __name__ == '__main__':
  makePOT(sys.argv[1:] or "/usr/share/zoneinfo/zone.tab")
