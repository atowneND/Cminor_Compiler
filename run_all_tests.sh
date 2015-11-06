#!/bin/sh

nfails=0
nsuccess=0
ntests=0

for testfile in ptests/good*.cminor
do
	if ./cminor -parse $testfile > $testfile.out
	then
		echo "$testfile success (as expected)"
        nsuccess=$((nsuccess+1))
	else
		echo "$testfile failure (INCORRECT)"
        nfails=$((nfails+1))
	fi
    ntests=$((ntests+1))
done

for testfile in ptests/bad*.cminor
do
	if ./cminor -parse $testfile > $testfile.out
	then
		echo "$testfile success (INCORRECT)"
        nfails=$((nfails+1))
	else
		echo "$testfile failure (as expected)"
        nsuccess=$((nsuccess+1))
	fi
    ntests=$((ntests+1))
done
echo Successes: $nsuccess/$ntests
echo Failed tests: $nfails/$ntests
