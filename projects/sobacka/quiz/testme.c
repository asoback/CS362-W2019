/*
Andrew Soback
Random Testing Quiz
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	int x; // Used to get a random integer between 0 and 8
	char a; // Used to store and return the randomly generated character
	x = rand() % 9; // Get the random number
	switch(x){
		case 0:
			a = '{';
			break;
		case 1:	
			a = '}';
			break;

		case 2:	
			a = ']';
			break;

		case 3:	
			a = '[';
			break;

		case 4:	
			a = '(';
			break;

		case 5:	
			a = ')';
			break;

		case 6:	
			a = ' ';
			break;

		case 7:	
			a = 'a';
			break;

		case 8:	
			a = 'x';
			break;
	}
    return a;
}

char *inputString()
{
	char* r = new char [6]; // This pointer is to contain a random string, and be returned
	r[5] = '\0'; // The string size is fixed at 5 letters, ending in a '\0'

	int i;
	int x;
	for(i = 0; i < 5; i++){
		x = rand() % 4;
		// Each character in the string will be randomly selected from these 4
		switch(x){
			case 0:
				r[i] = 'r';
				break;
			case 1:
				r[i] = 'e';
				break;
			case 2:
				r[i] = 's';
				break;
			case 3:
				r[i] = 't';
				break;
		}
	}

    return r;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
