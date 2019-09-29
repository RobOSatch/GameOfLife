// GameOfLife.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

#include "FileManager.h"

using namespace std;

enum MODE {
	seq
};

int main(int argc, char* argv[])
{
	string inputfile;
	string outputfile;
	int generations = 0;
	bool shouldMeasure = false;
	MODE mode;

	// Perform argument stuff
	for (int i = 0; i < argc; i++) {
		string currentArgument = argv[i];

		if (currentArgument == "--load") {
			inputfile = argv[i + 1];
		}

		if (currentArgument == "--generations") {
			generations = stoi(argv[i + 1]);
		}

		if (currentArgument == "--save") {
			outputfile = argv[i + 1];
		}

		if (currentArgument == "--measure") {
			shouldMeasure = true;
		}

		if (currentArgument == "--mode") {
			if (argv[i + 1] == "seq") {
				mode = seq;
			}
		}
	}
	
	Board* board = FileManager::importFile(inputfile);
	board->advanceGenerationsBy(generations);
	FileManager::exportFile(*board, outputfile);

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
