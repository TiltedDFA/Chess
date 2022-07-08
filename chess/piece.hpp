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
	sf::Vector2<float> get_pos();
	void set_pos(const sf::Vector2<int>& pos);//used to initalize the position of the pieces
	void update_pos(const sf::Vector2<int>& pos);// used to move the pieces
	bool get_colour();
	void set_colour(const bool& state);
	sf::Sprite get_sprite();
	void set_image_for_sprite();

	bool get_move_state();
	void set_moved_true();
private:
	p_type m_piece_type;
	bool m_is_white;
	bool m_has_moved = false;
	sf::Sprite m_piece_image;
	sf::Texture m_full_image;
};
#endif

