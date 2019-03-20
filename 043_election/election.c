#include "election.h"
//include any other headers you need here...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// count character numbers in the character array
int charcount(char str[]) {
  int count = 0;
  char * p = str;
  while (*p != '\0') {
    count++;
    p++;
  }
  return count;
}

// copy the string from src to dest
void strshort(char * src, char * dest, int count) {
  for (int i = 0; i < count; i++) {
    *dest = *src;
    dest++;
    src++;
  }
}

// check if a character is a number character
int IsValid(char * str, int size) {
  for (int i = 0; i < size - 1; i++) {
    if ((int)str[i] < 48 || (int)str[i] > 57) {
      return 0;
    }
  }
  return 1;
}

// check if a number is positive
int IsPositive(size_t number) {
  if (number > 0) {
    return 1;
  }
  else {
    return 0;
  }
}

state_t parseLine(const char * line) {
  //STEP 1: write me
  // initialize three char arrays to save statename, population and electoralvote
  const char * p1 = line;
  size_t array_size = strlen(line) + 1;
  char StateName[array_size];
  char population[array_size];
  char ElectoralVote[array_size];
  char CmpArray[array_size];

  for (size_t i = 0; i < array_size; i++) {
    StateName[i] = '\0';
    population[i] = '\0';
    ElectoralVote[i] = '\0';
    CmpArray[i] = '\0';
  }

  char * strArray[3] = {StateName, population, ElectoralVote};
  char ** p2 = strArray;
  int semi_count = 0;

  // parse string and assign values to arrays
  while (*p1 != '\0') {
    if (*p1 == ':') {
      semi_count++;
      p2++;
      p1++;
    }
    else if (semi_count < 3) {
      **p2 = *p1;
      (*p2)++;
      p1++;
    }
    else {
      fprintf(stderr, "Too many semicolons in the string! Expect two!\n");
      exit(EXIT_FAILURE);
    }
  }

  // check semicolon numbers
  if (semi_count != 2) {
    fprintf(stderr, "Not correct number of semicolons! Expect two!\n");
    exit(EXIT_FAILURE);
  }
  else if ((!strcmp(CmpArray, StateName)) || (!strcmp(CmpArray, population)) ||
           (!strcmp(CmpArray, ElectoralVote))) {
    fprintf(
        stderr,
        "At least one of the input entries are empty due to incorrect position of semicolon!\n");
    exit(EXIT_FAILURE);
  }

  // cut from the second null terminator at the end of the char array
  int len_StateName = charcount(StateName) + 1;
  char StateNameShort[len_StateName];
  strshort(StateName, StateNameShort, len_StateName);

  int len_population = charcount(population) + 1;
  char populationShort[len_population];
  strshort(population, populationShort, len_population);

  int len_ElectoralVote = charcount(ElectoralVote) + 1;
  char ElectoralVoteShort[len_ElectoralVote];
  strshort(ElectoralVote, ElectoralVoteShort, len_ElectoralVote);

  // check valid number of char array population and Electoralvote
  if ((!IsValid(populationShort, len_population)) ||
      (!IsValid(ElectoralVoteShort, len_ElectoralVote))) {
    fprintf(stderr,
            "Population and ElectoralVote contains negative values or non-numerical characters!\n");
    exit(EXIT_FAILURE);
  }

  // convert strings of population and ElectoralVote to integers
  uint64_t population_number = atoi(populationShort);
  unsigned int ElectoralVote_number = atoi(ElectoralVoteShort);

  // check population and Electoralvote are positive numbers
  if (population_number <= 0 || ElectoralVote <= 0) {
    fprintf(stderr, "Fault: Population or Electoralvote is non-postive value!\n");
    exit(EXIT_FAILURE);
  }

  // fill in state_t and return it
  state_t state;
  strcpy(state.name, StateNameShort);
  state.population = population_number;
  state.electoralVotes = ElectoralVote_number;

  // return the structure
  return state;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int sum_electoralvotes = 0;
  for (size_t i = 0; i < nStates; i++) {
    if ((voteCounts[i] * 2) > stateData[i].population) {
      sum_electoralvotes += stateData[i].electoralVotes;
    }
  }
  return sum_electoralvotes;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  double vote_rate = 0;
  for (size_t i = 0; i < nStates; i++) {
    vote_rate = ((double)voteCounts[i]) / (stateData[i].population);
    if (vote_rate >= 0.495 && vote_rate <= 0.505) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             vote_rate * 100);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  double max_voterate = ((double)voteCounts[0]) / (stateData[0].population);
  double current_voterate = max_voterate;
  double voterate = 0;
  for (size_t i = 1; i < nStates; i++) {
    current_voterate = ((double)voteCounts[i]) / (stateData[i].population);
    if (current_voterate > max_voterate) {
      max_voterate = current_voterate;
    }
  }
  // also consider cases with multiple LargestWins
  for (size_t i = 0; i < nStates; i++) {
    voterate = ((double)voteCounts[i]) / (stateData[i].population);
    if (voterate == max_voterate) {
      printf("Candidate A won %s with %.2f%% of the vote\n", stateData[i].name, voterate * 100);
    }
  }
}
