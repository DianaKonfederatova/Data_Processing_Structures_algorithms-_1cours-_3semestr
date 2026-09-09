#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void substring_search(std::ifstream& files, const std::string& searchword){
    std::string line;
    size_t T = searchword.length();
    int line_number = 1;
    int size_W = 0;
    bool found = false;

    while(std::getline(files, line)){
        size_t cur_line = line.length();

        if(cur_line < T){
            line_number++;
            continue;
        }  

        for(size_t i = 0; i<= cur_line; i++){
            size_t j;

            for (j = 0; j < T; j++){
                if(line[i + j] != searchword[j]){
                    break;
                }

            }

            if(j == T){
                std::cout << "Слово \"" << searchword << "\" найдено на строке " 
                          << line_number << ", позиция " << i << "\n";
                found = true;

            }

        }

        line_number++;
    }

    if (found == false) {
        std::cout << "Слово \"" << searchword << "\" не найдено в файле.\n";
    }
};

int main(){
    std::ofstream file("file_1.txt");

    if(file.is_open() == false){
        std::cout << "Ошибка создания файла\n";
        return 1;
    }

    file << "Yeah, yeah, yeah, yeah, yeah, yeah\n" 
    << "I think I did it again\n"
    << "I made you believe we're more than just friends\n"
    << "Oh, baby\n";

    file.close();

    std::ifstream file2("file_1.txt");
    if(file2.is_open() == false){
        std::cout << "Ошибка чтения файла\n";
        return 1;
    }

    substring_search(file2,"made");

    file2.close();    
}