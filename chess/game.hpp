#pragma once
#include "board.hpp"
class game
{
public:
	static [[nodiscard]] sf::Vector2<int> pos_to_coordinates(const int& x_pos, const int& y_pos);
	void display_all_pieces(board& c_board, sf::RenderWindow& window);
private:
};
