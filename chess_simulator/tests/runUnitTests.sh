#! /bin/bash

BUILD_DIR=${CHESS_ROOT}/bin

for folder in `ls -d unitTests/*`; do
  testCase=`basename ${folder}`

  ./runTest.sh ${testCase}
done

