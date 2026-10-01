#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::ifstream archivo("datos/productos.csv");
  if (!archivo.is_open()) {
    std::cout << "no se pudo abrir el archivo" << std::endl;
  }

  return 0;
}
