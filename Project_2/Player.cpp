#include "Player.h"


Player::Player(const sf::Texture* texture, const sf::Texture* inventoryTexture, const sf::Texture* itemSelectedTexture) :
    Entity("Player", 5.f, texture),
    m_inventaire(10, inventoryTexture, itemSelectedTexture),
    m_sword(texture)
{
    // m_useAcceleration = false;
    m_speed = 200.f;

    setAnimation();
    m_size = sf::Vector2f(8, 8);
    m_sprite.setOrigin(sf::Vector2f(12, 12));

    heal = [&](int value) {
        m_life += value;
        m_lifeBar.setValue(m_life);
    };
}

void Player::setAnimation() {
    m_animationController.addAnimation("Walk_DR", 336, 4, 0.13f);
    m_animationController.addAnimation("Walk_DL", 352, 4, 0.13f);
    m_animationController.addAnimation("Walk_UR", 368, 4, 0.13f);
    m_animationController.addAnimation("Walk_UL", 384, 4, 0.13f);
    std::vector <sf::IntRect> allIdle = m_animationController.getAllRect(176, 16);
    std::map<std::string, std::pair<size_t, size_t>> IdleMap{
        {"Idle_DR", {176, 16}},
        {"Idle_DL", {192,8}},
        {"Idle_UR", {208,16}},
        {"Idle_UL", {224,16}}
    };

    for (const auto& Idle : IdleMap) {
        m_animationController.addAnimation(Idle.first, Idle.second.first, Idle.second.second, 0.31111f);
    }

    m_animationController.changeCurrentAnim("Idle_DL");
}

void Player::draw(sf::RenderWindow& window, bool debugMode) {
   /* std::cout << m_life << std::endl;*/
    if (debugMode) {
        m_movebox.setFillColor(sf::Color::Green);
        window.draw(m_movebox);
    }
    
    if (m_direction.down) {
        Entity::draw(window, debugMode);
        m_sword.draw(window, debugMode);
    }
    else {
        m_sword.draw(window, debugMode);
        Entity::draw(window, debugMode);
    }
    
}

void Player::drawUI(sf::RenderWindow& window, bool debugMode)
{
    window.draw(m_lifeBar);
    if (m_isInventoryOpen) {
        m_inventaire.draw(window, debugMode);
    }
   
}

void Player::changeSprite() {

    std::string base = "";
    if (m_velocity.x != 0 || m_velocity.y != 0)
        base = "Walk";
    else
        base = "Idle";

    std::string dir = "";
    if (m_direction.up)
        dir += "U";
    else if (m_direction.down)
        dir += "D";
    if (m_direction.right)
        dir += "R";
    else if (m_direction.left)
        dir += "L";

    std::string name = base + "_" + dir;
    m_animationController.changeCurrentAnim(name);
}

void Player::update(sf::Time deltaTime, std::vector<sf::FloatRect>& listOfElements) {
    if (!m_isInventoryOpen) 
    {
        sf::Vector2f movement{ 0.f, 0.f };
    
        if (m_attack) {
            
            m_attack = m_sword.isHitting();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

            movement.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            
            movement.x -= 1;
        
        }

        addForce(Utils::normalize(movement) * m_speed);

        // direction changes
        if (m_velocity.y < 0)
        {
            m_moveHistory.y = -1;
            m_direction.up = true;
            m_direction.down = false;
        }
           
        if (m_velocity.x > 0)
        {
            m_moveHistory.x = 1;
            m_direction.right = true;
            m_direction.left = false;
        }
            
        if (m_velocity.y > 0)
        {
            m_moveHistory.y = 1;
            m_direction.down = true;
            m_direction.up = false;
        }
            
        if (m_velocity.x < 0)
        {
            m_moveHistory.x = -1;
            m_direction.left = true;
            m_direction.right = false;
        }
            

        sf::FloatRect futurePos = intersects(listOfElements);

        // adding after verification
        futurePos.left += movement.x;
        futurePos.top += movement.y;

        // update de la movebox
        m_movebox.setSize(sf::Vector2f(futurePos.width, futurePos.height));
        m_movebox.setPosition(futurePos.left, futurePos.top);
        changeSprite();
    }

    Entity::update(deltaTime);
    m_sword.update(deltaTime, getCenter(), m_attack, calcDirectionAngle());
}

sf::FloatRect Player::getBoundingBox() {
        return sf::FloatRect(getPosition().x, getPosition().y, m_size.x, m_size.y);
}

void Player::takeDamage(float damage)
{
    Entity::takeDamage(damage);
    m_lifeBar.setValue(m_life);
}



sf::FloatRect Player::intersects(std::vector<sf::FloatRect>& listOfElements) {
    sf::Vector2f initial(m_velocity.x, m_velocity.y);
    
    sf::FloatRect playerPos = getBoundingBox();
    sf::FloatRect futurePos = playerPos;

    futurePos.left += m_walkingBox.left;
    futurePos.top += m_walkingBox.top;
    futurePos.width = m_walkingBox.width;
    futurePos.height = m_walkingBox.height;
    
    for (const sf::FloatRect& bound : listOfElements) {

        if (m_velocity.x != 0.f) {
            futurePos.left += m_velocity.x;
            if (futurePos.intersects(bound)) {

                m_velocity.x = 0.f;
                // reset x
            }
            futurePos.left -= initial.x;
        }

        if (m_velocity.y != 0.f) {
            futurePos.top += m_velocity.y;
            if (futurePos.intersects(bound)) {

                m_velocity.y = 0.f;
                // reset y
            }
            futurePos.top -= initial.y;
        }

        if (m_velocity.x != 0.f && m_velocity.y != 0.f) {
            futurePos.left += m_velocity.x;

            if (futurePos.intersects(bound)) {
                m_velocity.x = 0.f;
                // reset only x : arbitrary choise
            }
            futurePos.left -= initial.x;
        }
    }
    return futurePos;
}

void Player::attack() { 
    if (!m_attack && !m_sword.isHitting()) { 
        m_attack = true;
        m_sword.attack(Utils::angle(m_sprite.getPosition(), m_sprite.getPosition() + m_velocity) * (180.0 / 3.141592653589793238463));
    }
};

bool Player::isAttacking(sf::Vector2f Enemy) {
    if (!m_attack) { return false; }
    double distance = Utils::dist(m_sprite.getPosition(), Enemy);
    int angleE = static_cast<int>(Utils::angle(Enemy, m_sprite.getPosition()) * (180.0 / 3.141592653589793238463));
    int angleP = static_cast<int>(calcDirectionAngle());
    angleP = Utils::modAngle(angleP);
    angleE = Utils::modAngle(angleE);
    
    int diffAngle = Utils::shortestAngle(angleP, angleE);

    if (distance < m_sword.getRange() && diffAngle<m_sword.getAttackAngle()) {
        return true;
    }
    return false;

};

bool Player::pickItem(Item* item)
{
    return m_inventaire.addItem(item);
}

void Player::keypressed(sf::Keyboard::Key keyCode)
{
    if (keyCode == sf::Keyboard::E) {
        m_isInventoryOpen = !m_isInventoryOpen;
        m_velocity.x = 0;
        m_velocity.y = 0;
        m_animationController.changeCurrentAnim("Idle_DR");
    }
    if (m_isInventoryOpen) {
        m_inventaire.keypressed(keyCode);
    }
    if (keyCode == sf::Keyboard::Space) {
        attack();
    }
}

double Player::calcDirectionAngle() {
    return Utils::angle(getPosition() + m_moveHistory, getPosition())* (180.0 / 3.141592653589793238463);
}

void Player::setProgressBar(ProgressBar& progressBar)
{
    m_lifeBar = progressBar;
    m_lifeBar.setNumberOfSprite(5);
    m_lifeBar.setValue(m_life);
}
