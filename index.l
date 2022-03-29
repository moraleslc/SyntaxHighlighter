RESERVADOS "_Packed"|"abstract"|"arguments"|"asm"|"auto"|"await"|"break"|"byte"|"case"|"catch"|"class"|"const"|"continue"|"debugger"|"default"|"delete"|"do"|"else"|"enum"|"eval"|"export"|"extends"|"extern"|"false"|"final"|"finally"|"for"|"friend"|"function"|"goto"|"if"|"implements"|"import"|"in"|"inline"|"instanceof"|"interface"|"let"|"native"|"new"|"operator"|"package"|"private"|"protected"|"public"|"register"|"return"|"sizeof"|"static"|"struct"|"super"|"switch"|"synchronized"|"template"|"this"|"throw"|"throws"|"transient"|"true"|"try"|"typedef"|"typeof"|"union"|"var"|"virtual"|"void"|"volatile"|"while"|"with"|"yield"

PREFUNCTION "abort"|"abs"|"acos"|"anchor"|"array"|"asin"|"atan"|"atexit"|"atof"|"atoi"|"atol"|"big"|"blink"|"bold"|"ceil"|"charAt"|"charCodeAt"|"clock"|"concat"|"constructor"|"cos"|"cosh"|"ctime"|"Date"|"div"|"every"|"exec"|"exit"|"exp"|"fabs"|"filter"|"fixed"|"floor"|"fmod"|"fontcolor"|"fontsize"|"forEach"|"getchar"|"getDate"|"getDay"|"getenv"|"getFullYear"|"getHours"|"getMilliseconds"|"getMinutes"|"getMonth"|"getSeconds"|"getTime"|"getTimezoneOffset"|"getUTCDate"|"getUTCDay"|"getUTCFullYear"|"getUTCHours"|"getUTCMilliseconds"|"getUTCMinutes"|"getUTCMonth"|"getUTCSeconds"|"getYear"|"indexOf"|"isalnum"|"isalpha"|"isdigit"|"isgraph"|"ispunct"|"isspace"|"isupper"|"italics"|"join"|"kbhit"|"lastIndexOf"|"length"|"link"|"localeCompare"|"log"|"log2"|"log10"|"map"|"match"|"max"|"memcmp"|"min"|"modf"|"parse"|"pop"|"pow"|"push"|"putchar"|"putenv"|"puts"|"rand"|"random"|"reduce"|"reduceRight"|"remove"|"rename"|"replace"|"reverse"|"round"|"search"|"setDate"|"setFullYear"|"setHours"|"setMilliseconds"|"setMinutes"|"setMonth"|"setSeconds"|"setTime"|"setUTCDate"|"setUTCFullYear"|"setUTCHours"|"setUTCMilliseconds"|"setUTCMinutes"|"setUTCMonth"|"setUTCSeconds"|"setYear"|"shift"|"sin"|"sinh"|"slice"|"small"|"some"|"sort"|"splice"|"split"|"sqrt"|"srand"|"strcat"|"strcmp"|"strerror"|"strike"|"sub"|"substr"|"substring"|"sup"|"tan"|"test"|"time"|"toDateString"|"toExponential"|"toFixed"|"toGMTString"|"toLocaleDateString"|"toLocaleFormat"|"toLocaleLowerCase"|"toLocaleString"|"toLocaleTimeString"|"toLocaleUpperCase"|"tolower"|"toLowerCase"|"toPrecision"|"toSource"|"toString"|"toTimeString"|"toupper"|"toUpperCase"|"toUTCString"|"unshift"|"UTC"|"value"|"valueOf"

PREPROCESSOR "#define"|"#elif"|"#else"|"#endif"|"#error"|"#if"|"#ifdef"|"#ifndef"|"#import"|"#include"|"#includepath"|"#line"|"#pragma"|"#script"|"#strict"|"#target"|"#targetengine"|"#undef"|"#using"

DATATYPE "BigInt"|"Boolean"|"char"|"double"|"float"|"int"|"long"|"null"|"Number"|"Object"|"short"|"signed"|"String"|"Symbol"|"undefined"|"unsigned"|"wchar_t"

OPERADORES  "."|"–>"|"++"|"&"|"^"|"="|"+="|"-="|"*="|","|"<<="|">>="|"%="|"&="|"="|"--"|"-"|"+"|"!"|"~"|"&"|"*"|"/"|"%"|"^="|"/="

OPERADORESLOG "<"|">"|"<="|">="|"!="|"=="

OPERADORESBIN "&&"|"||"|"|="|"|"|"&"

ESPECIALES "("|")"|"["|"]"|"{"|"}"

BOOLEANOS "True"|"true"|"False"|"false"

NUMEROS [0-9]+

%option c++ outfile="archivo.cpp" noyywrap

%{
    #include "index.h"
%}

%%

{RESERVADOS}    return RESERVADOS;
{PREFUNCTION}   return PREFUNCTION;
{PREPROCESSOR}  return PREPROCESSOR;
{DATATYPE}      return DATATYPE;
{OPERADORES}    return OPERADORES;
{OPERADORESLOG} return OPERADORESLOG;
{OPERADORESBIN} return OPERADORESBIN;
{ESPECIALES}    return ESPECIALES;
{BOOLEANOS}     return BOOLEANOS;
{NUMEROS}       return NUMEROS;
[a-zA-Z0-9_]+   return DEFAULT;
\n              return NEWLINE;
\"(.*)\"        return STRING;
\/\/.*          return COMENTARIOS;
.               return DEFAULT;

%%