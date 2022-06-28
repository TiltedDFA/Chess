#include "display.hpp"
sf::Vector2<int> display::pos_to_coordinates(const int& x_pos, const int& y_pos)
{
	sf::Vector2<int> vector;
	vector.x = (x_pos - 1) * 125;
	vector.y = (y_pos - 1) * 125;
	return vector;	
}