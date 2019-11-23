#include <iostream>
#include "Building.h"

using namespace std;

Building::Building(): GameObject('B')
{
	this->display_code = 'B';
	this->pokemon_count = 0;
	cout << "Building default constructed" << endl;
}

Building::Building(char in_code, int in_Id, Point2D in_loc): GameObject('B')
{
	this -> id_num = in_Id;
	this->location = in_loc;
	this->display_code = in_code;
	this->pokemon_count = 0;
	cout << "Building constructed" << endl;
}

void Building::AddOnePokemon(void)
{
	this->pokemon_count = pokemon_count + 1;
}

void Building::RemoveOnePokemon(void)
{
	this->pokemon_count = pokemon_count - 1;
}

void Building::ShowStatus(void)
{
	cout << display_code << id_num << " located at " << location << endl;
	if (pokemon_count == 1)
	{
		cout << pokemon_count << " pokemon is in this building" << endl;
	}
	else
	{
		cout << pokemon_count << " pokemon are in this building" << endl;
	}
}

bool Building::ShouldBeVisible(void)
{
	return true;
}