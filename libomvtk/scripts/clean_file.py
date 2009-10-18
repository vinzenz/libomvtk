#!/usr/bin/python

import sys

def apply( files ):
    for f in files:
        fd = open(f, 'r')
        data = fd.read()
        fd.close()
        fd = open(f, 'w')
        fd.write( data.replace('\r\n','\n').replace('\t','    ') )
        fd.close()

if len( sys.argv ) > 1:
    apply( sys.argv[1:] )
else:
    apply( [ f for f in sys.stdin.read().split('\n') if f != '' ] )
