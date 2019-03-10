%{
// Flex handles ambiguity by matching longest string;
// in case of tie, it matches the first one.

#include <iostream>
#include <cstdlib>
#include <ctime>

%}
letter      [a-zA-Z]

%%

a            { std::cout << "4" ; }
b            { std::cout << "6" ; }
c            { std::cout << "(" ; }
d            { std::cout << "[)"; }
e            { std::cout << "3" ;  }
f            { std::cout << "|=" ; }
g            { std::cout << "9" ; }
h            { std::cout << "}{"; }
i            { std::cout << "!" ; }
j            { std::cout << "_|" ; }
k            { std::cout << "]{" ; }
l            { std::cout << "|_"; }
m            { std::cout << "/|\\" ; }
n            { std::cout << "|\\|" ; }
o            { std::cout << "{}" ; }
p            { std::cout << "|>"; }
q            { std::cout << "()." ; }
r            { std::cout << ".-" ; }
s            { std::cout << "$" ; }
t            { std::cout << "+"; }
u            { std::cout << "(_)" ; }
v            { std::cout << "\\/" ; }
w            { std::cout << "\\|/" ; }
x            { std::cout << "><"; }
y            { std::cout << "`/" ; }
z            { std::cout << "2" ; }

A            { std::cout << "\u00C0" ; }
B            { std::cout << "\u00DF" ; }
C            { std::cout << "\u00E7"; }
D            { std::cout << "\u00D0"; }
E            { std::cout << "\u00C8" ;  }
F            { std::cout << "\u1E1E" ; }
G            { std::cout << "\u01F4" ; }
H            { std::cout << "\u0409"; }
I            { std::cout << "\u0208" ; }
J            { std::cout << "\u01F0" ; }
K            { std::cout << "\u01E8" ; }
L            { std::cout << "\u013D"; }
M            { std::cout << "\u03FB" ; }
N            { std::cout << "\u0145" ; }
O            { std::cout << "\u038c" ; }
P            { std::cout << "\u1E56"; }
Q            { std::cout << "\u024A" ; }
R            { std::cout << "\u024C" ; }
S            { std::cout << "\u1E60" ; }
T            { std::cout << "\u1E6A"; }
U            { std::cout << "\u0172" ; }
V            { std::cout << "\u0194" ; }
W            { std::cout << "\u0174" ; }
X            { std::cout << "\u03D7"; }
Y            { std::cout << "\u0178" ; }
Z            { std::cout << "\u017D" ; }

"\."         { std::cout << "\u2134" ; }
"\?"         { std::cout << "\u2125" ; }
"\!"         { std::cout << "\u2142" ; }
"\,"         { std::cout << "\u2111" ; }
"\;"         { std::cout << "\u2130" ; }
"\:"         { std::cout << "\u2136" ; }
"\'"         { std::cout << "\u2180" ; }
"\""         { std::cout << "\u214C" ; }
" "          { std::cout << " " ; }
@            { std::cout << "\u2117" ; }

0         { std::cout << "\u213A" ; }
1         { std::cout << "\u2160" ; }
2         { std::cout << "\u2161" ; }
3         { std::cout << "\u2162" ; }
4         { std::cout << "\u2163" ; }
5         { std::cout << "\u2164" ; }
6         { std::cout << "\u2165" ; }
7         { std::cout << "\u2166" ; }
8         { std::cout << "\u2167" ; }
9         { std::cout << "\u2168" ; }



.              { }
"\n"           {std::cout <<std::endl; }
%%
int yywrap() { return 1; }
