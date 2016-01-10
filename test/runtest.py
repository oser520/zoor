#!/usr/bin/env python
# file: runtest.py
# author: Omar A Serrano
# author: 2016-01-09
#
# Runs the unit tests.

import sys
import subprocess

if __name__ == '__main__':
    if len(sys.argv) == 1:
	sys.exit(0)
    for test in sys.argv[1:]:
	print "Running Unit Tests for %s" % test
	subprocess.call(["./"+test])
	print "Unit Tests for %s Finished!" % test
    sys.exit(0)
