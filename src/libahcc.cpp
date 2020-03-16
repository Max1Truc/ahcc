#include "libahcc.h"

int find_char_pos_in_set(std::set<char> my_set, char my_char) {
        int i = 0;
        for (std::set<char>::iterator it = my_set.begin(); it != my_set.end(); ++it) {
                if (*it == my_char) return i;
                i++;
        }

        return -1;
}

int compress(std::ifstream &input, std::ofstream &output) {
        // sets, give position of a char: find_char_pos_in_set(my_set, my_char)
        input.seekg(0, std::ios::end);
        int input_size = input.tellg();
        input.seekg(0, std::ios::beg);

        output << "AHCC0";

        std::set<char> usedchars;
        char tempchar;

        for (int i = 0; i < input_size; i++) {
                input.get(tempchar);
                usedchars.insert(tempchar);
        }

        std::cout << "Chars used: " << usedchars.size() << std::endl;

        for (std::set<char>::iterator it = usedchars.begin(); it != usedchars.end(); ++it) {
                output << *it;
        }
        output.write("\0", sizeof(char*));

        int sum = 1;

        if (usedchars.size() == 1) {
          // Only one character, we simply write the number of times it does appear
          output.write(reinterpret_cast<const char *>(&sum), sizeof(sum));
          return 0;
        }

        int pos = find_char_pos_in_set(usedchars, ',');
        std::cout << pos << std::endl;

        return 0;
}

int uncompress(std::ifstream &input, std::ofstream &output) {
        // sets, check char at a given position: *std::next(my_set.begin(), position)
        input.seekg(0, std::ios::end);
        int input_size = input.tellg();
        input.seekg(0, std::ios::beg);

        char tempchar;

        for (int i = 0; i < input_size; i++) {
                input.get(tempchar);
                if (i < 4) {
                        if ("AHCC0"[i] != tempchar) {
                                std::cerr << "Invalid or corrupted input file!" << std::endl;
                                return 1;
                        }
                }
        }
        return 0;
}
