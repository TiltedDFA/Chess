#pragma once
#include "piece.hpp"
#include "array"
class board
{
public:
	board();
	~board();

	void set_p_position(const sf::Vector2<int>& pos, const int& index);

	sf::Sprite get_p_sprite(const int& index);

	sf::Texture get_board_texture();

private:
	std::array<piece, 32>* pieces = new std::array<piece, 32>;
	sf::Texture m_board_texture;
};
