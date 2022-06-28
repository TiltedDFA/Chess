#pragma once
#include "board.hpp"
class display
{
public:
	static [[nodiscard]] sf::Vector2<int> pos_to_coordinates(const int& x_pos, const int& y_pos);
private:
};
