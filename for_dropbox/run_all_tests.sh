#!/bin/sh

nfails=0
nsuccess=0
ntests=0

for testfile in *.cminor
do
	if ./cminor -typecheck $testfile > $testfile.out
	then
		echo "$testfile success (as expected)"
        nsuccess=$((nsuccess+1))
	else
		echo "$testfile failure (INCORRECT)"
        nfails=$((nfails+1))
	fi
    ntests=$((ntests+1))
done

rm *.out

echo Successes: $nsuccess/$ntests
echo Failed tests: $nfails/$ntests
