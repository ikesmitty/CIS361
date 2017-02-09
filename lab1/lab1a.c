#include <stdio.h>
#include <ctype.h>
int main () {
char ch;
int numOfWords = 0;
int numOfSymbols = 0;
int lastCharWasSpace = 1;
printf ("Enter text (Ctrl-D to quit).\n");
while ( ch = getchar(), ch != EOF ) {
  if(isspace(ch))
    lastCharWasSpace = 1;
  else{
    if(lastCharWasSpace){
      lastCharWasSpace = 0;
      numOfWords = numOfWords + 1;
    }
    if ( islower(ch) )
      ch = toupper(ch);
    else
      ch = tolower(ch);
  }
    putchar(ch);
}
  printf("\nNumber of Words = %d\n", numOfWords);
  return 0;
}
