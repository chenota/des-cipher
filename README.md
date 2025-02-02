# DES Cipher

This program inputs a 64-bit block of text and a 64-bit key, and encrypts or decrypts the text using the DES algorithm.

## Program Arguments

| Argument        | Description                                                                                      |
|-----------------|--------------------------------------------------------------------------------------------------|
| `-v, --verbose` | Use verbose output. If included twice, use very verbose output.                                  |
| `-e, --encrypt` | (Default) Run in encrypt mode.                                                                   |
| `-d, --decrypt` | Run in decrypt mode.                                                                             |
| `text` | (Positional) Input text in hexadecimal format; either plaintext or ciphertext depending on other options. |
| `key` | (Positional) Encryption/decryption key in hexadecimal format.                                              |

## Build Information

To build the program, use the included Makefile.

## Example

We can verify the program correctness by encrypting some plaintext, decryping the resultant ciphertext, and ensuring the plaintexts match.

Encrypting some plaintext:
```
$ ./des.out -e 0123456789ABCDEF 133457799BBCDFF1
85e813540f0ab405
```

Decrypting the ciphertext:
```
$ ./des.out -d 85e813540f0ab405 133457799BBCDFF1
0123456789abcdef
```

The plaintexts match, which is a good sign that the program works!

## Sources

The following sources were crucial for building this project:
- Cryptography and Network Security: Principles and Practice 7e by William Stallings
- [The DES Algorithm Illustrated](https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm)
- [JavaScript DES Example](https://people.duke.edu/%7Etkb13/courses/ncsu-csc405-2015fa/RESOURCES/JS-DES.shtml)