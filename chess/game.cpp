#include "game.hpp"
sf::Vector2<int> game::pos_to_coordinates(const int& x_pos, const int& y_pos)
{
	sf::Vector2<int> vector;
	vector.x = (x_pos - 1) * 125;
	vector.y = (y_pos - 1) * 125;
	return vector;	
}
void game::display_all_pieces(board& c_board, sf::RenderWindow& window)
{
	window.draw(c_board.get_board_texture());
	for(int i = 0; i < 32;++i)
	{
		window.draw(c_board.get_p_sprite(i));
	}
	if(c_board.get_square_state())
		window.draw(c_board.get_selected_square());
}