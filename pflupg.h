#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <libgen.h>
#include <time.h>
#include <gcrypt.h>

#define UPG_HEADER_FLAG_ENCRYPTION	0x20000000
#define UPG_ENTRY_HEADER_ATTR_NESTED	0x04000000

static const char upg_header_magic[] = "2SWU3TXV";

#define PUBLIC_KEYS_CNT	2
static const char *public_keys[PUBLIC_KEYS_CNT][3] = { // { name, public exponent e (hex string), modulus n (hex string)}
	{"q5551", "010001", "D7EE8ED11AC048ED225D4F5F53F8509E55C5D94256A703C79E4CA78AE93ECE1639FE466363AD962BD6D6DE0C46FD19F363687C1D8A21820740A6E7FF87F41C4900DCE1E26EC122E5D4DFA76BFC8F296816B8D0910325E9DC5CBCC9579CF15FC0253EF7CF4919B7613491A5D7BF75DC1888531C458967FD1CF64B33139550BAA5"},
	{"qf1eu", "010001", "ACD684155C7CCCB04372A8808514489FA9EE75D305987D1337420241FDBE0AE1F7CDFBB931C9D56C91D36F2CE79D222695B484FF42BCA12CE362C7C9ABBDEEC8E5D6107FADCF2D4DA5DF0693E13ACE54A18AEB21C051F6B62C075A1791985547C1CFF4FB5B6EA7E0A9405A1B2BB71EB89A9B209E0F62BF9794D673179C0E60F1"}
};

#define AUTO_FW_CNT 6
static const char *auto_fw[AUTO_FW_CNT][2] = { // { platform code, key name to be used }
  {"Q5551", "q5551"},
  {"Q5553", "q5551"},
  {"Q554E", "q5551"},
  {"Q554M", "q5551"},
  {"QF1EU", "qf1eu"},
  {"QF2EU", "qf1eu"}
};

typedef struct _struct_sig {
	unsigned char sha1[20];
	unsigned char aes_key[32];
	unsigned char unknown[76];
} struct_sig;

typedef struct _upg_header
{
  unsigned char magic[8];
  uint32_t header_size;
  uint32_t data_size;
  uint32_t crc;
  uint32_t mask;
  uint32_t data_size_decompressed;
  uint32_t padding2;
  unsigned char description[512];
  struct_sig signature;
  unsigned char unknown[32];
  unsigned char releaseStr[28];
} upg_header;

typedef struct _upg_entry_header
{
  char filename[60];
  uint32_t iRealSize;
  uint32_t iStoredSize;
  uint32_t iHeaderSize;
  uint32_t iAttributes;
} upg_entry_header;
