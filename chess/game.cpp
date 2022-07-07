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
bool game::is_valid_move(piece* m_piece,const sf::Vector2f& position_to_move,board& c_board) const
{
	switch (m_piece->get_type())
	{
	case p_type::KING:
		if(m_piece->get_sprite().getPosition().x + 125.0f >= position_to_move.x &&
			m_piece->get_sprite().getPosition().x - 125.0f <= position_to_move.x &&
			m_piece->get_sprite().getPosition().y + 125.0f >= position_to_move.y &&
			m_piece->get_sprite().getPosition().y - 125.0f <= position_to_move.y &&
			(m_piece->get_colour() != c_board.find_piece_at_position(position_to_move)->get_colour() ||
			c_board.find_piece_at_position(position_to_move) == nullptr))
			// checks whether the pos to move is within the king's possible movement positions and that there is no piece or the piece is not of the same colour 
		{
			
		}
		break;
	case p_type::QUEEN:
		break;
	case p_type::BISHOP:
		break;
	case p_type::KNIGHT:
		break;
	case p_type::ROOK:
		break;
	case p_type::PAWN:
		break;
	}
	return true;
}
void game::update_previously_selected_piece(board& c_board)
{
	m_previously_selected_piece = c_board.find_piece_selected();
}
void game::move_piece(board& c_board)const 
{
	const sf::Vector2f pos_to_move_to = c_board.get_selected_square().getPosition();
	const sf::Vector2i adjusted(pos_to_move_to);
	if(c_board.get_square_state() && m_previously_selected_piece != nullptr)//if something has been selected
	{
		m_previously_selected_piece->set_pos(adjusted);
	}
}