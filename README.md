# DataEncryptionStandard-Implementation-DES-
This repository contains an optimized Sw iplementation of Data Encryption Standard (Standard DES) algorithm, which:
- encrypts data of size of 64 bits ,which means 64 bits of plain text go as the input to DES, which produces 64 bits of ciphertext. 
- The same algorithm and key are used for encryption and decryption, with minor differences.
- The number of CPU cycles taken for each process will be calculated.

#  _Requirements_
- g++ compiler need to be installed.

# Run
- open command promt or any command-line shell.
- navigate to the cpp file location.
- use : g++ -O main.cpp -o output
- To encrypt use : output.exe encrypt [PlainText] [Key] 
                   ,ex: output.exe encrypt 7A6C731D22347676 1323445A6D788381
- To decrypt use : output.exe decrypt [CipherText] [Key]
                 ,ex : output.exe decrypt 7DB033DD14D6F975 1323445A6D788381!
## output screen samples 
(https://user-images.githubusercontent.com/75391814/175969935-b9619485-f565-482c-b144-bdc706e5d244.jpg)
