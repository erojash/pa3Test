#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Point2D.h"
#include "Vector2D.h"

using namespace std;

class GameObject
{
protected:
	Point2D location; // location of the object
	int id_num; 
	char display_code; // how the object is represented in the View
	char state; // state of the object
public:
	GameObject(char in_code);
	GameObject(Point2D in_loc, int in_id, char in_code);
	virtual ~GameObject();
	Point2D GetLocation();
	int GetId();
	char GetState();
	void DrawSelf(char* ptr);
	// pure virtual functions
	virtual void ShowStatus() = 0;
	virtual bool Update() = 0;
	virtual bool ShouldBeVisible() = 0;
};
#endif 
