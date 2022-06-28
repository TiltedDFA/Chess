#include "main_loop.hpp"
#include "display.hpp"
void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");   
    board c_board;
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.waitEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }        
        window.clear();
        window.draw(static_cast<sf::Sprite>(c_board.get_board_texture()));
        window.draw(c_board.get_p_sprite(0));
        window.display();
    }
}	

