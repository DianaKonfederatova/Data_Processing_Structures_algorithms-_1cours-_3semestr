#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

void print_text(std::ifstream& files){
    std::string line;

    while(std::getline(files, line)){
        std::cout << line << "\n";
    }

}

void substring_search(std::ifstream& files, const std::string& searchword, long long& n_comp){
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

        for(size_t i = 0; i<= cur_line - T; i++){
            size_t j;

            for (j = 0; j < T; j++){
                n_comp++; 
                if(std::tolower(line[i + j]) != std::tolower(searchword[j])){
                    break;
                }

            }

            if(j == T){
                std::cout << "Подстрока, в которой найдено слово:\n";
                std::cout <<line << "\n" << "\n";
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

long long hash_value(const std::string& str){
    size_t cur_line = str.length();
    long long h = 0;
    long long q = 1000000007;

    for (size_t i = 0; i < cur_line; i++){

        unsigned char S = static_cast<unsigned char>(str[i]);
        h = ((h * 256) + S) % q;
    }

    return h;
}

void RabinKarp (std::ifstream& files, const std::string& searchword, long long& n_comp){
    std::string line;
    size_t m = searchword.length();
    int line_number = 1;
    bool found = false;

    std::string needle = searchword;
    for (char &c : needle) c = std::tolower(static_cast<unsigned char>(c));
    long long hash_needle = hash_value(needle);

    while(std::getline(files, line)){
        size_t n = line.length();

        if (n < m){
            line_number++;
            continue;
        }

        std::string haystack = line;
        for (char &c : haystack) c = std::tolower(static_cast<unsigned char>(c));
        long long hash_haystack = hash_value(haystack.substr(0, m));

        for(size_t i = 0; i <= n - m; i++){

            if(hash_haystack == hash_needle){

                bool match = true;
                for (size_t j = 0; j < m; j++) {
                    n_comp++; 
                    if (haystack[i + j] != needle[j]) {
                        match = false;
                        break;
                    }
                }

                if(match){
                    std::cout << "Подстрока, в которой найдено слово:\n";
                    std::cout << line << "\n" << "\n";
                    std::cout << "Слово \"" << searchword << "\" найдено методом Рабина-Карпа на строке " 
                              << line_number << ", позиция " << i << "\n";
                    found = true;
                }


            }

            if (i < n - m) {
                hash_haystack = hash_value(haystack.substr(i + 1, m));
            }
            

        }

        line_number++;

    }

    if (found == false) {
        std::cout << "Слово \"" << searchword << "\" не найдено методом Рабина-Карпа.\n";
    }

}


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

    std::cout << "Текст:\n" << "\n";
    print_text(file2);
    std::cout << "\n";
    file2.clear();
    file2.seekg(0);

    long long ss_comp = 0;
    long long rk_comp = 0;

    std::cout << "МЕТОД ПРЯМОГО ПОИСКА\n" << "\n";

    substring_search(file2,"yeah",ss_comp);

    file2.clear();
    file2.seekg(0);

    std::cout << "\n";

    std::cout << "\n\nМЕТОД РАБИНА-КАРПА\n\n";
    RabinKarp(file2, "yeah", rk_comp);

    std::cout << "\n\nКОЛИЧЕСТВО СРАВНЕНИЙ ДВУХ МЕТОДОВ\n\n";
    std::cout << "Количество сравнений прямого поиска: " << ss_comp << "\n";
    std::cout << "Количество сравнений методом Рабина-Карпа: " << rk_comp << "\n";
    file2.close();    
}