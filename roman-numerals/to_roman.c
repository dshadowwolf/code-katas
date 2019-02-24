#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *lt_ten[9] = { "I", "II", "III", "IV", "V", "VI", "VII", "IIX", "IX" };
const char *lt_hun[9] = { "X", "XX", "XXX", "XL", "L", "LX", "LXX", "XXC", "XC" };
const char *lt_tho[9] = { "C", "CC", "CCC", "CD", "D", "DC", "DCC", "CCM", "CM" };

char *handle_thousands(int input) {
  int r = input / 1000;
  char *rv = malloc(sizeof(char)*(r+1));
  memset(rv, 0, sizeof(char)*(r+1));
  for(int i = 0; i < r; i++) strcat(rv, "M");

  return rv;
}

char *handle_hundreds(int input) {
  char *pr = malloc(sizeof(char)*7);
  memset(pr, 0, sizeof(char)*7);
  int huns = input / 100;
  if(huns > 10) {
    char *tr = handle_thousands(input);
    strcat(pr, tr);
    free(tr);
    huns = (input % 1000) / 100;
  }

  if( huns > 0 ) {
    huns--;
    strcat(pr, lt_tho[huns]);
  }
  
  return pr;
}

char *handle_tens(int input) {
  char *rv = malloc(sizeof(char)*10);
  memset(rv, 0, sizeof(char)*10);
  int tens = input / 10;
  if( tens >= 10 ) {
    char *hr = handle_hundreds(input);
    strcat(rv, hr);
    free(hr);
    tens = (input % 100) / 10;
  }

  if( tens > 0 ) {
    tens--;
    strcat(rv, lt_hun[tens]);
  }
  
  return rv;
}

char *handle_singles(int input) {
  char *rets = malloc(sizeof(char)*13);
  memset(rets, 0, sizeof(char)*13);
  int v = input % 10;
  if(input >= 10) {
    char *temp = handle_tens(input);
    strcat(rets, temp);
    free(temp);
  }

  if( v > 0 ) {
    v--;
    strcat(rets, lt_ten[v]);
  }
  
  return rets;
}

char *to_roman(int input) {
  if(input > 3000) return "";
  
  return handle_singles(input);
}

/*
 * this was added for testing of the arabic->roman code
int main(int argc, char *argv[]) {
  if(argc == 1) {
    printf("usage: to_roman <value> [<value>...]\n");
    return -1;
  }

  for(int j = 1; j < argc; j++) {
    int pv = atoi(argv[j]);
    char *arg = argv[j];
    printf("%s is %s in roman numerals\n", arg, to_roman(pv));
  }
  
  return 0;
}
*/
