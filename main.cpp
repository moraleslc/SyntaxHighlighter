#include <FlexLexer.h>
#include <fstream>
#include <chrono>
#include "index.h"
#include <dirent.h>
#include <filesystem>
#include <vector>
#include <iostream>
#include <thread>
#include <string>
namespace fs = std::filesystem;
using namespace std;

std::vector<std::vector<string>> SplitVector(const std::vector<string>& vec, size_t n)
{
    std::vector<std::vector<string>> outVec;

    size_t length = vec.size() / n;
    size_t remain = vec.size() % n;

    size_t begin = 0;
    size_t end = 0;

    for (size_t i = 0; i < std::min(n, vec.size()); ++i)
    {
        end += (remain > 0) ? (length + !!(remain--)) : length;

        outVec.push_back(std::vector<string>(vec.begin() + begin, vec.begin() + end));

        begin = end;
    }

    return outVec;
}

int archivos(string nombrearch, int x){

    auto start = std::chrono::high_resolution_clock::now();

        ifstream* archivo= new ifstream(nombrearch);    
        yyFlexLexer* lex= new yyFlexLexer(archivo);

        string filesname = "./pruebashtml/salida" + std::to_string(x) + ".html";
    
        ofstream archivosalida(filesname);
        archivosalida<<"<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n    <link rel=\"stylesheet\" href=\"style.css\">\n    <meta charset=\"UTF-8\">\n    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n    <title>Document</title>\n</head>\n<body>";

        while (1)
        {
            switch (lex->yylex())
            {
            case 0:{
                archivosalida<<"</body>\n</html>";

                auto stop = std::chrono::high_resolution_clock::now();

                std::cout << "Tiempo total: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()<< " microsegundos." << std::endl;

                return 0;
            }
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

void procesarlista(vector <string> lista){
    for (size_t i = 0; i < lista.size(); i++)
    {
        archivos(lista[i], i);
    }
        
}

int main(int argc, const char** argv) {

    auto start = std::chrono::high_resolution_clock::now();

    int numthreads=1;

    std::string path = "./pruebas";
    vector<string> vect;
    for (const auto & entry : fs::recursive_directory_iterator(path)){
        if (!fs::is_directory(entry)){
            // std::cout << entry.path().string() << std::endl;

            vect.push_back(entry.path());
        }
    }

    auto prueba=SplitVector(vect, numthreads);    
    vector <thread> thrds;

    for (auto x: prueba){
        thrds.push_back(thread(procesarlista, x));
    }

    for (size_t i = 0; i < thrds.size(); i++)
    {
        thrds[i].join();
    }
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "Tiempo total de ejecución: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()<< " milisegundos." << std::endl;

    return (0);
    
}