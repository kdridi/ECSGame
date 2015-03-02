//
//  tilemap.cpp
//  arykow
//
//  Created by Karim DRIDI on 01/03/2015.
//
//

#include "tilemap.h"

#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    
    bool loadTextureFromFile(const std::string& textureFilename, const sf::Vector2u& tileSize) {
        m_texture_size = tileSize;
        return m_texture.loadFromFile(textureFilename);
    }
    
    bool load(const std::string& tsFilename, sf::Vector2u tsSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // on charge la texture du tileset67uikl.
        if (!loadTextureFromFile(tsFilename, tsSize))
            return false;
        
        // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);
        
        // on remplit le tableau de vertex, avec un quad par tuile
        for (unsigned int ti = 0; ti < width; ++ti)
            for (unsigned int tj = 0; tj < height; ++tj)
            {
                unsigned int index = ti + tj * width;
                
                // on récupère le numéro de tuile courant
                // on en déduit sa position dans la texture du tileset
                
                int tn = tiles[index];
                int tu = tn % (m_texture.getSize().x / m_texture_size.x);
                int tv = tn / (m_texture.getSize().x / m_texture_size.x);
                
                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &m_vertices[4 * index];
                
                quad[0].position  = sf::Vector2f((ti + 0) * m_texture_size.x, (tj + 0) * m_texture_size.y);
                quad[0].texCoords = sf::Vector2f((tu + 0) * m_texture_size.x, (tv + 0) * m_texture_size.y);
                
                quad[1].position  = sf::Vector2f((ti + 1) * m_texture_size.x, (tj + 0) * m_texture_size.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * m_texture_size.x, (tv + 0) * m_texture_size.y);
                
                quad[2].position  = sf::Vector2f((ti + 1) * m_texture_size.x, (tj + 1) * m_texture_size.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * m_texture_size.x, (tv + 1) * m_texture_size.y);
                
                quad[3].position  = sf::Vector2f((ti + 0) * m_texture_size.x, (tj + 1) * m_texture_size.y);
                quad[3].texCoords = sf::Vector2f((tu + 0) * m_texture_size.x, (tv + 1) * m_texture_size.y);
            }
        
        return true;
    }
    
private:
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation
        states.transform *= getTransform();
        
        // on applique la texture du tileset
        states.texture = &m_texture;
        
        // et on dessine enfin le tableau de vertex
        target.draw(m_vertices, states);
    }
    
    sf::VertexArray m_vertices;
    sf::Texture m_texture;
    sf::Vector2u m_texture_size;
};

int tilemap_main() {
    // on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap");
    
    // on définit le niveau à l'aide de numéro de tuiles
    const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };
    
    // on crée la tilemap avec le niveau précédemment défini
    TileMap map;
    if (!map.load(DATA_PATH "tileset.png", sf::Vector2u(32, 32), level, 16, 8))
    {
        return -1;
    }
    
    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }
                case sf::Event::KeyPressed:
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape:
                        {
                            window.close();
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        
        // on dessine le niveau
        window.clear();
        window.draw(map);
        window.display();
    }
    
    return 0;
}