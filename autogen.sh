#!/bin/bash
libtoolize
aclocal
autoheader
autoconf
automake --force-missing
