example.cc: adaptation from https://github.com/grimme-lab/xtb/blob/main/test/api/c_api_example.c
example.out: result from calculation

test-angstrom: start with xtb binary and Angstroms
test-bohr: start with xtb-binary and Bohrs
(point charges are always in Bohr)
xtb.sh: execute calculation
clean.sh: clean up temporary files
