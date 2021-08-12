#include "bot.h"
extern sf::RenderWindow window;


Bot::Bot (sf::Vector2i logicalPosition, int state, int direction, const std::vector<sf::Texture*>& texturePointers, Tile_matrix& tileMap):
    tileMap(tileMap),
    texturePointers(texturePointers),
    logicalPosition(logicalPosition),
    state(state),
    direction(direction),
    sprites(4, sf::RectangleShape(sf::Vector2f(Bot::unit, Bot::unit)))
    
{
    position = tileMap[logicalPosition.y][logicalPosition.x]->getPosition() + sf::Vector2f(0.f, 20.f);

    for (int i = 0; i < 4; ++i) {
        sprites[i].setOrigin(Bot::unit / 2.f, Bot::unit / 2.f);    
        sprites[i].setPosition(position);
        sprites[i].setTexture(texturePointers[i]);
    }
}


void Bot::pollActionQueue ()
{
    if (not actionQueue.empty()) {
        Action &currentAction = actionQueue.front();
        
        switch (currentAction.type) {
            case Action::move:
                move(); 
                if (--currentAction.argument == 0)
                    actionQueue.pop_front();
                break;

            case Action::turn:
                turn(); 
                if (--currentAction.argument == 0)
                    actionQueue.pop_front();
                break;

            case Action::write:
                write(currentAction.argument); 
                actionQueue.pop_front();
                break;

            default:
                setState(currentAction.argument); 
        }
    }
}


void Bot::draw ()
{
    window.draw(sprites[direction]);
}


void Bot::move ()
{
    isometricMove[direction](position, 1);
    
    for (auto& sprite : sprites) {
        sprite.setPosition(position);
    }
}


void Bot::turn ()
{
    direction = (direction + 1) % 4;
}


void Bot::write (int newData)
{
    // set data
    // set shape
}


void Bot::setState (int newState)
{
    state = newState;
    actionQueue.clear();
}