#include <iostream>
#include <string>
#include <vector>

const int TABLE_SIZE = 13;

class TablaHash {
public:
    int hashFunction(const std::string& key) {
        uint32_t hashValue = 0;
        for (int i = key.length() - 1; i >= 0; --i) {
            hashValue += static_cast<uint32_t>(key[i]);
            if (i > 0) {
                hashValue = (hashValue << 4) ^ (hashValue >> 28);
            }
        }
        return hashValue % TABLE_SIZE;
    }
};

int main() {
    TablaHash tabla;
    std::vector<std::string> palabras = {"oro", "plata", "cobre", "originales", "arandano", "solidario"};
    
    for (const auto& palabra : palabras) {
        int posicion = tabla.hashFunction(palabra);
        std::cout << "La palabra '" << palabra << "' se inserta en la posición: " << posicion << std::endl;
    }
    
    return 0;
}