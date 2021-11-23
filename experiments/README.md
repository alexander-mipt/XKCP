# Guide
## build
in src dir:
```
make generic64/libXKCP.so
```
it generates `libHKCP.so` and headers in new dir `./bin/generic64`
## Run sandbox example
```
cd experiments

g++ -I ../bin/generic64/libXKCP.so.headers/ sha-3.cpp -L../bin/generic64/ -lXKCP -Wl,-rpath,../bin/generic64/

./a.out
```

## Commit format
```
[<tag>] <do/fix/format/...> <smth>

Here comes detailed description of
commit changes in same manner.
Hackers.
```