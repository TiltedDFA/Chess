#include "game.hpp"
sf::Vector2<int> game::coordinates_to_pos(const sf::Vector2f& pos)
{
	sf::Vector2i vector;
	vector.x = static_cast<int>(pos.x / 125.0f) +1;
	vector.y = static_cast<int>(pos.y / 125.0f) +1;
	return vector;	
}
void game::display_all_pieces(board& c_board, sf::RenderWindow& window)
{
	
	window.draw(c_board.get_board_texture());
	for(int i = 0; i < 32;++i)
	{
		const auto temp = c_board.get_piece_at_index(i);
		temp->update_sprite_pos();
		window.draw(c_board.get_p_sprite(i));
	}
	if(c_board.get_square_state())
		window.draw(c_board.get_selected_square());
}
bool game::is_valid_move(piece* m_piece,const sf::Vector2f& position_to_move,board& c_board) const
{
	const sf::Vector2i adjusted_pos_to_move = coordinates_to_pos(position_to_move);
	switch (m_piece->get_type())
	{
	case p_type::KING:
		if(adjusted_pos_to_move.x +1 == m_piece->get_piece_position().x ||
			adjusted_pos_to_move.x == m_piece->get_piece_position().x ||
			adjusted_pos_to_move.x - 1 == m_piece->get_piece_position().x &&
			//the three statements above check whether the position the piece
			//wants to move to is within range of the king's possible x movements
			adjusted_pos_to_move.y + 1 == m_piece->get_piece_position().y ||
			adjusted_pos_to_move.y == m_piece->get_piece_position().y ||
			adjusted_pos_to_move.y - 1 == m_piece->get_piece_position().y &&
			//the three statements above check whether the position the piece
			//wants to move to is within range of the king's possible y movements
			c_board.find_piece_at_position(m_piece->get_piece_position()) == nullptr ||
			c_board.find_piece_at_position(m_piece->get_piece_position())->get_colour() != m_piece->get_colour()
			//This checks that there is no piece at the position that the king wants to move to or
			//that the piece at the position that the king wants to move to is not a piece of the same colour as the king
			)
		{
			return true;
		}
		return false;		
	case p_type::QUEEN:
		if (adjusted_pos_to_move.x + 1 == m_piece->get_piece_position().x ||
			adjusted_pos_to_move.x == m_piece->get_piece_position().x ||
			adjusted_pos_to_move.x - 1 == m_piece->get_piece_position().x &&
			//the three statements above check whether the position the piece
			//wants to move to is within range of the queen's possible x movements
			adjusted_pos_to_move.y + 1 == m_piece->get_piece_position().y ||
			adjusted_pos_to_move.y == m_piece->get_piece_position().y ||
			adjusted_pos_to_move.y - 1 == m_piece->get_piece_position().y &&
			//the three statements above check whether the position the piece
			//wants to move to is within range of the queen's possible y movements
			c_board.find_piece_at_position(m_piece->get_piece_position()) == nullptr ||
			c_board.find_piece_at_position(m_piece->get_piece_position())->get_colour() != m_piece->get_colour()
			//This checks that there is no piece at the position that the queen wants to move to or
			//that the piece at the position that the queen wants to move to is not a piece of the same colour as the queen
			)
		{
			return true;
		}
		return false;
	case p_type::BISHOP:
		break;
	case p_type::KNIGHT:
		break;
	case p_type::ROOK:
		break;
	case p_type::PAWN:
		if(m_piece->get_move_state() == false && 
			adjusted_pos_to_move.x == m_piece->get_piece_position().x + 2 &&
			adjusted_pos_to_move.y == m_piece->get_piece_position().y)
		{
			m_piece->set_moved_true();
			return true;
		}
		if(m_piece->get_move_state() == true &&
			adjusted_pos_to_move.x == m_piece->get_piece_position().x + 1 &&
			adjusted_pos_to_move.y == m_piece->get_piece_position().y)
		{
			return true;
		}
		if(true)
		break;
	}
	return false;
}
void game::update_previously_selected_piece(board& c_board)
{
	if(c_board.get_square_state())
	{
		m_previously_selected_piece = c_board.find_piece_selected();
	}
	else
	{
		m_previously_selected_piece = nullptr;
	}
}
void game::move_piece(board& c_board,sf::Vector2i mouse_pos)const 
{
	mouse_pos.x = mouse_pos.x - abs(static_cast<int>(mouse_pos.x) % 125);
	mouse_pos.y = mouse_pos.y - abs(static_cast<int>(mouse_pos.y) % 125);//finds the co-ords of the box which the mouse is in
	sf::Vector2i mouse_coords;
	const sf::Vector2f f_mouse_pos(mouse_pos);
	mouse_coords.x = (mouse_pos.x / 125) + 1;
	mouse_coords.y = (mouse_pos.y / 125) + 1;

	//const sf::Vector2f pos_to_move_to = {static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y)} ;
	//const sf::Vector2i adjusted(pos_to_move_to);
	if(c_board.get_square_state() && m_previously_selected_piece != nullptr)//if something has been selected
	{
		if(is_valid_move(m_previously_selected_piece,f_mouse_pos,c_board))
		{
			m_previously_selected_piece->set_piece_position(mouse_coords);
			c_board.set_square_state(false);
		}		
	}
}