### Tests execution flow is folowing:
- create strings in hex format to get hashes of
```randomness_test/generate_input_for_nist$ python3 generate_low_high_rand_inputs.py```
- calculate sha3 in different configurations using this inputs
```randomness_test/generate_input_for_nist$ ./generate_low_high_rand_outputs.sh```
- wait about 20 minutes
- compile statistical test suite
```sudo apt install libfftw3-dev``` - need to sts compilation
```randomness_test/sts$ make```
- run sts and write results to csv file
```randomness_test/sts$ python3 collect_results.py```
- wait about 1.5 - 2 hours (on 12 threads ryzen 2600)
