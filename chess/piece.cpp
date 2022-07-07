#include "piece.hpp"
piece::piece()
{
	m_piece_type = p_type::KING;
	m_is_white = true;
	m_full_image.loadFromFile(PIECE_FILE_NAME);		
}

p_type piece::get_type()
{
	return m_piece_type;
}
void piece::set_type(const p_type& type)
{
	m_piece_type = type;
}
sf::Vector2<float> piece::get_pos()
{
	return m_piece_image.getPosition();
}
void piece::set_pos(const sf::Vector2<int>& pos)
{
	sf::Vector2<float> adjusted_pos = { (static_cast<float>(pos.x)-1) * 125.0f
		,(static_cast<float>(pos.y)-1) * 125.0f };
	switch (m_piece_type)
	{
	case p_type::KING:
		adjusted_pos.x += 10;
		adjusted_pos.y += 7;
		break;
	case p_type::QUEEN:
		adjusted_pos.x += 5;
		adjusted_pos.y += 10;
		break;
	case p_type::BISHOP:
		adjusted_pos.x += 10;
		adjusted_pos.y += 10;
		break;
	case p_type::KNIGHT:
		adjusted_pos.x += 10;
		adjusted_pos.y += 10;
		break;
	case p_type::ROOK:
		adjusted_pos.x += 15;
		adjusted_pos.y += 15;
		break;
	case p_type::PAWN:
		adjusted_pos.x += 20;
		adjusted_pos.y += 20;
		break;
	}
	m_piece_image.setPosition(adjusted_pos);	
}
void piece::update_pos(const sf::Vector2<int>& pos)
{
	m_piece_image.setPosition(
		m_piece_image.getPosition().x - (static_cast<float>(pos.x)-1) * 125.0f
		, m_piece_image.getPosition().y - (static_cast<float>(pos.y)-1) * 125.0f
	);
}
bool piece::get_colour()
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
		m_is_white ? m_piece_image.setTextureRect({15,17,105,105})
			: m_piece_image.setTextureRect({ 14,148,105,105 });
		break;
	case p_type::QUEEN:
		m_is_white ? m_piece_image.setTextureRect({ 143,14,114,105 })
			: m_piece_image.setTextureRect({143,149,114,107});
		break;
	case p_type::BISHOP:
		m_is_white ? m_piece_image.setTextureRect({ 282,14,103,104 })
			: m_piece_image.setTextureRect({ 282,147,103,104 });
		break;
	case p_type::KNIGHT:
		m_is_white ? m_piece_image.setTextureRect({ 415,18,100,100 })
			: m_piece_image.setTextureRect({ 415,152,100,100 });
		break;
	case p_type::ROOK:
		m_is_white ? m_piece_image.setTextureRect({ 557,24,86,94 })
			: m_piece_image.setTextureRect({ 557,158,86,94 });
		break;
	case p_type::PAWN:
		m_is_white ? m_piece_image.setTextureRect({ 694,24,74,96 })
			: m_piece_image.setTextureRect({ 695,158,74,95 });
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