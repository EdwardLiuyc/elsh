# elsh

## Motivation 
In a word, I want to build my own script language that can be written in `C` or a simplied version of `C`. And here are some basic rules: 
- All the code would be written in C++ and C++ only, using c++11 standard. No more than that.
- The code should be able to be built anywhere there is a C++ compiler. so, we will use `Makefile` to build this project. No `cmake` or `bazel`.

## Goal
For example, you have a `elsh` script `example.sh` like this: 
```
int a = 0;
int b = 10;
do {
  a += 1;
  print(a);
} while ( a < b );
```
and you have already install the `elsh` in the system, then you can use: 
```
elsh example.sh
```
to run this script.

## Definitions
### Basic Data Types
| Name      |              Common name               | Character sequence |
| :-------- | :------------------------------------: | :----------------: |
| Dt_int32  |             32bit integer              |       int32        |
| Dt_int64  |             64bit integer              |       int64        |
| Dt_uint32 |         32bit unsigned integer         |       uint32       |
| Dt_uint64 |         64bit unsigned integer         |       uint64       |
| Dt_double | double-precision floating-point number |       double       |
| Dt_char   |                charater                |        char        |
| Dt_string |                 string                 |       string       |
| Dt_void   |               empty type               |        void        |
| Dt_bool   |                boolean                 |        bool        |

### Operators
| Name            |      Common name      | Character sequence |
| :-------------- | :-------------------: | :----------------: |
| Op_multiply     |       multiply        |         *          |
| Op_divide       |        divide         |         /          |
| Op_mod          |          mod          |         %          |
| Op_add          |         plus          |         +          |
| Op_subtract     |         minus         |         -          |
| Op_negate       |      unary minus      |         -          |
| Op_less         |       less than       |         <          |
| Op_lessequal    |  less than or equal   |         <=         |
| Op_greater      |     greater than      |         >          |
| Op_greaterequal | greater than or equal |         >=         |
| Op_equal        |         equal         |         ==         |
| Op_notequal     |       not equal       |         !=         |
| Op_not          |       unary not       |         !          |
| Op_assign       |      assignment       |         =          |
| Op_and          |      logical and      |         &&         |
| Op_or           |      logical or       |         ¦¦         |

### Symbols
| Name         |    Common name    | Character sequence |
| :----------- | :---------------: | :----------------: |
| LeftParen    | left parenthesis  |         (          |
| RightParen   | right parenthesis |         )          |
| LeftBrace    |    left brace     |         {          |
| RightBrace   |    right brace    |         }          |
| LeftBracket  |   left bracket    |         [          |
| RightBracket |   right bracket   |         ]          |
| Semicolon    |    semi-colon     |         ;          |
| Comma        |       comma       |         ,          |

### Reverved Keywords
| Name             | Character sequence |
| :--------------- | :----------------: |
| Keyword_if       |         if         |
| Keyword_else     |        else        |
| Keyword_while    |       while        |
| Keyword_break    |       break        |
| Keyword_continue |      continue      |
| Keyword_do       |         do         |
| Keyword_for      |        for         |
| Keyword_print    |       print        |
| Keyword_putc     |        putc        |
| Keyword_return   |       return       |
| Keyword_true     |        true        |
| Keyword_false    |       false        |
| Keyword_const    |       const        |

### Comments
| Name                | Character sequence |
| :------------------ | :----------------: |
| SingleLine Comments |        `//`        |
| MultiLine Comments  |    `/* ... */`     |


## Build
make