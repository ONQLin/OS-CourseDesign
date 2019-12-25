#!/bin/bash

insmod ghost.ko
cat "#<ghost>\nghost\n#<ghost>" >> etc/modules