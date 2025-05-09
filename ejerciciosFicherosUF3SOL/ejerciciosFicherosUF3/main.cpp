#include <iostream>
#include <fstream>
#include <istream> // Leer ficheros
#include <ostream> // Escribir ficheros
#include <string> // String


int main() {

	// std::fstream file1; // Leer y escribir
	// std::ifstream file2; // Solo leer
	// std::ofstream file2; // Solo es

	std::ifstream file1;
	file1.open("examen.txt");
	if (!file1.is_open())
	{
		std::cout << "Error al abrir el fichero" << std::endl;
		return 1;
	}
	char charInput;
	while (file1 >> charInput)
	{
		std::cout << charInput;
	}

	file1.close();


	std::ifstream file1;
	file1.open("examen.txt");
	if (!file1.is_open())
	{
		std::cout << "Error al abrir el fichero" << std::endl;
		return 1;
	}
	std::string stringInput;
	std::getline(file1, stringInput);
	std::cout << stringInput << std::endl;
}