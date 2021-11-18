#include "Player.h"


Player::Player(const sf::Texture* texture, const sf::Texture* inventoryTexture, const sf::Texture* itemSelectedTexture) :
    Entity("Player", 10.f, texture),
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

    m_animationController.addAnimation("FrontIdleRiding_R", 416, 16, 0.13f);
    m_animationController.addAnimation("FrontIdleRiding_L", 432, 16, 0.13f);
    m_animationController.addAnimation("FrontRiding_R", 448, 4, 0.13f);
    m_animationController.addAnimation("FrontRiding_L", 464, 4, 0.13f);

    m_animationController.addAnimation("IdleRide", 480, 16, 0.13f);
    m_animationController.addAnimation("Ride", 496, 8, 0.13f);


    m_animationController.addAnimation("Die", 320, 12, 0.13f);
    timeAnimationDie = 12 * 0.13f;

    m_animationController.changeCurrentAnim("Idle_DL");
}

void Player::drawGestion(sf::RenderWindow& window, bool debugMode) {
    if (debugMode) {
        m_movebox.setFillColor(sf::Color::Green);
        window.draw(m_movebox);
    }
    if (m_direction.down) {
        draw(window, debugMode);
        if (isAlive() && !m_riding && m_rideDuration < m_rideTime)
            m_sword.draw(window, debugMode);
        
        
    }
    else {
        
        if (isAlive() && !m_riding && m_rideDuration < m_rideTime)
            m_sword.draw(window, debugMode);
        draw(window, debugMode);
    }
}

void Player::draw(sf::RenderWindow& window, bool debugMode)
{
    //sf::RenderStates states;
    //states.transform = m_transform;
    //// Draw entity
    //window.draw(m_sprite, states);
    window.draw(m_sprite);
    // Draw boundingBox
    if (debugMode) {
        sf::FloatRect boundingBox = getBoundingBox();
        sf::RectangleShape rectBoundingBox;
        rectBoundingBox.setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));
        rectBoundingBox.setSize(sf::Vector2f(boundingBox.width, boundingBox.height));
        rectBoundingBox.setFillColor(sf::Color(255, 0, 0, 50));
        window.draw(rectBoundingBox);
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
    {
        if (m_riding && m_rideDuration < m_rideTime) {
            base = "Ride";
        }
        else {
            base = "Walk";
        }
    }
    else {
        base = "Idle";
        if (m_riding && m_rideDuration < m_rideTime)
            base.append("Ride");
    }

    std::string dir = "";
    if(!m_riding || m_rideDuration > m_rideTime) 
    {
        if (m_direction.up)
            dir += "U";
        else if (m_direction.down)
            dir += "D";
        if (m_direction.right)
            dir += "R";
        else if (m_direction.left)
            dir += "L";
    }
    
    std::string name = "";
    if (!m_riding || m_rideDuration > m_rideTime)
       name = base + "_" + dir;
    else
       name = base;
    
    m_animationController.changeCurrentAnim(name);
}

void Player::update(sf::Time deltaTime, std::vector<sf::FloatRect>& listOfElements) {
    
    if (!m_isInventoryOpen && isAlive()) 
    {
        m_movement = { 0.f, 0.f };
        if (m_attack) {
            m_attack = m_sword.isHitting();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            m_movement.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            m_movement.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            m_movement.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            m_movement.x -= 1;
        }

        if (m_rideDuration < m_rideTime) 
        {
            if (m_riding) {
                double vecAngle = (m_movement.x == 0.f) ? 0 : (m_movement.x < 0) ? -m_rotationSpeed * deltaTime.asSeconds() : m_rotationSpeed * deltaTime.asSeconds();
                vecAngle = fmod(m_sprite.getRotation() + vecAngle, 360);
                m_sprite.setRotation(static_cast<float>(vecAngle));
                
                m_movement.x = static_cast<float>(cos(vecAngle * 3.141592653589793238463 / 180) * m_movement.y);
                m_movement.y = static_cast<float>(sin(vecAngle * 3.141592653589793238463 / 180) * m_movement.y);
               
                addForce(m_movement * m_speed);
            } else {
                addForce(Utils::normalize(m_movement) * m_speed);
            }
           

            directionChange();

            sf::FloatRect futurePos = intersects(listOfElements, deltaTime);

            // update de la movebox
            m_movebox.setSize(sf::Vector2f(futurePos.width, futurePos.height));
            m_movebox.setPosition(futurePos.left, futurePos.top);
        }
        changeSprite();
        
    }
    if (!isAlive()) {
        chronoAniamtionDie += deltaTime.asSeconds();
        if (chronoAniamtionDie >= timeAnimationDie) {
            m_toRemove = true;
        }
    }
   
    if (!m_toRemove) {
        Entity::update(deltaTime);
    }

    if (!m_isInventoryOpen && isAlive())
    {
        m_sword.update(deltaTime, getCenter(), m_attack, static_cast<float>(calcDirectionAngle()));
    }
        
    m_rideTime += deltaTime.asSeconds();
}

sf::FloatRect Player::getBoundingBox() {
    if(!m_riding)
        return sf::FloatRect(getPosition().x, getPosition().y, m_size.x, m_size.y);
    else {
        return sf::FloatRect(getPosition().x + m_horseHitBox.left, getPosition().y + m_horseHitBox.top, m_horseHitBox.width, m_horseHitBox.height);
    }
}

void Player::takeDamage(float damage)
{
    Entity::takeDamage(damage);
    m_lifeBar.setValue(m_life);
    if (m_life <= 0) {
        m_animationController.changeCurrentAnim("Die");
    }
}

void Player::directionChange() {
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
}

sf::FloatRect Player::intersects(std::vector<sf::FloatRect>& listOfElements, sf::Time& deltaTime) {

    sf::Vector2f futureVel = m_velocity;

    sf::Vector2f acc(m_thrust / m_masse - m_friction * futureVel);
    futureVel += acc;
    if (abs(futureVel.x) < m_friction) {
        futureVel.x = 0;
    }
    if (abs(futureVel.y) < m_friction) {
        futureVel.y = 0;
    }

    futureVel *= deltaTime.asSeconds();

    sf::FloatRect playerPos = getBoundingBox();
    sf::FloatRect futurePos = playerPos;
    if (!m_riding) {
        futurePos.left += m_walkingBox.left;
        futurePos.top += m_walkingBox.top;
        futurePos.width = m_walkingBox.width;
        futurePos.height = m_walkingBox.height;
    }
    
    
    for (const sf::FloatRect& bound : listOfElements) {

        if (futureVel.x != 0.f) {
            futurePos.left += futureVel.x;
            if (futurePos.intersects(bound)) {
                m_thrust.x = 0.f;
                m_velocity.x = 0.f;
                // reset x
            }
            futurePos.left -= futureVel.x;
        }

        if (futureVel.y != 0.f) {
            futurePos.top += futureVel.y;
            if (futurePos.intersects(bound)) {
                m_thrust.y = 0.f;
                m_velocity.y = 0.f;
                // reset y
            }
            futurePos.top -= futureVel.y;
        }
    }
    return futurePos;
}

void Player::attack() { 
    if (!m_attack && !m_sword.isHitting()) { 
        m_attack = true;
        m_sword.attack(Utils::angle(m_sprite.getPosition(), m_sprite.getPosition() + m_moveHistory) * (180.0 / 3.141592653589793238463));
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

void Player::movementShift() {
    m_riding = !m_riding;

    float tempSpeed = m_otherSpeed;
    float tempMass = m_otherMass;
    
    m_otherSpeed = m_speed;
    m_otherMass = m_masse;

    m_speed = tempSpeed;
    m_masse = tempMass;

    m_sprite.setRotation(0);

    m_rideTime = 0;
    m_thrust = { 0.f , 0.f };
    m_velocity = { 0.f , 0.f };
}


void Player::keypressed(sf::Keyboard::Key keyCode)
{
    if (isAlive()) {
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
        if (keyCode == sf::Keyboard::T) {
            movementShift();
        }
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


//void Player::update(sf::Time& deltaTime)
//{
//    // Move the sprite
//    if (m_useAcceleration) {
//       
//        sf::Vector2f acc(m_thrust / m_masse - m_friction * m_velocity);
//        
//        m_velocity = m_velocity + acc;
//        if (abs(m_velocity.x) < m_friction) {
//            m_velocity.x = 0;
//        }
//        if (abs(m_velocity.y) < m_friction) {
//            m_velocity.y = 0;
//        }
//    }
//
//    setPosition(getPosition() + m_velocity * deltaTime.asSeconds());
//    m_thrust = { 0.f, 0.f };
//
//    // Animate
//    m_animationController.update(deltaTime);
//    m_sprite.setTextureRect(m_animationController.getCurrentRect());
//}