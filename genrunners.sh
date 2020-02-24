#!/bin/bash
make clean
for FL in test/*.c; do
	echo $FL
	ruby unity/auto/generate_test_runner.rb $FL;
done
make

#	ruby unity/auto/generate_test_runner.rb test/Testbaseset.c;
#	make