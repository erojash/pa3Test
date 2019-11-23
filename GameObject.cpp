#include <iostream>
#include "GameObject.h"
#include <stdlib.h>

using namespace std;

GameObject::GameObject(char in_code)
{
	this->display_code = in_code;
	this->id_num = 1;
	this->state = '0';
	cout << "GameObject constructed" << endl;
}
GameObject::GameObject(Point2D in_loc, int in_id, char in_code)
{
	this->display_code = in_code;
	this->id_num = in_id;
	this->location = in_loc;
	this->state = '0';
	cout << "GameObject constructed" << endl;
}
GameObject::~GameObject()
{
	cout << "GameObject destructed" << endl;
}
Point2D GameObject::GetLocation()
{
	return location;
}
int GameObject::GetId()
{
	return id_num;
}
char GameObject::GetState()
{
	return state;
}
void GameObject::DrawSelf(char* ptr)
{
	// puts the display_code at the character pointed to by the ptr
	// and then the ASCII character for the id_num in the next character
	ptr[0] = display_code;
	ptr[1] = '0' + id_num;
}
void GameObject::ShowStatus()
{
	cout << display_code << id_num << " at " << location << endl;
}