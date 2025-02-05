#include <string>
#include <vector>

template <typename T>
class TablaHash {
public:
    TablaHash(int size);
    void insertar(const T& key);
    bool buscar(const T& key);
    void eliminar(const T& key);
    int hashFunction(const T& key);
    std::vector<T> obtenerElementos(int posicion); // Nueva función para obtener elementos en una posición
private:
    std::vector<std::vector<T>> tabla;
    int size;
};