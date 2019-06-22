#ifndef FILE_H
#define FILE_H

#include <stdio.h>

#include "student.h"

short readStudent(FILE **, tStudent *);
short writeStudent(FILE *, tStudent);
void identifyProperInputFile(short);

#endif
