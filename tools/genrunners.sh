#!/bin/bash
`make test_clean`
for FL in test/*.c; do
	echo "Generating Runner for " $FL
	ruby unity/auto/generate_test_runner.rb $FL;
done

#	ruby unity/auto/generate_test_runner.rb test/Testbaseset.c;
#	make