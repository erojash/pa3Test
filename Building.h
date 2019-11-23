#ifndef BUILDING_H
#define BUILDING_H
#include "GameObject.h"

class Building: public GameObject
{
public:
	Building();
	Building(char in_code, int in_Id, Point2D in_loc);
	void AddOnePokemon();
	void RemoveOnePokemon();
	void ShowStatus();
	bool ShouldBeVisible();
private:
	unsigned int pokemon_count;
};
#endif // !BUILDING_H
