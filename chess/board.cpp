#include "board.hpp"
board::board()
{
	for(int i =0; i < 32; ++i)
	{
		auto* temp_ptr = new piece;
		m_pieces.emplace_back(temp_ptr);
	}

	m_pieces[0]->set_colour(true);
	m_pieces[0]->set_type(p_type::KING);
	m_pieces[0]->set_pos({ 375,0 });
	m_pieces[0]->set_image_for_sprite();

	m_pieces[1]->set_colour(false);
	m_pieces[1]->set_type(p_type::KING);
	m_pieces[1]->set_pos({ 375,875 });
	m_pieces[1]->set_image_for_sprite();

	m_pieces[2]->set_colour(true);
	m_pieces[2]->set_type(p_type::QUEEN);
	m_pieces[2]->set_pos({ 500,0 });
	m_pieces[2]->set_image_for_sprite();

	m_pieces[3]->set_colour(false);
	m_pieces[3]->set_type(p_type::QUEEN);
	m_pieces[3]->set_pos({ 500,875 });
	m_pieces[3]->set_image_for_sprite();


	m_pieces[4]->set_colour(true);
	m_pieces[4]->set_type(p_type::BISHOP);
	m_pieces[4]->set_pos({ 250,0 });
	m_pieces[4]->set_image_for_sprite();

	m_pieces[5]->set_colour(true);
	m_pieces[5]->set_type(p_type::BISHOP);
	m_pieces[5]->set_pos({ 625,0 });
	m_pieces[5]->set_image_for_sprite();

	m_pieces[6]->set_colour(false);
	m_pieces[6]->set_type(p_type::BISHOP);
	m_pieces[6]->set_pos({ 250,875 });
	m_pieces[6]->set_image_for_sprite();

	m_pieces[7]->set_colour(false);
	m_pieces[7]->set_type(p_type::BISHOP);
	m_pieces[7]->set_pos({ 625,875 });
	m_pieces[7]->set_image_for_sprite();


	m_pieces[8]->set_colour(true);
	m_pieces[8]->set_type(p_type::KNIGHT);
	m_pieces[8]->set_pos({ 125,0 });
	m_pieces[8]->set_image_for_sprite();

	m_pieces[9]->set_colour(true);
	m_pieces[9]->set_type(p_type::KNIGHT);
	m_pieces[9]->set_pos({ 750,0 });
	m_pieces[9]->set_image_for_sprite();

	m_pieces[10]->set_colour(false);
	m_pieces[10]->set_type(p_type::KNIGHT);
	m_pieces[10]->set_pos({ 125,875 });
	m_pieces[10]->set_image_for_sprite();

	m_pieces[11]->set_colour(false);
	m_pieces[11]->set_type(p_type::KNIGHT);
	m_pieces[11]->set_pos({ 750,875 });
	m_pieces[11]->set_image_for_sprite();


	m_pieces[12]->set_colour(true);
	m_pieces[12]->set_type(p_type::ROOK);
	m_pieces[12]->set_pos({ 0,0 });
	m_pieces[12]->set_image_for_sprite();

	m_pieces[13]->set_colour(true);
	m_pieces[13]->set_type(p_type::ROOK);
	m_pieces[13]->set_pos({ 875,0 });
	m_pieces[13]->set_image_for_sprite();

	m_pieces[14]->set_colour(false);
	m_pieces[14]->set_type(p_type::ROOK);
	m_pieces[14]->set_pos({ 0,875 });
	m_pieces[14]->set_image_for_sprite();

	m_pieces[15]->set_colour(false);
	m_pieces[15]->set_type(p_type::ROOK);
	m_pieces[15]->set_pos({ (875),875 });
	m_pieces[15]->set_image_for_sprite();

	for (int j = 0; j < 2; ++j) {
		for (int i = 0; i < 8; ++i) {
			m_pieces[16 + i + 8 * j]->set_colour(j);
			m_pieces[16 + i + 8 * j]->set_type(p_type::PAWN);
			m_pieces[16 + i + 8 * j]->set_pos({ (i * 125),(j == 1) ? 125 : 750 });
			m_pieces[16 + i + 8 * j]->set_image_for_sprite();
		}
	}	
	m_board_texture.loadFromFile("assets/board.png");
	m_board_sprite.setTexture(m_board_texture);

	m_selected_square.setSize({ 120.0f,120.0f });
	m_selected_square.setOutlineColor(sf::Color::Cyan);
	m_selected_square.setFillColor(sf::Color::Transparent);
	m_selected_square.setOutlineThickness(3);
	m_selected_square.setPosition({125.0f,125.0f});
}
board::~board()
{
	for(auto i : m_pieces)
	{
		delete i;
	}
	m_pieces.clear();
}
void board::set_p_position(const sf::Vector2<float>& pos, piece* p_piece)
{
	auto find_result = std::find(m_pieces.cbegin(), m_pieces.cend(), p_piece);
	if (find_result == m_pieces.cend())
		return;
	//*find_result
}

sf::Sprite board::get_p_sprite(const int& index)
{
	return m_pieces[index]->get_sprite();
}
sf::Sprite board::get_board_texture()
{
	return m_board_sprite;
}
void board::delete_piece(const int& index)
{
	delete m_pieces[index];
	m_pieces.erase(m_pieces.begin() + index);
}
sf::RectangleShape board::get_selected_square() const
{
	return m_selected_square;
}
void board::update_selected_square(const sf::Vector2<int>& mouse_pos)
{
	sf::Vector2<float> ss_pos = m_selected_square.getPosition();
	sf::Vector2f adj_m_pos(mouse_pos);
	if(adj_m_pos.x > ss_pos.x && adj_m_pos.x < (ss_pos.x + 125.0f) && adj_m_pos.y > ss_pos.y && adj_m_pos.y < ss_pos.y +125.0f 
		&& m_square_is_seleted)
		//if user clicked on the square and the square is selected
	{
		m_square_is_seleted = false;
	}
	else
	{
		adj_m_pos.x = adj_m_pos.x - abs(static_cast<int>(adj_m_pos.x) % 125) + 2;
		adj_m_pos.y = adj_m_pos.y - abs(static_cast<int>(adj_m_pos.y) % 125) + 2;
		m_square_is_seleted = true;
		m_selected_square.setPosition(adj_m_pos);
	}
}
bool board::get_square_state() const
{
	return m_square_is_seleted;
}
void board::set_square_state(const bool& state)
{
	m_square_is_seleted = state;
}
void board::flip_board() const 
{
	for(const auto& i : m_pieces)
	{
		const auto p_pos = i->get_pos();
		sf::Vector2f new_position = {abs(p_pos.x- 875.0f),abs(p_pos.y - 875.0f)};//mirrors pos in x and y axis
		sf::Vector2i converted(new_position);
		i->set_pos(converted);
	}
}
piece* board::find_piece_selected()const
{	
	for(const auto& i : m_pieces)
	{
		if (i->get_pos().x >= m_selected_square.getPosition().x - 10.0f  &&
		    i->get_pos().x <= m_selected_square.getPosition().x          &&
		    i->get_pos().y >= m_selected_square.getPosition().y - 10.0f  &&
		    i->get_pos().y <= m_selected_square.getPosition().y)
			return i;
	}
	return nullptr;
}
piece* board::find_piece_at_position(const sf::Vector2f& pos) const
{
	for (const auto& i : m_pieces)
	{
		if (i->get_pos() == pos)
			return i;
	}
	return nullptr;
}
