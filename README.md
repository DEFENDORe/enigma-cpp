# Enigma Machine C++

A simple library and CLI program to encode and decode text using the enigma cipher.

How an enigma machine works: 
https://www.youtube.com/watch?v=ybkkiGtJmkM


`Rotors: I, II, III, IV, V, VI, VII, VIII` 

`Rotor Position: A-Z, 0-25`

`Rotor Ring Setting: A-Z, 0-25`

`Reflectors: B, C`

---

Build:
```
make
```

Library: `/bin/enigma.a`

Run CLI: 
```
./bin/enigma-cli
```

### Examples
```
./bin/enigma-cli -r C -w I,A,A,II,A,A,III,A,A -p ab,cd
```

```
./bin/enigma-cli -t "text to encipher/decipher" -r B -w I,0,0,II,0,0,III,0,0 -p ab,cd,ef
```
```
echo "text to encipher/decipher" | ./bin/enigma-cli -r C -w I,0,0,II,0,0,III,0,0 -p ab,cd
```
