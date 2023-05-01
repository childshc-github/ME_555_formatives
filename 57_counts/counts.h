#include <stdio.h>

#ifndef __COUNTS_H__
#define __COUNTS_H__

struct _one_count_t {
  //DEFINE ME
  char * count_name;
  int count;
};

typedef struct _one_count_t one_count_t;

struct _counts_t {
  //DEFINE ME
  one_count_t * count_array;
  int length_count_array;
  int num_unknown_names;
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
