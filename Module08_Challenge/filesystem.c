#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 1000
#define MAX_LINE 1024

typedef struct {
  char brand[128];
  char city[128];
  char name[128];
  char state[128];
} Record;

void removeQuotes(char *str) {
  char *src = str, *dst = str;
  while (*src) {
    if (*src != '"')
      *dst++ = *src;
    src++;
  }
  *dst = '\0';
}

int main() {
  // Change permissions on the file to make the file read-only.
  system("chmod 444 input.txt");
  // Create another copy of the file with the name: "inputTemp.txt".
  system("cp input.txt inputTemp.txt");

  FILE *in = fopen("inputTemp.txt", "r");
  if (!in) {
    perror("Cannot open inputTemp.txt");
    return 1;
  }

  char line[MAX_LINE];
  // Skip the header line.
  fgets(line, MAX_LINE, in);

  // Use an array of structs or a struct-linked list.
  Record records[MAX_RECORDS];
  int count = 0;

  while (fgets(line, MAX_LINE, in) && count < MAX_RECORDS) {
    line[strcspn(line, "\n")] = '\0';

    char brand[128] = "", city[128] = "", name[128] = "", state[128] = "";
    int index = 0;
    char *token = strtok(line, ",");
    while (token) {
      removeQuotes(token);
      if (index == 1)
        strncpy(brand, token, sizeof(brand) - 1);
      else if (index == 9)
        strncpy(city, token, sizeof(city) - 1);
      else if (index == 10)
        strncpy(name, token, sizeof(name) - 1);
      else if (index == 11)
        strncpy(state, token, sizeof(state) - 1);
      token = strtok(NULL, ",");
      index++;
    }
    if (brand[0] != '\0') {
      strncpy(records[count].brand, brand, sizeof(records[count].brand) - 1);
      strncpy(records[count].city, city, sizeof(records[count].city) - 1);
      strncpy(records[count].name, name, sizeof(records[count].name) - 1);
      strncpy(records[count].state, state, sizeof(records[count].state) - 1);
      count++;
    }
  }
  fclose(in);

  // On the 7th record replace store_name with "WILDCATS MARKET"
  if (count >= 7)
    strncpy(records[6].name, "WILDCATS MARKET", sizeof(records[6].name) - 1);

  // Change all records with state "CA" to "California"
  for (int i = 0; i < count; i++) {
    if (strcmp(records[i].state, "CA") == 0)
      strncpy(records[i].state, "California", sizeof(records[i].state) - 1);
  }

  FILE *out = fopen("final.txt", "w");
  if (!out) {
    perror("Cannot open final.txt");
    return 1;
  }
  for (int i = 0; i < count; i++) {
    fprintf(out, "%s\t%s\t%s\t%s\n", records[i].brand, records[i].city,
            records[i].name, records[i].state);
  }
  fclose(out);

  return 0;
}
