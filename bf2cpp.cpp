#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

void translate(const std::string& brainfuck_code, std::ostream& out) {
    out << "#include \"brainfuck.hpp\"\n\n";
    out << "int main() {\n";
    out << "    Brainfuck bf;\n";
    out << "    \n";
    out << "    ";
    
    for (char c : brainfuck_code) {
        switch (c) {
            case '>':
                out << "++ ";
                break;
            case '<':
                out << "-- ";
                break;
            case '+':
                out << "+ ";
                break;
            case '-':
                out << "- ";
                break;
            case '.':
                out << "! ";
                break;
            case ',':
                out << "* ";
                break;
            case '[':
                out << "& ";
                break;
            case ']':
                out << "~ ";
                break;
            default:
                break;
        }
    }
    
    out << "bf;\n";
    out << "    \n";
    out << "    return 0;\n";
    out << "}\n";
}

int main(int argc, char* argv[]) {
    std::string input;
    
    if (argc == 1) {
        std::string line;
        while (std::getline(std::cin, line)) {
            input += line + "\n";
        }
        translate(input, std::cout);
    } else if (argc == 2) {
        std::ifstream file(argv[1]);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << argv[1] << std::endl;
            return 1;
        }
        std::string line;
        while (std::getline(file, line)) {
            input += line + "\n";
        }
        translate(input, std::cout);
    } else if (argc == 3) {
        std::ifstream in_file(argv[1]);
        if (!in_file.is_open()) {
            std::cerr << "Error: Cannot open input file " << argv[1] << std::endl;
            return 1;
        }
        std::ofstream out_file(argv[2]);
        if (!out_file.is_open()) {
            std::cerr << "Error: Cannot open output file " << argv[2] << std::endl;
            return 1;
        }
        std::string line;
        while (std::getline(in_file, line)) {
            input += line + "\n";
        }
        translate(input, out_file);
        std::cout << "Converting " << argv[1] << " -> " << argv[2] << std::endl;
    } else {
        std::cerr << "Usage: " << argv[0] << " [input_file] [output_file]" << std::endl;
        std::cerr << "  If no arguments: read from stdin, write to stdout" << std::endl;
        std::cerr << "  If one argument: read from file, write to stdout" << std::endl;
        std::cerr << "  If two arguments: read from input_file, write to output_file" << std::endl;
        return 1;
    }
    
    return 0;
}

