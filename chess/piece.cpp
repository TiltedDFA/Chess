#include "piece.hpp"
piece::piece()
{
	m_piece_type = p_type::KING;
	m_is_white = true;
	m_full_image.loadFromFile(PIECE_FILE_NAME);
	m_piece_pos = { 0,0 };
}

p_type piece::get_type()const
{
	return m_piece_type;
}
void piece::set_type(const p_type& type)
{
	m_piece_type = type;
}
sf::Vector2<float> piece::get_sprite_pos()const
{
	return m_piece_image.getPosition();
}
void piece::set_sprite_pos(const sf::Vector2<int>& pos)
{
	const sf::Vector2<float> adjusted_pos = { static_cast<float>(pos.x),static_cast<float>(pos.y)};
	m_piece_image.setPosition(adjusted_pos);	
}
void piece::update_sprite_pos(const sf::Vector2<int>& pos)
{
	m_piece_image.move(static_cast<float>(pos.x),static_cast<float>(pos.y));
}
bool piece::get_colour()const
{
	return m_is_white;
}
void piece::set_colour(const bool& state)
{
	m_is_white = state;
}
sf::Sprite piece::get_sprite()
{
	return m_piece_image;
}
void piece::set_image_for_sprite()
{	
	m_piece_image.setTexture(m_full_image);
	switch (m_piece_type)
	{
	case p_type::KING:
		m_is_white ? m_piece_image.setTextureRect({5,10,125,125})
			: m_piece_image.setTextureRect({ 4,141,125,125 });
		break;
	case p_type::QUEEN:
		m_is_white ? m_piece_image.setTextureRect({ 138,4,125,125 })
			: m_piece_image.setTextureRect({138,139,125,125 });
		break;
	case p_type::BISHOP:
		m_is_white ? m_piece_image.setTextureRect({ 272,4,125,125 })
			: m_piece_image.setTextureRect({ 272,137,125,125 });
		break;
	case p_type::KNIGHT:
		m_is_white ? m_piece_image.setTextureRect({ 405,8,125,125 })
			: m_piece_image.setTextureRect({ 405,142,125,125 });
		break;
	case p_type::ROOK:
		m_is_white ? m_piece_image.setTextureRect({ 542,9,125,125 })
			: m_piece_image.setTextureRect({ 542,143,125,125 });
		break;
	case p_type::PAWN:
		m_is_white ? m_piece_image.setTextureRect({ 674,4,125,125 })
			: m_piece_image.setTextureRect({ 675,138,125,125 });
		break;
	}
}
bool piece::get_move_state()
{
	return m_has_moved;
}
void piece::set_moved_true()
{
	m_has_moved = true;
}
sf::Vector2i piece::get_piece_position()const
{
	return m_piece_pos;
}
void piece::set_piece_position(const sf::Vector2i& pos)
{
	m_piece_pos = pos;
}
void piece::update_sprite_pos()
{
	m_piece_image.setPosition(static_cast<float>(m_piece_pos.x - 1) * 125.0f, static_cast<float>(m_piece_pos.y - 1) * 125.0f);
}