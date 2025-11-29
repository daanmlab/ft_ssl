#include "ft_ssl.h"

int ft_strcmp(const char *s1, const char *s2)
{
  int i;

  i = 0;
  while (s1[i] && s2[i] && s1[i] == s2[i])
    i++;
  return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *ft_strdup(const char *s)
{
  int len;
  char *dup;
  int i;

  len = 0;
  while (s[len])
    len++;
  dup = (char *)malloc(len + 1);
  if (dup == NULL)
    return (NULL);
  i = 0;
  while (i < len)
  {
    dup[i] = s[i];
    i++;
  }
  dup[i] = '\0';
  return (dup);
}

void *ft_memcpy(void *dest, const void *src, int n)
{
  unsigned char *d;
  const unsigned char *s;
  int i;

  d = (unsigned char *)dest;
  s = (const unsigned char *)src;
  i = 0;
  while (i < n)
  {
    d[i] = s[i];
    i++;
  }
  return (dest);
}
