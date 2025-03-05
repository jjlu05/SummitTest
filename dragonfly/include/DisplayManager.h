// System includes.
#include <SFML/Graphics.hpp>

// Engine includes.
#include "Color.h"
#include "Manager.h"
#include "Vector.h"
#define DM DisplayManager::getInstance()
enum Justification {
    LEFT_JUSTIFIED,
    CENTER_JUSTIFIED,
    RIGHT_JUSTIFIED,
};
// Defaults for SFML window.
const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80*2*2;
const int WINDOW_VERTICAL_CHARS_DEFAULT = 24*2*2;//change the 80 24 values
const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
const std::string FONT_FILE_DEFAULT = "df-font.ttf";

// Compute character height in pixels, based on window size.
float charHeight();

// Compute character width in pixels, based on window size.
float charWidth();

// Convert ASCII spaces (x, y) to window pixels (x, y).
df::Vector spacesToPixels(df::Vector spaces);   

// Convert window pixels (x, y) to ASCII spaces (x, y).
df::Vector pixelsToSpaces(df::Vector pixels);

class DisplayManager : public df::Manager {

private:
    DisplayManager(); // Private (a singleton).
    DisplayManager(DisplayManager const&); // Don't allow copy.
    void operator=(DisplayManager const&); // Don't allow assignment.
    sf::Font m_font; // Font used for ASCII graphics.
    sf::RenderWindow* m_p_window; // Pointer to SFML window.
    int m_window_horizontal_pixels; // Horizontal pixels in window.
    int m_window_vertical_pixels; // Vertical pixels in window.
    int m_window_horizontal_chars; // Horizontal ASCII spaces in window.
    int m_window_vertical_chars; // Vertical ASCII spaces in window.

public:
    void setA(float b);

    // Get the one and only instance of the DisplayManager.
    static DisplayManager& getInstance();

    // Open graphics window, ready for text-based display.
    // Return 0 if ok, else -1.
    int startUp();

    // Close graphics window.
    void shutDown();

    // Draw character at window location (x, y) with color.
    // Return 0 if ok, else -1.
    int drawCh(df::Vector world_pos, char ch, df::Color color) const;

    // Return window’s horizontal maximum (in characters).
    int getHorizontal() const;

    // Return window’s vertical maximum (in characters).
    int getVertical() const;

    // Return window’s horizontal maximum (in pixels).
    int getHorizontalPixels() const;

    // Return window’s vertical maximum (in pixels).
    int getVerticalPixels() const;

    // Render current window buffer.
    // Return 0 if ok, else -1.
    int swapBuffers();

    // Return pointer to SFML graphics window.
    sf::RenderWindow* getWindow() const;

    int drawString(df::Vector pos, std::string str, Justification just, df::Color color) const;
};
