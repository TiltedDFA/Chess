#include "board.hpp"
board::board()
{
	pieces->at(0).set_colour(true);
	pieces->at(0).set_type(p_type::KING);
	pieces->at(0).set_pos({ 5,1 });
	pieces->at(0).set_image_for_sprite();

	pieces->at(1).set_colour(false);
	pieces->at(1).set_type(p_type::KING);
	pieces->at(1).set_pos({ 5,8 });
	pieces->at(1).set_image_for_sprite();

	pieces->at(2).set_colour(true);
	pieces->at(2).set_type(p_type::QUEEN);
	pieces->at(2).set_pos({ 4,1 });
	pieces->at(2).set_image_for_sprite();

	pieces->at(3).set_colour(false);
	pieces->at(3).set_type(p_type::QUEEN);
	pieces->at(3).set_pos({ 4,8 });
	pieces->at(3).set_image_for_sprite();


	pieces->at(4).set_colour(true);
	pieces->at(4).set_type(p_type::BISHOP);
	pieces->at(4).set_pos({ 3,1 });
	pieces->at(4).set_image_for_sprite();

	pieces->at(5).set_colour(true);
	pieces->at(5).set_type(p_type::BISHOP);
	pieces->at(5).set_pos({ 6,1 });
	pieces->at(5).set_image_for_sprite();

	pieces->at(6).set_colour(false);
	pieces->at(6).set_type(p_type::BISHOP);
	pieces->at(6).set_pos({ 3,8 });
	pieces->at(6).set_image_for_sprite();

	pieces->at(7).set_colour(false);
	pieces->at(7).set_type(p_type::BISHOP);
	pieces->at(7).set_pos({ 6,8 });
	pieces->at(7).set_image_for_sprite();


	pieces->at(8).set_colour(true);
	pieces->at(8).set_type(p_type::KNIGHT);
	pieces->at(8).set_pos({ 2,1 });
	pieces->at(8).set_image_for_sprite();

	pieces->at(9).set_colour(true);
	pieces->at(9).set_type(p_type::KNIGHT);
	pieces->at(9).set_pos({ 7,1 });
	pieces->at(9).set_image_for_sprite();

	pieces->at(10).set_colour(false);
	pieces->at(10).set_type(p_type::KNIGHT);
	pieces->at(10).set_pos({ 2,8 });
	pieces->at(10).set_image_for_sprite();

	pieces->at(11).set_colour(false);
	pieces->at(11).set_type(p_type::KNIGHT);
	pieces->at(11).set_pos({ 7,8 });
	pieces->at(11).set_image_for_sprite();


	pieces->at(12).set_colour(true);
	pieces->at(12).set_type(p_type::ROOK);
	pieces->at(12).set_pos({ 1,1 });
	pieces->at(12).set_image_for_sprite();

	pieces->at(13).set_colour(true);
	pieces->at(13).set_type(p_type::ROOK);
	pieces->at(13).set_pos({ 8,1 });
	pieces->at(13).set_image_for_sprite();

	pieces->at(14).set_colour(false);
	pieces->at(14).set_type(p_type::ROOK);
	pieces->at(14).set_pos({ 1,8 });
	pieces->at(14).set_image_for_sprite();

	pieces->at(15).set_colour(false);
	pieces->at(15).set_type(p_type::ROOK);
	pieces->at(15).set_pos({ 8,8 });
	pieces->at(15).set_image_for_sprite();

	for (int j = 0; j < 2; ++j) {
		for (int i = 0; i < 8; ++i) {
			pieces->at(16+i +8*j).set_colour(j);
			pieces->at(16 + i + 8 * j).set_pos({ (i + 1),(j == 1) ? 2:7 });
			pieces->at(16 + i + 8 * j).set_type(p_type::PAWN);
			pieces->at(16 + i + 8 * j).set_image_for_sprite();
		}
	}

	m_board_texture.loadFromFile("assets/board.png");
}
board::~board()
{
	delete pieces;
}
sf::Sprite board::get_p_sprite(const int& index)
{
	return pieces->at(index).get_sprite();
}
sf::Texture board::get_board_texture()
{
	return m_board_texture;
}
