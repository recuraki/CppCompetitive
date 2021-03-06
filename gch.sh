#!/bin/bash -x

BASEDIR=/usr/include/x86_64-linux-gnu/c++/7/bits/

echo host
echo $HOST
if test "$HOSTNAME" = "UG020-kanai-MBP13-01.local"; then
echo "OSX MODE"
BASEDIR=/usr/local/include/bits/
fi

if test ! -f "$BASEDIR/stdc++.h"; then
 BASEDIR=/usr/include/x86_64-linux-gnu/c++/9/bits/
fi

GCHDIR=$BASEDIR/stdc++.h.gch/


mkdir -p $GCHDIR

DEBUG_OPTION='-std=c++17 -O0 -g -Wall -fsanitize=undefined -Wno-deprecated -Wno-unneeded-internal-declaration'
DEBUG2_OPTION=''
RELEASE_OPTION=''

STDH=$BASEDIR/stdc++.h

echo default.gch
g++ $STDH -o $GCHDIR/default.gch
echo debug.gch
g++ $DEBUG_OPTION $STDH -o $GCHDIR/default-debug.gch
echo release
g++ $RELEASE_OPTION $STDH -o $GCHDIR/default-release.gch
echo debug14
g++ -std=c++14 $DEBUG_OPTION $STDH -o $GCHDIR/c++14-debug.gch
echo release14
g++ -std=c++14 $RELEASE_OPTION $STDH -o $GCHDIR/c++14-release.gch
echo debug17
g++ -std=c++17 $DEBUG_OPTION $STDH -o $GCHDIR/c++17-debug.gch
echo debug17
g++ -std=c++17 $RELEASE_OPTION $STDH -o $GCHDIR/c++17-release.gch

echo "finish!"
