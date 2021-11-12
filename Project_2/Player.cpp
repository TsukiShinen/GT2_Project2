#include "Player.h"

//
//Player::Player(std::pair<int, int> size) {
//    _sprite._size = size;
//    _sprite._rect.setFillColor(sf::Color::White);
//    _sprite._rect.setPosition(_position);
//}

Player::Player(const sf::Texture* texture) :
    Entity("Player", 100, texture) 
{  
    setAnimation();
    m_size = sf::Vector2f(8, 8);
    m_sprite.setOrigin(sf::Vector2f(12, 12));
}

void Player::setAnimation() {
    m_animationController.addAnimation("WalkBR", 336, 4, 0.13f);
    m_animationController.addAnimation("WalkBL", 352, 4, 0.13f);
    m_animationController.addAnimation("WalkTR", 368, 4, 0.13f);
    m_animationController.addAnimation("WalkTL", 384, 4, 0.13f);
    std::vector <sf::IntRect> allIdle = m_animationController.getAllRect(176, 16);
    std::map<std::string, std::pair<size_t, size_t>> IdleMap{
        {"IdleBR", {176, 16}},
        {"IdleBL", {192,8}},
        {"IdleTR", {208,16}},
        {"IdleTL", {224,16}}
    };

    for (const auto& Idle : IdleMap) {
        m_animationController.addAnimation(Idle.first, Idle.second.first, Idle.second.second, 0.31111f);
    }

    m_animationController.changeCurrentAnim("IdleBL");
}

void Player::draw(sf::RenderWindow& window, bool debugMode) {
    if (debugMode) {
        m_movebox.setFillColor(sf::Color::Green);
        window.draw(m_movebox);
    }
    Entity::draw(window, debugMode);
}

void Player::changeSprite() {
    if (m_direction.x < 0) 
    {
        m_directionAnim = m_directionAnim.replace(5, 1, "L");
    }
    else if (0 < m_direction.x)
    {
        m_directionAnim = m_directionAnim.replace(5, 1, "R");
    }
    if (m_direction.y < 0)
    {
        m_directionAnim = m_directionAnim.replace(4, 1, "T");
    }
    else if (m_direction.y > 0)
    {
        m_directionAnim = m_directionAnim.replace(4, 1, "B");
    }


    if (m_direction.x == 0.f && m_direction.y == 0.f) {
        std::string test = "Idle";
        test.append(m_directionAnim.substr(4, 6));
        if (m_animationController.getCurrentAnim() != test) {
            m_animationController.changeCurrentAnim(test);
        }       
    }
    else {
        if (m_animationController.getCurrentAnim() != m_directionAnim) {
            m_animationController.changeCurrentAnim(m_directionAnim);
        }
    }
    
}

void Player::update(sf::Time clock, std::vector<sf::FloatRect>& listOfElements) {
    
    m_direction = { 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        // move(0, -_speed*clock.asSeconds());
        m_direction.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        // move(_speed * clock.asSeconds(), 0);
        m_direction.x = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        // move(0, _speed*clock.asSeconds());
        m_direction.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        // move(-_speed*clock.asSeconds(), 0);
        m_direction.x = -1;
        
    }
    


    sf::FloatRect playerPos = getBoundingBox();
    sf::FloatRect futurePos = playerPos;


    futurePos.left += 13;
    futurePos.top += 17;
    futurePos.width = 6;
    futurePos.height = 3;

    
    sf::Vector2f initial(m_direction.x, m_direction.y);
  

    for (const sf::FloatRect& bound : listOfElements) {
        /*sf::FloatRect bound = thing.getGlobalBounds();*/
        
        if (m_direction.x != 0.f) {
            futurePos.left += m_direction.x;
            if (futurePos.intersects(bound)) {
                
                m_direction.x = 0.f;
                // reset x
            }
            futurePos.left -= initial.x;
        }
        
        if (m_direction.y != 0.f) {
            futurePos.top += m_direction.y;
            if (futurePos.intersects(bound)) {
                
                m_direction.y = 0.f;
                // reset y
            }
            futurePos.top -= initial.y;
        }

        if (m_direction.x != 0.f && m_direction.y != 0.f) {
            futurePos.left += m_direction.x;
            futurePos.top += m_direction.y;
            if (futurePos.intersects(bound)) {
                m_direction.x = 0.f;
                m_direction.y = 0.f;
                // reset both 
            }
            futurePos.left -= initial.x;
            futurePos.top -= initial.y;
        }
       

    }
    
    changeSprite();

    // adding after verification
    futurePos.left += m_direction.x;
    futurePos.top += m_direction.y;

    m_movebox.setSize(sf::Vector2f(futurePos.width, futurePos.height));
    m_movebox.setPosition(futurePos.left, futurePos.top);
    m_sprite.move(m_direction);
}

sf::FloatRect Player::getBoundingBox() {
        return sf::FloatRect(getPosition().x, getPosition().y, m_size.x, m_size.y);
}

