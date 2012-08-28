#! /bin/bash

BUILD_DIR=${CHESS_ROOT}/bin

for folder in `ls -d unitTests/*`; do
	testCase=`basename ${folder}`

	${BUILD_DIR}/runUnitTest "${BUILD_DIR}/algorithm ${folder}/white.in ${$}.white.out" "${BUILD_DIR}/algorithm ${folder}/black.in ${$}.black.out"
	if [ ${?} -ne 0 ]; then
		echo "Runtime Error: ${testCase}"
		break;
	fi

	diff ${$}.white.out ${folder}/white.out
	if [ ${?} -ne 0 ]; then
			echo "WHITE TEST CASE FAILED: ${testCase}"
			break;
	fi

	diff ${$}.black.out ${folder}/black.out
	if [ ${?} -ne 0 ]; then
			echo "BLACK TEST CASE FAILED: ${testCase}"
			break;
	fi

	echo "${testCase} - PASSED" 
done

if [ -e ${$}.white.out ]; then
	rm ${$}.white.out
fi

if [ -e ${$}.black.out ]; then
	rm ${$}.black.out
fi
