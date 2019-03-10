%{
// Flex handles ambiguity by matching longest string;
// in case of tie, it matches the first one.

#include <iostream>
#include <cstdlib>
#include <ctime>

%}
letter      [a-zA-Z]

%%
"4"            { std::cout << "a"; }
"6"            { std::cout << "b"; }
"("            { std::cout << "c"; }
"[)"           { std::cout << "d"; }
"3"            { std::cout << "e"; }
"|="           { std::cout << "f"; }
"9"            { std::cout << "g"; }
"}{"           { std::cout << "h"; }
"!"            { std::cout << "i"; }
"_|"           { std::cout << "j"; }
"]{"           { std::cout << "k"; }
"|_"           { std::cout << "l"; }
"/|\\"         { std::cout << "m"; }
"|\\|"         { std::cout << "n"; }
"{}"           { std::cout << "o"; }
"|>"           { std::cout << "p"; }
"()."          { std::cout << "q"; }
".-"           { std::cout << "r"; }
"$"            { std::cout << "s"; }
"+"            { std::cout << "t"; }
"(_)"          { std::cout << "u"; }
"\\/"          { std::cout << "v"; }
"\\|/"         { std::cout << "w"; }
"><"           { std::cout << "x"; }
"`/"           { std::cout << "y"; }
"2"            { std::cout << "z"; }



À            { std::cout << "A" ; }
ß            { std::cout << "B" ; }
ç            { std::cout << "C" ; }
Ð            { std::cout << "D" ; }
È            { std::cout << "E" ; }
Ḟ            { std::cout << "F" ; }
Ǵ            { std::cout << "G" ; }
Љ            { std::cout << "H" ; }
Ȉ            { std::cout << "I" ; }
ǰ            { std::cout << "J" ; }
Ǩ            { std::cout << "K" ; }
Ľ            { std::cout << "L" ; }
ϻ            { std::cout << "M" ; }
Ņ            { std::cout << "N" ; }
Ό            { std::cout << "O" ; }
Ṗ            { std::cout << "P" ; }
Ɋ            { std::cout << "Q" ; }
Ɍ            { std::cout << "R" ; }
Ṡ            { std::cout << "S" ; }                        
Ṫ            { std::cout << "T" ; }
Ų            { std::cout << "U" ; }
Ɣ            { std::cout << "V" ; }
Ŵ            { std::cout << "W" ; }
ϗ            { std::cout << "X" ; }
Ÿ            { std::cout << "Y" ; }
Ž            { std::cout << "Z" ; }

"ℴ"         { std::cout << "." ; }
"℥"         { std::cout << "?" ; }
"⅂"         { std::cout << "!" ; }
"ℑ"         { std::cout << "," ; }
"ℰ"         { std::cout << ";" ; }
"ℶ"         { std::cout << ":" ; }
"ↀ"        { std::cout << "\'" ; }
"⅌"        { std::cout << "\"" ; }
" "        { std::cout << " " ; }
℗          { std::cout << "@" ; }


℺        { std::cout << "0" ; }
Ⅰ        { std::cout << "1" ; }
Ⅱ        { std::cout << "2" ; }
Ⅲ        { std::cout << "3" ; }
Ⅳ        { std::cout << "4" ; }
Ⅴ        { std::cout << "5" ; }
Ⅵ        { std::cout << "6" ; }
Ⅶ        { std::cout << "7" ; }
Ⅷ         { std::cout << "8" ; }
Ⅸ         { std::cout << "9" ; }
.              { }
"\n"           {std::cout <<std::endl; }
%%
int yywrap() { return 1; }
