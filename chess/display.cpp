#include "display.hpp"
void display::all_pieces(board& c_board, sf::RenderWindow& window)
{
	window.draw(c_board.get_board_texture());
	for (int i = 0; i < c_board.get_num_pieces_left(); ++i)
	{
		const auto temp = c_board.get_piece_at_index(i);
		temp->update_sprite_pos();
		window.draw(c_board.get_piece_sprite(i));
	}
	if (c_board.get_square_state())
		window.draw(c_board.get_selected_square());
}
void display::possible_moves(std::vector<move> p_moves, sf::RenderWindow& window)
{
	for(const auto& i : p_moves)
	{
		sf::Vector2f to_display = game::coordinates_to_pos(i.target_pos);
		sf::RectangleShape square_to_display;
		square_to_display.setPosition(to_display);
		square_to_display.setFillColor(sf::Color(255, 0, 0, 128));
		square_to_display.setSize({ 125.0f,125.0f });
		window.draw(square_to_display);
	}	
}