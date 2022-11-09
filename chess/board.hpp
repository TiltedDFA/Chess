#pragma once
#include "piece.hpp"
#include <vector>
class board
{
public:
	board();
	~board();
	
	sf::Sprite get_piece_sprite(const int& index)const;
	sf::Sprite get_board_texture()const;
	short int get_num_pieces_left()const;

	piece* get_piece_at_index(const int& index)const;
	void delete_piece(const piece* m_piece);

	sf::RectangleShape get_selected_square() const;
	void update_selected_square(const sf::Vector2<int>& pos);
	bool get_square_state() const;
	void set_square_state(const bool& state);
	sf::Vector2i get_square_board_coordinates()const;

	void flip_board()const;

	piece* find_piece_selected()const;
	piece* find_piece_at_position(const sf::Vector2i& pos) const;
private:
	std::vector<piece*> m_pieces;

	sf::Sprite m_board_sprite;
	sf::Texture m_board_texture;

	//bool m_

	sf::RectangleShape m_selected_square;
	bool m_square_is_seleted = false;
};
