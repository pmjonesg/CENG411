#!/bin/bash
# File: tScript.sh
# Course: CENG411
# Author: Peter Jones
# Date: Thursday Feb 02/27/14, 2014   02:13 AM

echo "Testing --all flag"
lss --all
echo ""
echo "Testing -a flag"
lss -a
echo ""
echo "Testing -i flag"
lss -i
echo ""
echo "Testing -L flag"
lss -L
echo ""
echo "Testing -s flag"
lss -s
echo ""
echo "Testing -F flag"
lss -F lss
lss -F direct
lss -F lss.c
echo ""
echo "Testing missing arguments"
lss -F 
echo ""
echo "Testing no flags"
lss
echo ""
echo "Testing -P flag"
lss -P octal
lss -P symbolic
echo ""
echo "Testing --minSize flag"
lss --minSize 9000
echo ""
echo "Testing --maxSize flag"
lss --maxSize 9000
echo ""
