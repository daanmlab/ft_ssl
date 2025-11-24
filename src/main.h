#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

struct s_ABCD {
  uint32_t A;
  uint32_t B;
  uint32_t C;
  uint32_t D;
};

struct s_ABCD compute_md5(uint8_t *data);