BUILD_DIR=${CPP_CHESS_ROOT}/bin

testCase=${1}
folder=`find -name ${testCase}`

cleanup() {
  if [ -e ${$}.white.out ]; then
    rm ${$}.white.out
  fi

  if [ -e ${$}.black.out ]; then
    rm ${$}.black.out
  fi
}

fail() {
  echo "TEST CASE FAILED: ${testCase}"

  echo "White - Expected: "
  cat ${folder}/white.out

  echo "White - Given:"
  cat ${$}.white.out

  echo "Black - Expected: "
  cat ${folder}/black.out

  echo "Black - Given:"
  cat ${$}.black.out

  cleanup
  exit 1
}

${BUILD_DIR}/runUnitTest "${BUILD_DIR}/algorithm ${folder}/white.in ${$}.white.out" "${BUILD_DIR}/algorithm ${folder}/black.in ${$}.black.out"
if [ ${?} -ne 0 ]; then
  echo "Runtime Error: ${testCase}"
  cleanup
  exit 1
fi

diff ${$}.white.out ${folder}/white.out > /dev/null
if [ ${?} -ne 0 ]; then
  fail
fi

diff ${$}.black.out ${folder}/black.out > /dev/null
if [ ${?} -ne 0 ]; then
  fail
fi

echo "${testCase} - PASSED" 
cleanup
