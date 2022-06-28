#pragma once
#ifndef PIECE_HPP
#define PIECE_HPP
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#define PIECE_FILE_NAME "assets/chess_sprites.png"

enum class p_type
{
	KING = 0,
	QUEEN,
	BISHOP,
	KNIGHT,
	ROOK,
	PAWN
};

class piece
{
public:
	piece();
	~piece() = default;	

	p_type get_type();
	void set_type(const p_type& type);
	sf::Vector2<int> get_pos();
	void set_pos(const sf::Vector2<int>& pos);
	bool get_colour();
	void set_colour(const bool& state);
	sf::Sprite get_sprite();
	void set_image_for_sprite();
private:
	p_type m_piece_type;
	sf::Vector2<int> m_position;
	bool m_is_white;
	sf::Sprite m_piece_image;
	sf::Texture m_full_image;
};
#endif

