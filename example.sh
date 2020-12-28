int a = 1
int b = 2
/* if else */ 
if ( a != b ) {
  print("Not equal"); 
} else {
  print("Equal");
}

/* do while */
do {
  a += 1;
} while ( a < b );

/* for loop */
for(int i = 0; i < 3; i += 1) {
  print(i);
  if ( i == 1 ) {
    break;
  } else {
    continue;
  }
}

string str = "abc";
char c = 'a';
