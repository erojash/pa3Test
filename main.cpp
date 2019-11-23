#include <iostream>
#include <stdlib.h>
#include "GameCommand.h"
#include "View.h"


using namespace std;

int main()
{
	cout << "Introduction to Software Engineering" << endl;
	cout << "Fall 2019 \nProgramming Assignment 3\n\n";
	Model model;
	View view;
	//view.Clear();
	char commandCode; // user input for command
	int pokemon_id; // user input for pokemon id
	double p1_x; // user input for pokemon destination x 
	double p1_y; // user input for pokemon destination y
	int gym_id; // user input for pokemon gym id
	int center_id; // user input for pokemon center id
	unsigned int stamina_points; // user input for stamina points
	unsigned int training_units; // user input for training units
	model.Display(view);
	model.ShowStatus();
	cout << "\n\n";
	while (commandCode != 'q')
	{
		cin >> commandCode;
		cout << "Enter command: ";
		switch (commandCode)
		{
		case 'm':
			cin >> pokemon_id;
			cin >> p1_x;
			cin >> p1_y;
			DoMoveCommand(model, pokemon_id, Point2D(p1_x, p1_y));
			break;
		case 'g':
			cin >> pokemon_id;
			cin >> gym_id;
			DoMoveToGymCommand(model, pokemon_id, gym_id);
			break;
		case 'c':
			cin >> pokemon_id;
			cin >> center_id;
			DoMoveToCenterCommand(model, pokemon_id, center_id);
			break;
		case 's':
			cin >> pokemon_id;
			DoStopCommand(model, pokemon_id);
			break;
		case 'r':
			cin >> pokemon_id;
			cin >> stamina_points;
			DoRecoverInCenterCommand(model, pokemon_id, stamina_points);
			break;
		case 't':
			cin >> pokemon_id;
			cin >> training_units;
			DoTrainInGymCommand(model, pokemon_id, training_units);
			break;
		case 'v':
			DoGoCommand(model, view);
			break;
		case 'x':
			DoRunCommand(model, view);
			break;
		case 'q':
			exit(EXIT_FAILURE);
		default:
			cout << "Error: Please enter a valid command!" << endl;
		}	
	} 


	return 0;
}