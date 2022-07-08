#pragma once
#include "piece.hpp"
#include <vector>
class board
{
public:
	board();
	~board();

	void set_p_position(const sf::Vector2<float>& pos, piece* p_piece);
	sf::Sprite get_p_sprite(const int& index);
	sf::Sprite get_board_texture();
	void delete_piece(const int& index);
	sf::RectangleShape get_selected_square() const;
	void update_selected_square(const sf::Vector2<int>& pos);
	bool get_square_state() const;
	void set_square_state(const bool& state);
	void flip_board()const;
	piece* find_piece_selected()const;
	piece* find_piece_at_position(const sf::Vector2f& pos) const;
private:
	std::vector<piece*> m_pieces;
	sf::Sprite m_board_sprite;
	sf::Texture m_board_texture;
	sf::RectangleShape m_selected_square;
	bool m_square_is_seleted = false;
};
