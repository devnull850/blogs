#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef LEN
#define LEN 19
#endif

const char BASE[] = { 0x30, 0x41, 0x61 };

int generate_char(void);

int main(void) {
  char key[LEN+1];
  double d;
  int i;

  srand(time(NULL));

  key[4] = key[9] = key[14] = 45;

  key[6] = generate_char();
  key[7] = generate_char();
  key[10] = generate_char();
  key[12] = generate_char();

  while (1) {
    key[1] = generate_char();
    key[2] = key[1] - rand() % 4;

    i = 0;

    do {
      key[5] = generate_char();
    } while (i < 20 && (key[5] - key[9] >= 75));

    if (i == 20) continue;

    key[16] = generate_char();
    if ((key[16] & 1)) ++key[16];
    key[0] = key[16];
    key[11] = key[0] - 1;

    do {
      key[18] = generate_char();
    } while ((key[18] & 1));

    do {
      key[17] = generate_char();
    } while (!(key[17] & 1));

    d = sqrt((double) key[17]) + sqrt((double) key[16]);

    i = 0;

    do {
      key[3] = generate_char();
      key[13] = generate_char();
      ++i;
    } while (i < 20 && d <= sqrt((double) key[3]) + sqrt((double) key[13]));

    if (i == 20) continue;

    i = 0;

    do {
      key[15] = generate_char();
      key[8] = generate_char();
      ++i;
    } while (i < 20 && key[15] - key[11] - key[14] + key[8] + key[0] <= 25);

    if (i == 20) continue;

    if (key[0] - key[14] - key[11] + key[15] + key[8] < 140) break;
  }

  key[LEN] = 0;

  puts(key);

  return 0;
}

int generate_char(void) {
  int ch;

  ch = BASE[rand() % 3];

  switch (ch) {
    case 0x41:
    case 0x61:
      ch = ch + rand() % 26;
      break;

    case 0x30:
      ch = ch + rand() % 10;
  };

  return ch;
}

