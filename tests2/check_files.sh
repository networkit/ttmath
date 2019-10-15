#!/bin/sh

was_error=0

for expected in *.expected ; do

	out=`basename $expected .expected`.out
	
	if [ -f $out ] ; then
		diff -u $out $expected
		
		if [ `diff -u $out $expected | wc -l` -ne 0 ] ; then
			was_error=1
		fi
	else
		echo "there is no file: $out"
		was_error=1
	fi

done


if [ $was_error -eq 0 ] ; then
	echo "****************************************************************************"
	echo "             congratulations: all tests passed successfully"
	echo "****************************************************************************"
else
	echo "****************************************************************************"
	echo "             error: not all tests passed successfully"
	echo "****************************************************************************"
fi
