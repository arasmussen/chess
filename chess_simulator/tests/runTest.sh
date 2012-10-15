BUILD_DIR=${CHESS_ROOT}/bin

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

${BUILD_DIR}/runUnitTest "${BUILD_DIR}/algorithm ${folder}/white.in ${$}.white.out" "${BUILD_DIR}/algorithm ${folder}/black.in ${$}.black.out"
if [ ${?} -ne 0 ]; then
  echo "Runtime Error: ${testCase}"
  cleanup
  exit 1
fi

diff ${$}.white.out ${folder}/white.out
if [ ${?} -ne 0 ]; then
  echo "WHITE TEST CASE FAILED: ${testCase}"
  cleanup
  exit 1
fi

diff ${$}.black.out ${folder}/black.out
if [ ${?} -ne 0 ]; then
  echo "BLACK TEST CASE FAILED: ${testCase}"
  cleanup
  exit 1
fi

echo "${testCase} - PASSED" 
cleanup
