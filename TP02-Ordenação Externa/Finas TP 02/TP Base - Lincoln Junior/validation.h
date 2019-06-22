#ifndef VALIDATION_H
#define VALIDATION_H

typedef struct
{
  short showData;
  int method, quantity, situation;
} tArguments;

int validateArguments(int, char ***, tArguments *);

#endif
