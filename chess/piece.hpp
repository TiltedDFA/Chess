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
	piece(const piece&) = delete;

	p_type get_type()const;
	void set_type(const p_type& type);

	sf::Vector2<float> get_sprite_pos()const;
	void set_sprite_pos(const sf::Vector2<int>& pos);
	void update_sprite_pos(const sf::Vector2<int>& pos);

	bool get_colour()const;
	void set_colour(const bool& state);

	sf::Sprite get_sprite();
	void set_image_for_sprite();

	bool get_move_state();
	void set_moved_true();

	sf::Vector2i get_piece_position()const;
	void set_piece_position(const sf::Vector2i& pos);
	void update_sprite_pos();
private:
	p_type m_piece_type;
	sf::Sprite m_piece_image;
	inline static sf::Texture m_full_image = sf::Texture();
	bool m_is_white;
	bool m_has_moved = false;
	sf::Vector2i m_piece_pos;
};
#endif

