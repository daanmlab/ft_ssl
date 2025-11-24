#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// Hardcoded K and S values for the redbox
uint32_t g_K[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8,
                    0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193,
                    0xa679438e, 0x49b40821,

                    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d,
                    0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6,
                    0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905,
                    0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,

                    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44,
                    0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6,
                    0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039,
                    0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,

                    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3,
                    0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f,
                    0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82,
                    0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

uint32_t g_S[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,

                    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,

                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,

                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

uint32_t g_A = 0x67452301;
uint32_t g_B = 0xefcdab89;
uint32_t g_C = 0x98badcfe;
uint32_t g_D = 0x10325476;

int len(char *a)
{
  char *ptr;

  ptr = (char *)a;
  while (*ptr != '\0')
    ptr++;
  return (ptr - (char *)a);
}

int _get_padding(int len)
{
  int L;

  L = len % 64;
  if (L < 56)
    return (56 - L);
  else
    return (56 + 64 - L);
}

struct s_prepped
{
  uint8_t *data;
  int length;
};

struct s_ABCD
{
  uint32_t A;
  uint32_t B;
  uint32_t C;
  uint32_t D;
};

struct s_prepped prep_with_padding(uint8_t *data)
{
  struct s_prepped prepped;
  int data_len;
  int padding_bytes;
  int terminator;
  int total_len;
  int i;
  uint64_t bit_len;
  int j;

  data_len = len((char *)data);
  padding_bytes = _get_padding(data_len);
  terminator = 0x80;
  total_len = data_len + padding_bytes + 8;
  prepped.data = malloc((total_len) * sizeof(uint8_t));
  i = 0;
  // copy data to new_data
  while (data[i])
  {
    prepped.data[i] = data[i];
    i++;
  }
  // add terminator
  prepped.data[i++] = terminator;
  // fill up 0s till 8 bytes left
  while (i < data_len + padding_bytes)
    prepped.data[i++] = 0x00;
  // original length in bits
  bit_len = (uint64_t)data_len * 8;
  j = 0;
  while (j < 8)
    prepped.data[i++] = (bit_len >> (8 * j++) & 0xFF);
  prepped.length = total_len;
  return (prepped);
}

uint32_t F(uint32_t B, uint32_t C, uint32_t D, int i)
{
  if (i >= 0 && i <= 15)
    return (B & C) | ((~B) & D);
  else if (i >= 16 && i <= 31)
    return (D & B) | ((~D) & C);
  else if (i >= 32 && i <= 47)
    return (B ^ C ^ D);
  else
    return (C ^ (B | (~D)));
}

uint32_t redBox(uint32_t input, uint32_t B, int i)
{
  uint32_t returnVal;

  returnVal = input;
  returnVal += g_K[i];
  returnVal = (returnVal << g_S[i] | returnVal >> (32 - g_S[i]));
  returnVal += B;
  return (returnVal);
}

void _to_words(uint8_t *input, uint32_t words[])
{
  int i;
  int base;

  i = 0;
  while (i < 16)
  {
    base = i * 4;
    words[i] = ((uint32_t)input[base] + ((uint32_t)input[base + 1] << 8) + ((uint32_t)input[base + 2] << 16) + ((uint32_t)input[base + 3] << 24));
    i++;
  }
}

int _get_word_index(int i)
{
  if (i >= 0 && i <= 15)
    return (i);
  if (i >= 16 && i <= 31)
    return (((i * 5) + 1) % 16);
  if (i >= 32 && i <= 47)
    return (((i * 3) + 5) % 16);
  if (i >= 48 && i <= 63)
    return ((i * 7) % 16);
  return (i);
}

struct s_ABCD hash(uint8_t *input, uint32_t _A, uint32_t _B, uint32_t _C,
                   uint32_t _D)
{
  uint32_t A;
  uint32_t B;
  uint32_t C;
  uint32_t D;
  uint32_t newA;
  uint32_t newB;
  uint32_t newC;
  uint32_t newD;
  uint32_t words[16];
  int i;
  struct s_ABCD returnHash;

  A = _A;
  B = _B;
  C = _C;
  D = _D;
  _to_words(input, words);
  i = 0;
  while (i < 64)
  {
    newA = D;
    newB = redBox((A + F(B, C, D, i)) + words[_get_word_index(i)], B, i);
    newC = B;
    newD = C;
    A = newA;
    B = newB;
    C = newC;
    D = newD;
    i++;
  }
  returnHash.A = _A + A;
  returnHash.B = _B + B;
  returnHash.C = _C + C;
  returnHash.D = _D + D;
  return (returnHash);
}

struct s_ABCD compute_md5(uint8_t *data)
{
  struct s_prepped prepped;
  struct s_ABCD current;
  int i;

  // add padding
  prepped = prep_with_padding(data);
  current.A = g_A;
  current.B = g_B;
  current.C = g_C;
  current.D = g_D;
  i = 0;
  while (i * 64 < prepped.length)
  {
    current = hash(&(prepped.data[i * 64]), current.A, current.B, current.C,
                   current.D);
    i++;
  }
  free(prepped.data);
  return (current);
}
