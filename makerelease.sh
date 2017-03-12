#!/usr/bin/env bash

a=""
b=""
c=""
p=""
d=""
doxygen=""

# reading until not empty

while [ -z $a ]
do
	echo -n "Major: " ; read a
done


while [ -z $b ]
do
	echo -n "Minor: " ; read b;
done


while [ -z $c ]
do
	echo -n "Revision: " ; read c;
done


while [ -z $p ]
do
	echo -n "Prerelease? (y/n): " ; read p;
done


while [ -z $d ]
do
	echo -n "Add date? (y/n): " ; read d;
done


while [ -z $doxygen ]
do
	echo -n "Clean make and add to the package doxygen doc? (y/n): " ; read doxygen;
done


mkdir -p releases
package_dir_name="ttmath-$a.$b.$c"
datestr=""


if [ $p = "y" -o $p = "Y" ]
then
	package_dir_name=${package_dir_name}.prerelease
fi

package_dir_name=${package_dir_name}-src

if [ $d = "y" -o $d = "Y" ]
then
	datestr=`/bin/date "+%G.%m.%d"`;
	package_dir_name=${package_dir_name}-$datestr
fi




dir="releases/"${package_dir_name}
package=${package_dir_name}.tar.gz


if [ -d $dir ]
then
	echo "Directory $dir exists! (exiting)";
	exit 1;
fi

if [ -f "releases/"${package} ] ; then
	echo "File releases/${package} exists! (exiting)"
	exit 1;
fi


mkdir $dir



if [ $doxygen = "y" -o $doxygen = "Y" ]
then

	echo "------------------------------------------------------"
	echo "creating doxygen doc"
	echo "------------------------------------------------------"

	rm -rf doc/doxygen
	doxygen doxygen.cfg

	cp -r doc $dir/
fi


echo "------------------------------------------------------"
echo "make clean in samples"
echo "------------------------------------------------------"

make -C samples clean 
make -C constgen clean


echo "------------------------------------------------------"
echo "making source package"
echo "------------------------------------------------------"

mkdir $dir/ttmath
mkdir $dir/samples
mkdir $dir/res

cp ttmath/*  $dir/ttmath/

cp samples/* $dir/samples/
# cmake is not ready yet (cmake will generate Makefile which overwrites our own one)
rm $dir/samples/CMakeLists.txt

cp COPYRIGHT         $dir/
cp README            $dir/
cp CHANGELOG         $dir/

cp res/ttmath_logo.svg	$dir/res/

cd releases
tar -czf $package ${package_dir_name}

echo "the package has been created to:" releases/${package}

exit 0

