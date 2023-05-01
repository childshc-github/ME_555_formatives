#include "stats.h"

// notes:
// name:number:position (ends in null terminator, no newline)
// valid input: name at least 1 character but < 64, a number, a letter
// if wrong input --> error message + exit(EXIT_FAILURE)
// initialize fields in player_t w/ inputs
// initialize rebounds, points, games = 0
// use valgrind + create test cases

// any other headers you need here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// initialize vars
int sequencer = 0;
int name_counter = 0;
int num_counter = 0;
int posn_counter = 0;

// input format checker
void format_checker(char * line) {
  // check name
  while (line[sequencer] != ':') {
    if (line[sequencer] == ' ') {
      if (sequencer == 0) {
        fprintf(stderr, "Player's name contains leading space\n");
        exit(EXIT_FAILURE);
      }
      name_counter++;
      sequencer++;
      continue;
    }
    if ((line[sequencer] < 'A') || (line[sequencer] > 'z')) {
      fprintf(stderr, "Player name is invalid type\n");
      exit(EXIT_FAILURE);
    }
    name_counter++;
    sequencer++;
  }
  if ((name_counter == 0) || (name_counter > MAX_NAME_LEN)) {
    fprintf(stderr, "Player's name is formatted incorrectly.\n");
    exit(EXIT_FAILURE);
  }

  // check num
  sequencer++;
  while (line[sequencer] != ':') {
    if ((line[sequencer] < '0') || (line[sequencer] > '9')) {
      fprintf(stderr, "Player number is invalid type\n");
      exit(EXIT_FAILURE);
    }
    num_counter++;
    sequencer++;
  }
  if ((num_counter == 0) || (num_counter > 2)) {
    fprintf(stderr, "Player's number is formatted incorrectly\n");
    exit(EXIT_FAILURE);
  }

  // check posn
  sequencer++;
  while (line[sequencer] != '\0') {
    posn_counter++;
    sequencer++;
  }
  if (posn_counter != 1) {
    fprintf(stderr, "Player's position is formatted incorrectly.\n");
    exit(EXIT_FAILURE);
  }
  sequencer--;
  if ((line[sequencer] == 'C') || (line[sequencer] == 'F' || (line[sequencer] == 'G'))) {
    return;
  }
  else {
    fprintf(stderr, "Player's position is not labelled correctly.\n");
    exit(EXIT_FAILURE);
  }
}

player_t parseLine(char * line) {
  // check format of input string
  format_checker(line);

  // templates
  char nameArray[MAX_NAME_LEN];
  unsigned player_num;
  int posn;

  // extract name data
  for (int i = 0; i < name_counter; i++) {
    nameArray[i] = line[i];
  }

  nameArray[name_counter] = '\0';

  // extract num data
  if (num_counter == 1) {
    player_num = line[name_counter + 1] - '0';
  }
  if (num_counter == 2) {
    unsigned num1 = line[name_counter + 1] - '0';
    unsigned num2 = line[name_counter + 2] - '0';
    player_num = (num1 * 10) + num2;
  }

  // assign posn data
  if (line[sequencer] == 'C') {
    posn = 0;
  }
  if (line[sequencer] == 'F') {
    posn = 1;
  }
  if (line[sequencer] == 'G') {
    posn = 2;
  }

  // update player struct + return
  player_t answer;
  strncpy(answer.name, nameArray, (name_counter + 1));
  answer.number = player_num;
  answer.position = posn;
  answer.rebounds = 0;
  answer.points = 0;
  answer.games = 0;

  // reset vars for next input
  sequencer = 0;
  name_counter = 0;
  num_counter = 0;
  posn_counter = 0;

  return answer;
}

// notes:
// roster = array of player_t's (has stats so far)
// n_players = number of players in the roster
// number = the player's number
// rebounds = # of rebounds that player had in the game
// points = # of points that player had in the game
// match name by player num + update roster
// increment stats and games!
// num not in data = print error + exit
// num may start w/ 0 if single digit
// takes multiple file inputs

void addGame(player_t * roster,
             size_t n_players,
             unsigned number,
             unsigned rebounds,
             unsigned points) {
  // setup tracking vars
  unsigned checks = 0;
  int in_roster = 0;

  // format handling
  if (number == ' ') {
    fprintf(stderr, "Player game number is formatted incorrectly\n");
    exit(EXIT_FAILURE);
  }

  if (rebounds == ' ') {
    fprintf(stderr, "Player game rebounds is formatted incorrectly\n");
    exit(EXIT_FAILURE);
  }

  if (points == ' ') {
    fprintf(stderr, "Player game points is formatted incorrectly\n");
    exit(EXIT_FAILURE);
  }

  // loops through roster array for num of players
  for (int i = 0; i < n_players; i++) {
    // setup values
    unsigned pnum = roster[i].number;

    // increment tracker
    checks++;

    // if num in roster + match
    if (pnum == number) {
      roster[i].rebounds += rebounds;
      roster[i].points += points;
      roster[i].games += 1;
      in_roster = 1;
    }

    // num in roster resets
    if ((checks == n_players) && (in_roster == 1)) {
      checks = 0;
      in_roster = 0;
    }

    // if player num not in roster
    if ((checks == n_players) && (in_roster == 0)) {
      fprintf(stderr, "Player number is not in roster\n");
      exit(EXIT_FAILURE);
    }
  }
}

// notes:
// doubledouble: when player earns >= 10 rebounds && >= 10 points
// roster: array of player_ts
// n_players: number of players in roster
// print name w/ newline if conditions met

void printDoubleDouble(player_t * roster, size_t n_players) {
  // initialize tracker
  int tracker = 0;

  // loop through + check
  for (int i = 0; i < n_players; i++) {
    if ((roster[i].rebounds >= 10) && (roster[i].points >= 10)) {
      while (roster[i].name[tracker] != '\0') {
        printf("%c", roster[i].name[tracker]);
        tracker++;
      }
      if (roster[i].name[tracker] == '\0') {
        tracker = 0;
        printf("\n");
      }
    }
  }
}

// notes:
// Calculates total points with players in a position + prints most points

void printPosPoints(player_t * roster, size_t n_players) {
  // initiate trackers
  unsigned C_points = 0;
  unsigned F_points = 0;
  unsigned G_points = 0;
  unsigned max_points;

  // loop through
  for (int i = 0; i < n_players; i++) {
    if (roster[i].position == 0) {
      C_points += roster[i].points;
    }
    if (roster[i].position == 1) {
      F_points += roster[i].points;
    }
    if (roster[i].position == 2) {
      G_points += roster[i].points;
    }
  }

  // determines posn with most points
  if ((C_points > F_points) && (C_points > G_points)) {
    max_points = C_points;
    printf("Centers had the most points with %u points\n", max_points);
  }
  if ((F_points > C_points) && (F_points > G_points)) {
    max_points = F_points;
    printf("Forwards had the most points with %u points\n", max_points);
  }
  if ((G_points > C_points) && (G_points > F_points)) {
    max_points = G_points;
    printf("Guards had the most points with %u points\n", max_points);
  }

  // determines if tie
  // C tie with F
  if ((C_points == F_points) && (C_points > G_points)) {
    max_points = C_points;
    printf("Centers had the most points with %u points\n", max_points);
  }

  // C tie with G
  if ((C_points == G_points) && (C_points > F_points)) {
    max_points = C_points;
    printf("Centers had the most points with %u points\n", max_points);
  }

  // F tie with G
  if ((F_points == G_points) && (F_points > C_points)) {
    max_points = F_points;
    printf("Forwards had the most points with %u points\n", max_points);
  }

  // C tie with all
  if ((C_points == F_points) && (C_points == G_points)) {
    max_points = C_points;
    printf("Centers had the most points with %u points\n", max_points);
  }
}
