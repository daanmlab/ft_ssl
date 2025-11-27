#include "ft_ssl.h"

void print_md5_hash(s_md5_state result)
{
  print_hex_byte((result.A & 0xFF));
  print_hex_byte(((result.A >> 8) & 0xFF));
  print_hex_byte(((result.A >> 16) & 0xFF));
  print_hex_byte(((result.A >> 24) & 0xFF));
  print_hex_byte((result.B & 0xFF));
  print_hex_byte(((result.B >> 8) & 0xFF));
  print_hex_byte(((result.B >> 16) & 0xFF));
  print_hex_byte(((result.B >> 24) & 0xFF));
  print_hex_byte((result.C & 0xFF));
  print_hex_byte(((result.C >> 8) & 0xFF));
  print_hex_byte(((result.C >> 16) & 0xFF));
  print_hex_byte(((result.C >> 24) & 0xFF));
  print_hex_byte((result.D & 0xFF));
  print_hex_byte(((result.D >> 8) & 0xFF));
  print_hex_byte(((result.D >> 16) & 0xFF));
  print_hex_byte(((result.D >> 24) & 0xFF));
}
