#pragma once
#include "board.hpp"
#include <array>
struct move
{
	sf::Vector2i start_pos = {0,0};
	sf::Vector2i target_pos = { 0,0 };
};

namespace p_moves
{
	constexpr int king_moves[8][2] = { {1,1},{1,0},{0,1},{-1,-1},{-1,1},{1,-1}, {0,-1}, {-1,0} };
	constexpr int rook_moves[32][2] = {
		{0,1},{0,2},{0,3},{0,4},{0,5},{0,6}, {0,7}, {0,8},
		{0,-1},{0,-2},{0,-3},{0,-4},{0,-5},{0,-6}, {0,-7}, {0,-8},
		{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},
		{-1,0},{-2,0},{-3,0},{-4,0},{-5,0},{-6,0},{-7,0},{-8,0}
	};
	constexpr int bishop_moves[32][2] = {
		{1,1},{2,2},{3,3},{4,4},{5,5},{6,6}, {7,7}, {8,8},
		{-1,-1},{-2,-2},{-3,-3},{-4,-4},{-5,-5},{-6,-6}, {-7,-7}, {-8,-8},
		{-1,1},{-2,2},{-3,3},{-4,4},{-5,5},{-6,6}, {-7,7}, {-8,8},
		{1,-1},{2,-2},{3,-3},{4,-4},{5,-5},{6,-6}, {7,-7}, {8,-8}
	};
	constexpr int queen_moves[64][2] = {
		{0,1},{0,2},{0,3},{0,4},{0,5},{0,6}, {0,7}, {0,8},
		{0,-1},{0,-2},{0,-3},{0,-4},{0,-5},{0,-6}, {0,-7}, {0,-8},
		{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},
		{-1,0},{-2,0},{-3,0},{-4,0},{-5,0},{-6,0},{-7,0},{-8,0},
		{1,1},{2,2},{3,3},{4,4},{5,5},{6,6}, {7,7}, {8,8},
		{-1,-1},{-2,-2},{-3,-3},{-4,-4},{-5,-5},{-6,-6}, {-7,-7}, {-8,-8},
		{-1,1},{-2,2},{-3,3},{-4,4},{-5,5},{-6,6}, {-7,7}, {-8,8},
		{1,-1},{2,-2},{3,-3},{4,-4},{5,-5},{6,-6}, {7,-7}, {8,-8}
	};
	constexpr int knight_moves[8][2] = {
		{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}
	};
	const sf::Vector2i max_bounds = { 8,8 };
	const sf::Vector2i min_bounds = { 1,1 };
}

class game
{	
public:
	static [[nodiscard]] sf::Vector2<int> pos_to_coordinates(const sf::Vector2f& pos);
	static [[nodiscard]] sf::Vector2f coordinates_to_pos(const sf::Vector2i& pos);
	static bool is_move_legal(const p_type& piece_type, const sf::Vector2i& current_pos, const sf::Vector2i target_pos);
	piece* get_last_selected_piece()const;
	void take_piece(piece* taking_piece, piece* piece_to_take, board& c_board);
	std::vector<move> generate_possible_moves(const piece* m_piece,const board& c_board )const;
	bool is_valid_move(piece* m_piece, const sf::Vector2i& position_to_move, board& c_board)const;
	void update_previously_selected_piece(board& c_board);
	void move_piece(board& c_board, sf::Vector2i mouse_pos);
private:
	bool m_is_white_true = true;
	piece* m_previously_selected_piece = nullptr;
};
