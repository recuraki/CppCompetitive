#!/bin/bash -x
BASEDIR=/usr/include/x86_64-linux-gnu/c++/9/bits/
# システムディレクトリに書き込みたいのでrootを必要とする
if test "`id -u`" -ne 0; then echo PLZ sudo;  exit 1; fi
# プリコンパイル済みヘッダは完全に同じg++オプションの時しか有効にならない
# 私の場合は、aliasで使うDEBUGか、g++ main.cppなどオプションなししか使わない
DEBUG_OPTION='-std=c++17 -O0 -g -Wall -fsanitize=undefined -Wno-deprecated -Wno-unneeded-internal-declaration'
DEBUG_OPTION='-std=c++17 -O0 -g -Wall -fsanitize=undefined -fsanitize-undefined-trap-on-error -Wno-deprecated -Wno-unneeded-internal-declaration '
RELEASE_OPTION=''

# OSX用のディレクトリにする(自分の環境の場合)
if test "$(uname)" == 'Darwin' ; then
 echo "OSX MODE"
 BASEDIR=/usr/local/include/bits/
 BASEDIR=/opt/homebrew/include/c++/11/aarch64-apple-darwin21/bits/
fi


mkdir -p $GCHDIR
# コンパイルするヘッダ
STDH=$BASEDIR/stdc++.h
# コンパイル済みのヘッダを書き込むディレクトリ
GCHDIR=$BASEDIR/stdc++.h.gch/

# includeされるディレクトリの中で合うオプションのコンパイル済みヘッダがあれば
# 勝手に使われるので、使いそうなやつを書いておく
# OPTIONでc++17を入れていると以下のc++14は意味ないので注意
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
