#include <iostream>
#include <string>
#include "BTree.hpp"

int main() {
    BT::Tree    tree;
    std::string command;
    int         value;

    while (std::cin >> command) {
        if (command == "insere") {
            std::cin >> value;
            tree.insert(value);
            continue;
        }

        if (command == "percorre") {
            tree.traverse();
            std::cout << "\n";
            continue;
        }

        if (command == "busca") {
            std::cin >> value;
            if (tree.search(value)) {
                std::cout << "Valor " << value << " encontrado!" << std::endl;
                continue;
            }
            std::cout << "Valor " << value << " não encontrado!" << std::endl;
        }
    }
    return 0;
}
