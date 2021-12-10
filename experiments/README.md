# sha-3 tests
## sha-3 generator
```
./sha3gen_build.sh
```
see help:
```
./sha3gen.out
```

example:
```bash
alexander@alexander-Inspiron-3180:~/GitHub/XKCP/experiments$ ./sha3gen.out 'abcd' 224 
sha-224 input[4]        abcd
dev sha-224
dd886b5fd8421fb3871d24e39e53967ce4fc80dd348bedbea0109c0e
fips202 sha-224
dd886b5fd8421fb3871d24e39e53967ce4fc80dd348bedbea0109c0e
fips202 sha-224
dd886b5fd8421fb3871d24e39e53967ce4fc80dd348bedbea0109c0e
```
## sha-3 avalanche test stat
```
./avalanche_effect_build.sh
```

see help:
```
./avalanche_input.py
./avalanche_test.out
```

run example:
```
./avalanche_input.py 100 8 100 4
./avalanche_test.out 224 24 1
```

`224 24 1` means:
* use 224 bits hash
* use 24 round keccak
* use `0x01` as init state of LFSR generator

output examples on diff count of rounds:
```bash
alexander@alexander-Inspiron-3180:~/GitHub/XKCP/experiments$ ./avalanche_input.py 8 2 32 4
Namespace(blockSizeLim=8, lenStep=4, maxLen=32, minLen=2, seed=1)
alexander@alexander-Inspiron-3180:~/GitHub/XKCP/experiments$ ./avalanche_test.out 224 24 1
Avalanche test
        Args: <hash_size> <num_rounds> <LSFR_state>
        if LSFR_state < 0 then exclude l-permutation

hash_size: 224 rounds: 24 LSFR[1] 1

    56              56    0.5069        |
alexander@alexander-Inspiron-3180:~/GitHub/XKCP/experiments$ ./avalanche_test.out 224 6 1
Avalanche test
        Args: <hash_size> <num_rounds> <LSFR_state>
        if LSFR_state < 0 then exclude l-permutation

hash_size: 224 rounds: 6 LSFR[1] 1

    56              56    0.4946        |
alexander@alexander-Inspiron-3180:~/GitHub/XKCP/experiments$ ./avalanche_test.out 224 4 1
Avalanche test
        Args: <hash_size> <num_rounds> <LSFR_state>
        if LSFR_state < 0 then exclude l-permutation

hash_size: 224 rounds: 4 LSFR[1] 1

    56              56    0.5029        |
alexander@alexander-Inspiron-3180:~/GitHub/XKCP/experiments$ ./avalanche_test.out 224 3 1
Avalanche test
        Args: <hash_size> <num_rounds> <LSFR_state>
        if LSFR_state < 0 then exclude l-permutation

hash_size: 224 rounds: 3 LSFR[1] 1

    56              56    0.5018        |
alexander@alexander-Inspiron-3180:~/GitHub/XKCP/experiments$ ./avalanche_test.out 224 2 1
Avalanche test
        Args: <hash_size> <num_rounds> <LSFR_state>
        if LSFR_state < 0 then exclude l-permutation

hash_size: 224 rounds: 2 LSFR[1] 1

    56              56    0.4882        |
alexander@alexander-Inspiron-3180:~/GitHub/XKCP/experiments$ ./avalanche_test.out 224 1 1
Avalanche test
        Args: <hash_size> <num_rounds> <LSFR_state>
        if LSFR_state < 0 then exclude l-permutation

hash_size: 224 rounds: 1 LSFR[1] 1

    56              56    0.4020        |
alexander@alexander-Inspiron-3180:~/GitHub/XKCP/experiments$ 
```

last num means average % of bit changes

output files:
* `avalanche_stat.log`
* `hash_output.log`

examples:
```
avalanche_stat.log:
   Idx	InLenBits	  Itrs	   Mod	|	       ModPerBit (224 bits)
     1	     2	     1	  0.0179	|	
     2	     2	     1	  0.0357	|	
     3	     2	     1	  0.0580	|	
     4	     2	     1	  0.0804	|	
     5	     2	     1	  0.0982	|	
     6	     2	     1	  0.1116	|	
     7	     2	     1	  0.1295	|	
     8	     6	     1	  0.2857	|	
     9	     6	     1	  0.2991	|	
    10	     6	     1	  0.3214	|	
    11	     6	     1	  0.3438	|	
    12	     6	     1	  0.3571	|	
    13	     6	     1	  0.3705	|	
    14	     6	     1	  0.3884	|	
    15	    10	     1	  0.3750	|	
    16	    10	     1	  0.3705	|	
    17	    10	     1	  0.3884	|	
    18	    10	     1	  0.3884	|	
    19	    10	     1	  0.4018	|	
    20	    10	     1	  0.4152	|	
    21	    10	     1	  0.4152	|	
    22	    14	     1	  0.4375	|	
    23	    14	     1	  0.4420	|	
    24	    14	     1	  0.4509	|	
    25	    14	     1	  0.4598	|	
    26	    14	     1	  0.4509	|	
    27	    14	     1	  0.4643	|	
    28	    14	     1	  0.4688	|	
    29	    18	     1	  0.4866	|	
    30	    18	     1	  0.4911	|	
    31	    18	     1	  0.5000	|	
    32	    18	     1	  0.5000	|	
    33	    18	     1	  0.4911	|	
    34	    18	     1	  0.5045	|	
    35	    18	     1	  0.5000	|	
    36	    22	     1	  0.4866	|	
    37	    22	     1	  0.4821	|	
    38	    22	     1	  0.4821	|	
    39	    22	     1	  0.4821	|	
    40	    22	     1	  0.4732	|	
    41	    22	     1	  0.4866	|	
    42	    22	     1	  0.5000	|	
    43	    26	     1	  0.5000	|	
    44	    26	     1	  0.4866	|	
    45	    26	     1	  0.5045	|	
    46	    26	     1	  0.4955	|	
    47	    26	     1	  0.4911	|	
    48	    26	     1	  0.5000	|	
    49	    26	     1	  0.5000	|	
    50	    30	     1	  0.4732	|	
    51	    30	     1	  0.4688	|	
    52	    30	     1	  0.4866	|	
    53	    30	     1	  0.4777	|	
    54	    30	     1	  0.4732	|	
    55	    30	     1	  0.4821	|	
    56	    30	     1	  0.4821	|	
    56	      	    56	  0.4020	|	  1.0000   0.5000   0.7143   0.5000   0.5179   0.2857   0.5893   0.7500   0.6250   0.0000   0.6250   0.0000   0.5000   0.0000   0.5000   0.7500   0.0000   0.0000   0.6250   0.5000   0.0000   0.6250   0.8750   0.6250   0.0000   0.2500   0.2500   0.2500   0.1250   0.3750   0.3750   0.2500   0.5000   0.6250   0.6250   0.2500   0.2500   0.3750   0.3750   0.6250   0.0000   0.3750   0.0000   0.3750   0.8750   0.2321   0.4286   0.4821   0.3571   0.2679   0.4643   0.6250   0.5000   0.5000   0.5000   0.5000   0.2500   0.2500   0.0000   0.5000   0.5000   0.2500   0.7500   0.0000   0.0000   0.3750   0.8750   0.3750   0.0000   0.8750   0.7500   0.7500   0.0000   0.7500   0.5000   0.1250   0.0000   0.8750   0.3750   0.6250   0.8750   0.7500   0.6250   0.3750   0.0000   0.3750   0.3750   0.5000   0.7500   0.8750   0.5000   0.1250   0.0000   0.3750   0.5000   0.3750   0.0000   0.2500   0.7500   0.2500   0.0000   0.0000   0.0000   0.2500   0.7500   0.2500   0.5000   0.2500   1.0000   0.8571   0.6607   0.5000   0.5000   0.2857   0.4107   0.1250   0.0000   0.0000   0.1250   0.0000   0.5000   0.5000   0.1250   0.1250   0.0000   0.2500   0.3750   0.3750   0.2500   0.6250   0.6250   0.6250   0.6250   0.3750   0.1250   0.5000   0.6250   0.5000   0.1250   0.5000   0.5000   0.2500   0.5000   1.0000   0.7679   0.5000   0.5536   0.6250   0.0000   0.2321   0.0000   0.3750   0.2500   0.5000   0.1250   0.5000   0.3750   0.2500   0.3750   0.2500   0.0000   0.0000   0.8750   0.0000   0.1250   0.7500   0.5000   0.0000   0.7500   0.7500   0.8750   0.7500   0.7500   0.1250   0.2500   0.1250   0.2500   0.5000   0.7500   0.5000   0.2500   0.6250   0.2500   0.1250   0.5000   0.6250   0.7500   0.5000   0.2500   0.6250   0.1250   0.5000   1.0000   0.3393   0.9286   0.5179   0.4286   0.5714   0.4107   0.3750   0.0000   0.2500   0.7500   0.2500   0.0000   0.0000   0.7500   0.5000   0.0000   0.7143   0.6429   0.4286   0.0000   0.0893   0.8750   0.2500   0.5000   0.2500   0.7500   0.5000   0.0000   0.0000   0.2500   0.3750 


```
```
avalanche_input.txt:

gS
fS
dS
`S
hS
xS
XS
S
gSNnzx
fSNnzx
dSNnzx
`SNnzx
hSNnzx
xSNnzx
XSNnzx
SNnzx
gSNnzxHPeb
fSNnzxHPeb
dSNnzxHPeb
`SNnzxHPeb
hSNnzxHPeb
xSNnzxHPeb
XSNnzxHPeb
SNnzxHPeb
gSNnzxHPebRwNa
fSNnzxHPebRwNa
dSNnzxHPebRwNa
`SNnzxHPebRwNa
hSNnzxHPebRwNa
xSNnzxHPebRwNa
XSNnzxHPebRwNa
SNnzxHPebRwNa
gSNnzxHPebRwNaxLlX
fSNnzxHPebRwNaxLlX
dSNnzxHPebRwNaxLlX
`SNnzxHPebRwNaxLlX
hSNnzxHPebRwNaxLlX
xSNnzxHPebRwNaxLlX
XSNnzxHPebRwNaxLlX
SNnzxHPebRwNaxLlX
gSNnzxHPebRwNaxLlXUbbC
fSNnzxHPebRwNaxLlXUbbC
dSNnzxHPebRwNaxLlXUbbC
`SNnzxHPebRwNaxLlXUbbC
hSNnzxHPebRwNaxLlXUbbC
xSNnzxHPebRwNaxLlXUbbC
XSNnzxHPebRwNaxLlXUbbC
SNnzxHPebRwNaxLlXUbbC
gSNnzxHPebRwNaxLlXUbbCWtlv
fSNnzxHPebRwNaxLlXUbbCWtlv
dSNnzxHPebRwNaxLlXUbbCWtlv
`SNnzxHPebRwNaxLlXUbbCWtlv
hSNnzxHPebRwNaxLlXUbbCWtlv
xSNnzxHPebRwNaxLlXUbbCWtlv
XSNnzxHPebRwNaxLlXUbbCWtlv
SNnzxHPebRwNaxLlXUbbCWtlv
gSNnzxHPebRwNaxLlXUbbCWtlvblwz
fSNnzxHPebRwNaxLlXUbbCWtlvblwz
dSNnzxHPebRwNaxLlXUbbCWtlvblwz
`SNnzxHPebRwNaxLlXUbbCWtlvblwz
hSNnzxHPebRwNaxLlXUbbCWtlvblwz
xSNnzxHPebRwNaxLlXUbbCWtlvblwz
XSNnzxHPebRwNaxLlXUbbCWtlvblwz
SNnzxHPebRwNaxLlXUbbCWtlvblwz
```

```
hash_output.log:

665306000000000000001000006036650080a3290300000067531400
675306000000000000001000007036650000a3290300000066531400
655306000000000000001000005036650000a2290300000064531400
615306000000000000001000001036650000a0290300000060531600
695306000000000000001000009036650000a4290300000068531200
795306000000000000001000009037650000ac290300000078531200
595306000000000000001000009035650000ac290300000058531200
1953060000000000000010000090316500008c290300000018531200
66534e6e7a780600e4a69767006036e50380a32927373d3c64535c46
67534e6e7a780600e4a69767007036e50300a32927373d3c64535c46
65534e6e7a780600e4a69767005036e50300a22927373d3c64535c46
61534e6e7a780600e4a69767001036e50300a02927373d3c60535e46
69534e6e7a780600e4a69767009036e50300a42927373d3c68535a46
79534e6e7a780600e4a69767009037e50300ac2927373d3c78535246
59534e6e7a780600e4a69767009035e50300ac2927373d3c58535246
19534e6e7a780600e4a69767009031e503008c2927373d3c18535246
ac97426e7a704942e4a69787046536e524a8a329271f2e0f89175046
ad97426e7a704942e4a69787047536e52428a329271f2e0f88975046
af97426e7a504942e4a69787045536e52428a229271f2e0f8a975046
ab97426e7a504942e4a69787041536e52428a029271f2e0f8a975246
a397426e7a504942e4a69787049536e52428a429271f2e0f82975246
b397426e7a504842e4a69787049537e52428ac29271f2e0f92975246
9397426e7a504a42e4a69787049535e52428ac29271f2e0f92975246
d397426e7a504a42e4a69787049531e524288c29271f2e0fd2975246
b6c6e2b0e6b24542e4a69787046536e59edba91a271f2eaf89175880
b7c6e2b0e6b24542e4a69787047536e59e5ba91a271f2eaf88975880
b5c6e2b0e6924542e4a69787045536e59e5ba81a271f2eaf8a975880
b1c6e2b0e6924542e4a69787041536e59e5baa1a271f2eaf8a975a80
b9c6e2b0e6924542e4a69787049536e59e5bae1a271f2eaf82975a80
a9c6e2b0e6924442e4a69787049537e59e5ba61a271f2eaf92975280
89c6e2b0e6924642e4a69787049535e59e5ba61a271f2eaf92975280
c9c6e2b0e6924642e4a69787049531e59e5b861a271f2eafd2977280
b6c6e2c085b0b859e4a6178b8ce53b2e9edb29e3471d2eaf8917d88d
b7c6e2c085b0b859e4a6178b8cf53b2e9e5b29e3471d2eaf8897d88d
b5c6e2c08590b859e4a6178b8cd53b2e9e5b28e3471d2eaf8a97d88d
b1c6e2c08590b859e4a6178b8c953b2e9e5b2ae3471d2eaf8a97da8d
b9c6e2c08590b859e4a6178b8c153b2e9e5b2ee3471d2eaf8297da8d
a9c6e2c08590b959e4a6178b8c153a2e9e5b26e3471d2eaf9297d28d
89c6e2c08590bb59e4a6178b8c15382e9e5b26e3471d2eaf9297d28d
c9c6e2c08590bb59e4a6178b8c153c2e9e5b06e3471d2eafd297f28d
bc86ea0085b0b859eeea7b438ca577229edb29e3671f22834117d88d
bd86ea0085b0b859eeea7b438cb577229e5b29e3671f22834097d88d
bf86ea008590b859eeea7b438c9577229e5b28e3671f22834297d88d
bb86ea008590b859eeea7b438cd577229e5b2ae3671f22834297da8d
b386ea008590b859eeea7b438c5577229e5b2ee3671f22834a97da8d
a386ea008590b959eeea7b438c5576229e5b26e3671f22835a97d28d
8386ea008590bb59eeea7b438c5574229e5b26e3671f22835a97d28d
c386ea008590bb59eeea7b438c5570229e5b06e3671f22831a97f28d
bc86ea0087bafc78ee627f6306eb3346be532a7367df44e4619d5c0d
bd86ea0087bafc78ee627f6306fb3346be532a7367df44e4601d5c0d
bf86ea00879afc78ee627f6306db3346be532b7367df44e4621d5c0d
bb86ea0087dafc78ee627f63069b3346be532b7367df44e4621d5e0d
b386ea00875afc78ee627f63061b3346be532b7367df44e46a1d5e0d
a386ea00875afd78ee627f63061b3246be532b7367df44e47a1d560d
8386ea00875afd78ee627f63061b3046be532b7367df44e47a1d560d
c386ea00875af978ee627f63061b3446be530b7367df44e43a1d760d
fc92ee0087bafc782e60f96606eb330679258d14774ed536609d5c0d
fd92ee0087bafc782e60f96606fb330679258d14774ed536601d5c0d
ff92ee00879afc782e60f96606db330679258c14774ed536621d5c0d
fb92ee0087dafc782e60f966069b330679258c14774ed536621d5e0d
f392ee00875afc782e60f966061b330679258c14774ed5366a1d5e0d
e392ee00875afd782e60f966061b320679258c14774ed5367a1d560d
c392ee00875afd782e60f966061b300679258c14774ed5367a1d560d
8392ee00875af9782e60f966061b34067925ac14774ed5363a1d760d

```