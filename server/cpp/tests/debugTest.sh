#!/bin/bash

BUILD_DIR=${CPP_CHESS_ROOT}/bin

testCase=${1}
folder=`find -name ${testCase}`

(echo "handle SIGPIPE nostop" ; echo "run \"${BUILD_DIR}/algorithm ${folder}/white.in ${$}.white.out\" \"${BUILD_DIR}/algorithm ${folder}/black.in ${$}.black.out\" "; cat) \
  | gdb ${BUILD_DIR}/runUnitTest 

rm ${$}.white.out
rm ${$}.black.out
