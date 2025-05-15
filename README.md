# pflupg-tool

## Introduction
pflupg-tool is an unpacking tool for Philips SmartTV firmware (Fusion platform - 2008-2013).

This fork adds the following to the original tool:
- Add decryption keys for Q5551, QF1EU and Q591E platforms
- Add automatic detection of firmware and applying the correct key
- Add the ability to output to a custom folder (It will extract to a folder "out" by default)
- Fix makefile

## Usage
> Usage: ./pflupg [-k key_name] [-o output_folder] upg_filename

If -k is not specified, the program will automatically try to find a fitting key
If -o is not specified, the extracted files will be output to a folder called "out" in the current directory

> 2 keys available :
> * q5551
> * qf1eu
> * q591e
  
## Supported firmwares
The following firmwares can be extracted using the included keys:
| Platform | Year      | Key            |
| -------- | --------- | -------------- |
| Q591E    | 2008      | Key is present |
| Q5551    | 2010/2011 | Key is present |
| Q5553    | 2010/2011 | Uses Q5551 Key |
| Q554E    | 2012      | Uses Q5551 Key |
| Q554M    | 2012      | Uses Q5551 Key |
| QF1EU    | 2012      | Key is present |
| QF2EU    | 2013      | Uses QF1EU Key |

## Customize
If your firmware is encrypted, and the key is not in the support list, you have to provide the corresponding public key (public exponent + modulus).
You can add public keys in pflupg.h file:
> \#define PUBLIC_KEYS_CNT 2
>
> // { name, public exponent e (hex string), modulus n (hex string)}
>
> static const char *public_keys[PUBLIC_KEYS_CNT][3] = {
>
>  {"my_key_1", "010001", "AABBCCDD"},
>
>  {"my_key_2", "010001", "010E020F"}
>
> };

## Build
You'll need Libgcrypt library to compile it. Then:

> $ make

## License
GPL v2
