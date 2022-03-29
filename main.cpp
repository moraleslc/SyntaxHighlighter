#include <FlexLexer.h>
#include <fstream>
#include <chrono>
#include "index.h"
using namespace std;

int main(int argc, const char** argv) {

    std::chrono::system_clock::time_point stop;

    auto start = std::chrono::high_resolution_clock::now();

    --argc, ++argv;
    if (argc>0)
    {
        ifstream* archivo= new ifstream(argv[0]);    
        yyFlexLexer* lex= new yyFlexLexer(archivo);
    
        ofstream archivosalida("salida.html");
        archivosalida<<"<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n    <link rel=\"stylesheet\" href=\"style.css\">\n    <meta charset=\"UTF-8\">\n    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n    <title>Document</title>\n</head>\n<body>";

        while (1)
        {
            switch (lex->yylex())
            {
            case 0:
                archivosalida<<"</body>\n</html>";

                stop = std::chrono::high_resolution_clock::now();

                std::cout << "Tiempo total: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()<< " microsegundos." << std::endl;

                return 0;
            
            case RESERVADOS:
                archivosalida<<"<span class=\"reservados\">"<<lex->YYText()<<"</span>";
                break;

            case NUMEROS:
                archivosalida<<"<span class=\"numeros\">"<<lex->YYText()<<"</span>";
                break;
                
            case OPERADORES:
                archivosalida<<"<span class=\"operadores\">"<<lex->YYText()<<"</span>";
                break;

            case BOOLEANOS:
                archivosalida<<"<span class=\"booleanos\">"<<lex->YYText()<<"</span>";
                break;

            case ESPECIALES:
                archivosalida<<"<span class=\"especiales\">"<<lex->YYText()<<"</span>";
                break;

            case DEFAULT:
                archivosalida<<"<span>"<<lex->YYText()<<"</span>";
                break;

            case NEWLINE:
                archivosalida<<"<br>";
                break;

            case STRING:
                archivosalida<<"<span class=\"string\">"<<lex->YYText()<<"</span>";
                break;

            //comentario
            case COMENTARIOS:
                archivosalida<<"<span class=\"comentarios\">"<<lex->YYText()<<"</span>";
                break;
            
            case OPERADORESLOG:
                archivosalida<<"<span class=\"operadoreslog\">"<<lex->YYText()<<"</span>";
                break;

            case OPERADORESBIN:
                archivosalida<<"<span class=\"operadoresbin\">"<<lex->YYText()<<"</span>";
                break;

            case PREFUNCTION:
                archivosalida<<"<span class=\"prefunction\">"<<lex->YYText()<<"</span>";
                break;

            case DATATYPE:
                archivosalida<<"<span class=\"datatype\">"<<lex->YYText()<<"</span>";
                break;

            case PREPROCESSOR:
                archivosalida<<"<span class=\"preprocessor\">"<<lex->YYText()<<"</span>";
                break;
            }
        }


        
    }
    
}