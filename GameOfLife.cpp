// GameOfLife.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>


int main()
{
    std::cout << "Hello World!\n";
	std::ifstream myfile;
	myfile.open("InputFiles/random250_in.gol");
	std::string a;

	std::getline(myfile, a);

	std::vector<int> dimensions;

	std::string token;
	std::istringstream tokenStream(a);
	while (std::getline(tokenStream, token, ',')) {
		dimensions.push_back(std::stoi(token));
	}

	std::vector<std::vector<int>> board;
	int j = 0;
	while (std::getline(myfile, a)) {
		std::cout << a << std::endl;
		board.push_back(std::vector<int>());
		for (int i = 0; i < a.size(); i++) {
			board[j].push_back(a[i] == 'x' ? 1 : 0);
		}

		j++;
	}

	// Get size of board
	int x = dimensions[0];
	int y = dimensions[1];

	std::cout << x << " " << y << std::endl;
	std::cout << board.size() << std::endl;

	myfile.close();

	return 0;
}

// Programm ausführen: STRG+F5 oder "Debuggen" > Menü "Ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
