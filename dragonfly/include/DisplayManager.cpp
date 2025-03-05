// System includes.
#include <SFML/Graphics.hpp>
#include "stdio.h"
// Engine includes.
#include "DisplayManager.h"
#include "Color.h"
#include "Manager.h"
#include "Vector.h"
#include <iostream>
#include "utility.h"
float a = 1;

void DisplayManager::setA(float b) {
    a = b;
}
float charHeight() {
    return a*DM.getVerticalPixels() / static_cast<float>(DM.getVertical());
}


// Compute character width in pixels, based on window size.
float charWidth() {
    return a*DM.getHorizontalPixels() / static_cast<float>(DM.getHorizontal());
};

// Convert ASCII spaces (x, y) to window pixels (x, y).
df::Vector spacesToPixels(df::Vector spaces) {
    float pixelX = spaces.getX() * charWidth();
    float pixelY = spaces.getY() * charHeight();
    return df::Vector(pixelX, pixelY);
};

// Convert window pixels (x, y) to ASCII spaces (x, y).
df::Vector pixelsToSpaces(df::Vector pixels) {
    float spaceX = pixels.getX() / charWidth();
    float spaceY = pixels.getY() / charHeight();
    return df::Vector(spaceX, spaceY);
};

// Get the one and only instance of the DisplayManager.
DisplayManager& DisplayManager::getInstance() {
    static DisplayManager instance;
    return instance;
}

// Private constructor (singleton).
DisplayManager::DisplayManager() {
    m_p_window = NULL;
    // Constructor stub.
}

// Don't allow copy.
DisplayManager::DisplayManager(DisplayManager const&) {
    // Copy constructor stub.
}

// Don't allow assignment.
void DisplayManager::operator=(DisplayManager const&) {
    // Assignment operator stub.
}

// Open graphics window, ready for text-based display.
// Return 0 if ok, else -1.
int DisplayManager::startUp() {
    if (m_p_window != NULL) {
        return 0;
    }
    m_p_window = new sf::RenderWindow(sf::VideoMode({ 700,768*2}), "SFML - Hello, World!");
    //fullscreen
    if (!m_p_window) {
        std::cout << "Error! Unable to allocate renderwindow" << std::endl;
        return -1;
    }
    m_p_window->setMouseCursorVisible(false);
    m_p_window->setVerticalSyncEnabled(true);
    
    //PAY ATTENTION TO THIS LOCAL FONT
    if (m_font.openFromFile("df-font.ttf") == false) {
        std::cout << "Error! Unable to load font 'df-font.ttf'." << std::endl;
        return -1;
    }


    Manager::startUp();
    return 0;
}

// Close graphics window.
void DisplayManager::shutDown() {
    if (m_p_window) {
        m_p_window->close();
    }
    //MIGHT BE WRONG
    //MIGHT BE WRONG
    //MIGHT BE WRONG//MIGHT BE WRONG//MIGHT BE WRONG
    //delete m_p_window;
    m_p_window = NULL;
   
    Manager::shutDown();
}

int DisplayManager::drawCh(df::Vector world_pos, char ch, df::Color color) const {
    // Make sure window is allocated.
    if (m_p_window == NULL) {
        return -1;
    }

    // Convert world coordinates to view coordinates.
    df::Vector view_pos = worldToView(world_pos);

    // Convert view coordinates (game spaces) to pixel coordinates.

    // Draw background rectangle since text is "see-through" in SFML.
    static sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
    rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
    rectangle.setPosition({ spacesToPixels(view_pos).getX() - charWidth() / 10,
                            spacesToPixels(view_pos).getY() + charHeight() / 5 });
    m_p_window->draw(rectangle);

    // Create character text to draw.
    static sf::Text text(m_font);
    text.setString(ch);
    text.setStyle(sf::Text::Bold); // Make bold, since it looks better.

    // Scale to right size.
    //SCALE TEXT
    if (charWidth() < charHeight()) {
        text.setCharacterSize(charWidth() * 2);
    }
    else {
        text.setCharacterSize(charHeight() * 2);
    }

    // Set SFML color based on Dragonfly color.
    switch (color) {
    case df::YELLOW:
        text.setFillColor(sf::Color::Yellow);
        break;
    case df::RED:
        text.setFillColor(sf::Color::Red);
        break;
    case df::GREEN:
        text.setFillColor(sf::Color::Green);
        break;
    case df::BLUE:
        text.setFillColor(sf::Color::Blue);
        break;
    case df::MAGENTA:
        text.setFillColor(sf::Color::Magenta);
        break;
    case df::CYAN:
        text.setFillColor(sf::Color::Cyan);
        break;
    case df::WHITE:
        text.setFillColor(sf::Color::White);
        break;
    case df::BLACK:
        text.setFillColor(sf::Color::Black);
        break;
    default:
        text.setFillColor(sf::Color::White); // Default to white if color is undefined
        break;
    }

    // Set position in window (in pixels) using view position.
    text.setPosition({ spacesToPixels(view_pos).getX(), spacesToPixels(view_pos).getY() });

    // Draw character.
    m_p_window->draw(text);

    return 0; // Success.
}


// Return window’s horizontal maximum (in characters).
int DisplayManager::getHorizontal() const {
    return WINDOW_HORIZONTAL_CHARS_DEFAULT;

}

// Return window’s vertical maximum (in characters).
int DisplayManager::getVertical() const {
    return WINDOW_VERTICAL_CHARS_DEFAULT;

}

// Return window’s horizontal maximum (in pixels).
int DisplayManager::getHorizontalPixels() const {
    return 2048;
}

// Return window’s vertical maximum (in pixels).
int DisplayManager::getVerticalPixels() const {
    return 768*2;
}

// Render current window buffer.
// Return 0 if ok, else -1.
int DisplayManager::swapBuffers() {
    if (m_p_window == NULL) {
        return -1;
    }
    m_p_window->display();

    m_p_window->clear();
    return 0;
}

// Return pointer to SFML graphics window.
sf::RenderWindow* DisplayManager::getWindow() const {
    return m_p_window;
}


// Draw string at window location (x, y) with color.
// Justified left, center, or right.
// Return 0 if ok, else -1.

int DisplayManager::drawString(df::Vector pos, std::string str, Justification just, df::Color color) const {
    // Get starting position.
    df::Vector starting_pos = pos;
    
    switch (just) {
    case CENTER_JUSTIFIED:
        starting_pos.setX(pos.getX() - str.size() / 2);
        break;
    case RIGHT_JUSTIFIED:
        starting_pos.setX(pos.getX() - str.size());
        break;
    case LEFT_JUSTIFIED:
    default:
        break;
    }

    // Draw string character by character.
    for (size_t i = 0; i < str.size(); i++) {
        df::Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
        drawCh(temp_pos, str[i], color);
    }

    // All is well.
    return 0;
}

