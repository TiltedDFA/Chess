#include "game.hpp"
bool operator==(const move& m1, const sf::Vector2i& m2)
{
	if(m1.target_pos.x != m2.x)
	{
		return false;
	}
	if (m1.target_pos.y != m2.y)
	{
		return false;
	}
	return true;
}
sf::Vector2<int> game::pos_to_coordinates(const sf::Vector2f& pos)
{
	sf::Vector2i vector;
	vector.x = static_cast<int>(pos.x / 125.0f) +1;
	vector.y = static_cast<int>(pos.y / 125.0f) +1;
	return vector;	
}
sf::Vector2f game::coordinates_to_pos(const sf::Vector2i& pos)
{
	sf::Vector2f vector;
	vector.x = static_cast<float>((pos.x - 1) * 125);
	vector.y = static_cast<float>((pos.y - 1) * 125);
	return vector;
}
bool game::is_move_legal(const p_type& piece_type, const sf::Vector2i& current_pos, const sf::Vector2i target_pos)
{
	if(target_pos.x > 8 || target_pos.y > 8 || target_pos.x < 1 || target_pos.y < 1
		|| target_pos == current_pos)
	{
		return false; 
	}
	switch(piece_type)
	{
	case p_type::KING:
		if (target_pos.x <= current_pos.x + 1 &&
			target_pos.x >= current_pos.x - 1 &&
			target_pos.y <= current_pos.y + 1 &&
			target_pos.y >= current_pos.y - 1 )
		{
			return true;
		}
		break;
	case p_type::QUEEN:
		bool valid_move_yet = false;
		if(target_pos.x == current_pos.x &&
			target_pos.y != current_pos.y ||
			target_pos.y == current_pos.y &&
			target_pos.x != current_pos.x)
		return valid_move_yet;
	}
	return false;
}
piece* game::get_last_selected_piece()const
{
	return m_previously_selected_piece;
}
void game::take_piece(piece* taking_piece, piece* piece_to_take, board& c_board)
{
	taking_piece->set_piece_position(piece_to_take->get_piece_position());
	c_board.delete_piece(piece_to_take);	
}
std::vector<move> game::generate_possible_moves(const piece* m_piece, const board& c_board)const
{
	std::vector<move> possible_moves;
	const sf::Vector2i piece_position = m_piece->get_piece_position();
	switch(m_piece->get_type())
	{
	case p_type::KING:
		for(int i = 0; i < 8; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + p_moves::king_moves[i][0];
			temp.y = piece_position.y + p_moves::king_moves[i][1];
			if (temp.x <= 8 &&
				temp.y <= 8 &&
				temp.x >= 1 &&
				temp.y >= 1 &&
				c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({{piece_position},{temp}});
			}
		}		
		break;
	case p_type::PAWN:
		if(m_piece->get_move_state() == false &&
			c_board.find_piece_at_position({piece_position.x,
				(m_piece->get_colour() ? piece_position.y + 2 : piece_position.y - 2) }) == nullptr)
			//this checks whether the pawn can move two spaces
		{
			possible_moves.push_back({ piece_position,{piece_position.x,
				(m_piece->get_colour() ? piece_position.y + 2 : piece_position.y - 2)} });
		}
		if(c_board.find_piece_at_position({ piece_position.x,
				(m_piece->get_colour() ? piece_position.y + 1 : piece_position.y - 1) }) == nullptr && 
			piece_position.x <= 8 &&
			piece_position.y <= 8 &&
			piece_position.x >= 1 &&
			piece_position.y >= 1)
			//this checks whether the pawn can move forward
		{
			possible_moves.push_back({ piece_position,{piece_position.x,
				(m_piece->get_colour() ? piece_position.y + 1 : piece_position.y - 1)} });
		}
		if(c_board.find_piece_at_position({ (piece_position.x + 1) ,
				(m_piece->get_colour() ? piece_position.y + 1 : piece_position.y - 1) }) != nullptr &&
			c_board.find_piece_at_position({ (piece_position.x + 1) ,
				(m_piece->get_colour() ? piece_position.y + 1 : piece_position.y - 1) })->get_colour() != m_piece->get_colour() )
		{
			possible_moves.push_back({ piece_position, {(piece_position.x + 1),(m_piece->get_colour() ? piece_position.y + 1 : piece_position.y - 1)} });
		}
		if (c_board.find_piece_at_position({ (piece_position.x - 1) ,
				(m_piece->get_colour() ? piece_position.y + 1 : piece_position.y - 1) }) != nullptr &&
			c_board.find_piece_at_position({ (piece_position.x - 1) ,
				(m_piece->get_colour() ? piece_position.y + 1 : piece_position.y - 1) })->get_colour() != m_piece->get_colour())
		{
			possible_moves.push_back({ piece_position, {(piece_position.x - 1),(m_piece->get_colour() ? piece_position.y + 1 : piece_position.y - 1)} });
		}
		break;
	case p_type::ROOK:
		for(int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + 0;
			temp.y = piece_position.y + (i+1);
			if(c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour() 
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + (i + 1);
			temp.y = piece_position.y + 0;
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + (-i -1);
			temp.y = piece_position.y + 0;
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + 0;
			temp.y = piece_position.y + (-i - 1);
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		break;
	case p_type::BISHOP:
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + (i + 1);
			temp.y = piece_position.y + (i + 1);
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + (i + 1);
			temp.y = piece_position.y + (-i -1);
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + (-i - 1);
			temp.y = piece_position.y + (i+1);
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + (-i - 1);
			temp.y = piece_position.y + (-i - 1);
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		break;
	case p_type::QUEEN:
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + (i + 1);
			temp.y = piece_position.y + (i + 1);
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if(c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + (i + 1);
			temp.y = piece_position.y + (-i - 1);
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if(c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + (-i - 1);
			temp.y = piece_position.y + (i + 1);
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + (-i - 1);
			temp.y = piece_position.y + (-i - 1);
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + 0;
			temp.y = piece_position.y + (i + 1);
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + (i + 1);
			temp.y = piece_position.y + 0;
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + (-i - 1);
			temp.y = piece_position.y + 0;
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		for (int i = 0; i < 7; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + 0;
			temp.y = piece_position.y + (-i - 1);
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() == m_piece->get_colour()
				)
			{
				break;
			}
			if (c_board.find_piece_at_position(temp) != nullptr &&
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()
				)
			{
				possible_moves.push_back({ piece_position, temp });
				break;
			}
			else if (c_board.find_piece_at_position(temp) == nullptr ||
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour() &&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
		break;
	case p_type::KNIGHT:
		for(int i = 0; i < 8; ++i)
		{
			sf::Vector2i temp;
			temp.x = piece_position.x + p_moves::knight_moves[i][0];
			temp.y = piece_position.y + p_moves::knight_moves[i][1];
			if(c_board.find_piece_at_position(temp) == nullptr || 
				c_board.find_piece_at_position(temp)->get_colour() != m_piece->get_colour()&&
				temp.x >= p_moves::min_bounds.x &&
				temp.y >= p_moves::min_bounds.y &&
				temp.x <= p_moves::max_bounds.x &&
				temp.y <= p_moves::max_bounds.y
				)
			{
				possible_moves.push_back({ piece_position, temp });
			}
		}
	}
	return possible_moves;
}
bool game::is_valid_move(piece* m_piece,const sf::Vector2i& position_to_move,board& c_board) const
{
	const std::vector<move> possible_moves = generate_possible_moves(m_piece,c_board);
	const auto position_in_possible_moves = 
		std::find(possible_moves.begin(), possible_moves.end(), position_to_move);
	if(position_in_possible_moves != possible_moves.end())
	{
		return true;
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
void game::move_piece(board& c_board,sf::Vector2i mouse_pos) 
{
	mouse_pos.x = mouse_pos.x - abs(static_cast<int>(mouse_pos.x) % 125);
	mouse_pos.y = mouse_pos.y - abs(static_cast<int>(mouse_pos.y) % 125);//finds the co-ords of the box which the mouse is in
	sf::Vector2i mouse_coords;
	mouse_coords.x = (mouse_pos.x / 125) + 1;
	mouse_coords.y = (mouse_pos.y / 125) + 1;

	//const sf::Vector2f pos_to_move_to = {static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y)} ;
	//const sf::Vector2i adjusted(pos_to_move_to);
	if(c_board.get_square_state() && m_previously_selected_piece != nullptr)//if something has been selected
	{
		if(is_valid_move(m_previously_selected_piece,mouse_coords,c_board))
		{
			if(c_board.find_piece_at_position(mouse_coords) == nullptr)
			{
				m_previously_selected_piece->set_piece_position(mouse_coords);
				m_previously_selected_piece->set_moved_true();
				c_board.set_square_state(false);
			}
			else
			{
				take_piece(m_previously_selected_piece, c_board.find_piece_at_position(mouse_coords), c_board);
			}
		}		
	}
}