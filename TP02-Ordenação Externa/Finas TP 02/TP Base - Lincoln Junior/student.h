#ifndef STUDENT_H
#define STUDENT_H

typedef struct
{
  char state[3], city[51], course[32];
  int id;
  short origin, priority, flag;
  float grade;
} tStudent;

#endif
