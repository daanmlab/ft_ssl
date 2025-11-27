#include "ft_ssl.h"

static const uint32_t g_sha256_k[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

void _update_state(s_sha256_ctx *ctx, uint32_t words[64])
{
  int i = 0;
  uint32_t big_s1;
  uint32_t ch;
  uint32_t temp1;
  uint32_t big_s0;
  uint32_t maj;
  uint32_t temp2;

  uint32_t a = ctx->state.A;
  uint32_t b = ctx->state.B;
  uint32_t c = ctx->state.C;
  uint32_t d = ctx->state.D;
  uint32_t e = ctx->state.E;
  uint32_t f = ctx->state.F;
  uint32_t g = ctx->state.G;
  uint32_t h = ctx->state.H;

  i = 0;
  while (i < 64)
  {

    big_s1 = ROTR(e, 6) ^ ROTR(e, 11) ^ ROTR(e, 25);
    ch = (e & f) ^ ((~e) & g);
    temp1 = h + big_s1 + ch + g_sha256_k[i] + words[i];

    big_s0 = ROTR(a, 2) ^ ROTR(a, 13) ^ ROTR(a, 22);
    maj = (a & b) ^ (a & c) ^ (b & c);
    temp2 = big_s0 + maj;

    h = g;
    g = f;
    f = e;
    e = d + temp1;
    d = c;
    c = b;
    b = a;
    a = temp1 + temp2;

    i++;
  }

  ctx->state.A += a;
  ctx->state.B += b;
  ctx->state.C += c;
  ctx->state.D += d;
  ctx->state.E += e;
  ctx->state.F += f;
  ctx->state.G += g;
  ctx->state.H += h;
}

static void _process_block(s_sha256_ctx *ctx)
{
  uint32_t words[64];
  int i;
  uint32_t s0;
  uint32_t s1;

  // Set up message schedule
  i = 0;
  while (i < 16)
  {
    words[i] = ((uint32_t)ctx->block[(i * 4)] << 24) | ((uint32_t)ctx->block[(i * 4) + 1] << 16) | ((uint32_t)ctx->block[(i * 4) + 2] << 8) | ((uint32_t)ctx->block[(i * 4) + 3]);
    i++;
  }

  while (i < 64)
  {
    s0 = (ROTR(words[i - 15], 7) ^
          ROTR(words[i - 15], 18) ^
          (words[i - 15] >> 3));
    s1 =
        (ROTR(words[i - 2], 17) ^
         ROTR(words[i - 2], 19) ^
         (words[i - 2] >> 10));
    words[i] = (words[i - 16] + s0 +
                words[i - 7] + s1);
    i++;
  }

  _update_state(ctx, words);
}

void sha256_init(s_sha256_ctx *ctx)
{
  ctx->state.A = 0x6a09e667;
  ctx->state.B = 0xbb67ae85;
  ctx->state.C = 0x3c6ef372;
  ctx->state.D = 0xa54ff53a;
  ctx->state.E = 0x510e527f;
  ctx->state.F = 0x9b05688c;
  ctx->state.G = 0x1f83d9ab;
  ctx->state.H = 0x5be0cd19;
  ctx->block_len = 0;
  ctx->bitlen = 0x00;
}

void sha256_update(s_sha256_ctx *ctx, const uint8_t *data, size_t size)
{
  ctx->bitlen += (uint64_t)size * 8;

  while (size-- > 0)
  {
    ctx->block[ctx->block_len++] = *(data++);

    if (ctx->block_len == 64)
    {
      _process_block(ctx);
      ctx->block_len = 0;
    }
  }
}

void sha256_finalize(s_sha256_ctx *ctx)
{
  int i;
  uint32_t bits;

  ctx->block[ctx->block_len++] = 0x80;

  if (ctx->block_len > 56)
  {
    while (ctx->block_len < 64)
      ctx->block[ctx->block_len++] = 0x00;
    _process_block(ctx);
    ctx->block_len = 0;
  }

  while (ctx->block_len < 56)
    ctx->block[ctx->block_len++] = 0x00;

  i = 7;
  bits = ctx->bitlen;
  while (i >= 0)
  {
    ctx->block[ctx->block_len + i] = (uint8_t)(bits & 0xFF);
    bits >>= 8;
    i--;
  }
  ctx->block_len += 8;
  _process_block(ctx);
  ctx->block_len = 0;
}
