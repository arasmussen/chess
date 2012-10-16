#! /bin/bash

BUILD_DIR=${CPP_CHESS_ROOT}/bin

for folder in `ls -d unitTests/*`; do
  testCase=`basename ${folder}`

  ./runTest.sh ${testCase}
done

