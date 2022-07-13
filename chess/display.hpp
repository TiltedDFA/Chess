#pragma once
#include "game.hpp"

namespace display
{
	void all_pieces(board& c_board, sf::RenderWindow& window);
	void possible_moves(std::vector<move> p_moves, sf::RenderWindow& window);
}
