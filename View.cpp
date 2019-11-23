#include <iostream>
#include "View.h"

using namespace std;

View::View()
{
	this->size = 11;
	this->scale = 2;
	this->origin = Point2D(0, 0);
}
void View::Clear()
{
	// sets all the cells of the grid to the background
	// pattern shown in the sample output
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; i < size; j++)
		{
			this->grid[i][j][0] = '.';
			this->grid[i][j][0] = ' ';
		}
	}
		
}
void View::Plot(GameObject* ptr)
{
	// plots the pointed-to object in the proper cell of the grid
	// calls get_subscripts and if the subscipts are valid it calls DrawSelf() for the object
	// to insert the appropriate characters in the cell of the grid
	// the characters are replaced with '*' and '' to indicate that 
	// there is more than one object in that cell of the grid
	int out_x, out_y;
	bool validSubs = GetSubscripts(out_x, out_y, ptr->GetLocation()); // checking for valid subscripts 
	if (validSubs == true && grid[out_x][out_y][0] == '.') // valid and empty cell
	{
		ptr->DrawSelf(grid[out_x][out_y]);
	}
	else if (validSubs == true) // assign star 
	{
		grid[out_x][out_y][0] = '*';
		grid[out_x][out_y][1] = ' ';
	}
}
void View::Draw()
{
	// outputs the grid array to produce a display
	// the size, scale, and origin, are printed first
	// then each row and column, for the current size of the display.
	// note that the grid is plotted like a normal graph
	// the x and y axes are labeled with values for every alternate column and row
	// use the output stream formatting facilities to save
	// the format settings, set them for neat output
	// of the axis labels on the grid, and then restore them to their
	// original settings
	// Specifications: allow two characters for each numeric value of the 
	// axis labels, with no decimal points. The axis labels will be out of 
	// alignment and rounded off if their values cannot be represented well in two characters
	// this distortion is acceptable

	// printing graph
	int axis = view_maxsize; // for labeling x and y axis 
	int subtractor = 0; // to decrement axis values
	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 0) // if even print y axis value 
		{
			cout << axis - subtractor;
			if (axis - subtractor < 10)
			{
				// not two digits
				cout << " ";
			}
			subtractor = subtractor + 4;
		}
		else
		{
			// if odd dont print axis value
			cout << "  ";
		}

		// printing inner characters of graph
		for (int j = 0; j < size; j++)
		{
			// print grid characters
			cout << grid[i][j];
		}
		
		cout << endl;
	
	}

	// printing x axis
	for (int k = 0; k <= view_maxsize; k = k + 4)
	{
		if (k == 0)
		{
			cout << "  " << k << "   ";
		}
		else if (k == view_maxsize)
		{
			cout << k << endl;
		}
		else if (k < 10)
		{
			// not 2 digits
			cout << k << "   ";
		}
		else
		{
			cout << k << "  ";
		}
	}
}
bool View::GetSubscripts(int& out_x, int& out_y, Point2D location)
{
	int x, y; // to be assigned to out_x and out_y
	x = (location.x - origin.x) / scale;
	y = (location.y - origin.y) / scale;
	if (x > size || y > size)
	{
		// outside of display
		cout << "An object is outside the display" << endl;
		return false;
	}
	else
	{
		// subscripts are valid
		out_x = x;
		out_y = y;
		return true;
	}
}