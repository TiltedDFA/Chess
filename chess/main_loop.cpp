#include "main_loop.hpp"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Chess Engine By Tilted");   
    board c_board;
    game _game;
    bool u_date_needed = true;
    
    while (window.isOpen())
    {        
        sf::Event event{};
        while (window.waitEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Space:
                    c_board.flip_board();
                    u_date_needed = true;                    
                    break;
                default:
                    break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    c_board.update_selected_square(sf::Mouse::getPosition(window));
                    _game.move_piece(c_board, sf::Mouse::getPosition(window));
                    _game.update_previously_selected_piece(c_board);                    
                    u_date_needed = true;
                    break;                   
                }
                break;
            default:
            	break;
            }
            if (u_date_needed)
            {
                _game.display_all_pieces(c_board, window);
                window.display();
                u_date_needed = false;
            }
        }
    }
}	

