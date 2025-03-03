#include "InputManager.h"
#include "DisplayManager.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
#include <SFML/Graphics.hpp >
#include "Object.h";
namespace df {
    // Private constructor (singleton)
    InputManager::InputManager() {

        setType("InputManager");
    }

    // Don't allow copy
    InputManager::InputManager(InputManager const&) {}

    // Don't allow assignment
    void InputManager::operator=(InputManager const&) {}

    // Get the one and only instance of the InputManager
    InputManager& InputManager::getInstance() {
        static InputManager instance;
        return instance;
    }

    // Get window ready to capture input
    // Return 0 if ok, else return -1
    int InputManager::startUp() {

        if (!DM.isStarted()) {
            return -1;
        }

        sf::RenderWindow* window = DM.getWindow();
            window->setKeyRepeatEnabled(false);

            Manager::startUp();
            return 0;
    }
    // Revert back to normal window mode
    void InputManager::shutDown() {
        sf::RenderWindow* window = DM.getWindow();
        window->setKeyRepeatEnabled(true);
        Manager::shutDown();
    }

    // Get input from the keyboard and mouse
    // Pass event along to all Objects
    void InputManager::getInput() {
        sf::RenderWindow* test_window = DM.getWindow();
        while (const std::optional<sf::Event> p_event = test_window->pollEvent()) {
            sf::Event e = p_event.value();
            if (p_event->is<sf::Event::KeyPressed>()) {
                EventKeyboard ek;
                sf::Event::KeyPressed* p_kb_event =
                    reinterpret_cast<sf::Event::KeyPressed*> (&e);
                // Get SFML keyboard code.
                sf::Keyboard::Key key;
                key = p_kb_event->code;
                Keyboard::Key realKey;
                switch (key) {
                case sf::Keyboard::Key::Space: realKey = Keyboard::Key::SPACE; break;
                case sf::Keyboard::Key::Enter: realKey = Keyboard::Key::RETURN; break;
                case sf::Keyboard::Key::Escape: realKey = Keyboard::Key::ESCAPE; break;
                case sf::Keyboard::Key::Tab: realKey = Keyboard::Key::TAB; break;
                case sf::Keyboard::Key::Left: realKey = Keyboard::Key::LEFTARROW; break;
                case sf::Keyboard::Key::Right: realKey = Keyboard::Key::RIGHTARROW; break;
                case sf::Keyboard::Key::Up: realKey = Keyboard::Key::UPARROW; break;
                case sf::Keyboard::Key::Down: realKey = Keyboard::Key::DOWNARROW; break;
                case sf::Keyboard::Key::Pause: realKey = Keyboard::Key::PAUSE; break;
                case sf::Keyboard::Key::Subtract: realKey = Keyboard::Key::MINUS; break;
                case sf::Keyboard::Key::Equal: realKey = Keyboard::Key::PLUS; break;
                case sf::Keyboard::Key::Grave:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) {
                        realKey = Keyboard::Key::TILDE;   
                    }
                    else {
                        realKey = Keyboard::Key::UNDEFINED_KEY;
                    }
                    break;
                case sf::Keyboard::Key::Period: realKey = Keyboard::Key::PERIOD; break;
                case sf::Keyboard::Key::Comma: realKey = Keyboard::Key::COMMA; break;
                case sf::Keyboard::Key::Slash: realKey = Keyboard::Key::SLASH; break;
                case sf::Keyboard::Key::LControl: realKey = Keyboard::Key::LEFTCONTROL; break;
                case sf::Keyboard::Key::RControl: realKey = Keyboard::Key::RIGHTCONTROL; break;
                case sf::Keyboard::Key::LShift: realKey = Keyboard::Key::LEFTSHIFT; break;
                case sf::Keyboard::Key::RShift: realKey = Keyboard::Key::RIGHTSHIFT; break;
                case sf::Keyboard::Key::F1: realKey = Keyboard::Key::F1; break;
                case sf::Keyboard::Key::F2: realKey = Keyboard::Key::F2; break;
                case sf::Keyboard::Key::F3: realKey = Keyboard::Key::F3; break;
                case sf::Keyboard::Key::F4: realKey = Keyboard::Key::F4; break;
                case sf::Keyboard::Key::F5: realKey = Keyboard::Key::F5; break;
                case sf::Keyboard::Key::F6: realKey = Keyboard::Key::F6; break;
                case sf::Keyboard::Key::F7: realKey = Keyboard::Key::F7; break;
                case sf::Keyboard::Key::F8: realKey = Keyboard::Key::F8; break;
                case sf::Keyboard::Key::F9: realKey = Keyboard::Key::F9; break;
                case sf::Keyboard::Key::F10: realKey = Keyboard::Key::F10; break;
                case sf::Keyboard::Key::F11: realKey = Keyboard::Key::F11; break;
                case sf::Keyboard::Key::F12: realKey = Keyboard::Key::F12; break;
                case sf::Keyboard::Key::A: realKey = Keyboard::Key::A; break;
                case sf::Keyboard::Key::B: realKey = Keyboard::Key::B; break;
                case sf::Keyboard::Key::C: realKey = Keyboard::Key::C; break;
                case sf::Keyboard::Key::D: realKey = Keyboard::Key::D; break;
                case sf::Keyboard::Key::E: realKey = Keyboard::Key::E; break;
                case sf::Keyboard::Key::F: realKey = Keyboard::Key::F; break;
                case sf::Keyboard::Key::G: realKey = Keyboard::Key::G; break;
                case sf::Keyboard::Key::H: realKey = Keyboard::Key::H; break;
                case sf::Keyboard::Key::I: realKey = Keyboard::Key::I; break;
                case sf::Keyboard::Key::J: realKey = Keyboard::Key::J; break;
                case sf::Keyboard::Key::K: realKey = Keyboard::Key::K; break;
                case sf::Keyboard::Key::L: realKey = Keyboard::Key::L; break;
                case sf::Keyboard::Key::M: realKey = Keyboard::Key::M; break;
                case sf::Keyboard::Key::N: realKey = Keyboard::Key::N; break;
                case sf::Keyboard::Key::O: realKey = Keyboard::Key::O; break;
                case sf::Keyboard::Key::P: realKey = Keyboard::Key::P; break;
                case sf::Keyboard::Key::Q: realKey = Keyboard::Key::Q; break;
                case sf::Keyboard::Key::R: realKey = Keyboard::Key::R; break;
                case sf::Keyboard::Key::S: realKey = Keyboard::Key::S; break;
                case sf::Keyboard::Key::T: realKey = Keyboard::Key::T; break;
                case sf::Keyboard::Key::U: realKey = Keyboard::Key::U; break;
                case sf::Keyboard::Key::V: realKey = Keyboard::Key::V; break;
                case sf::Keyboard::Key::W: realKey = Keyboard::Key::W; break;
                case sf::Keyboard::Key::X: realKey = Keyboard::Key::X; break;
                case sf::Keyboard::Key::Y: realKey = Keyboard::Key::Y; break;
                case sf::Keyboard::Key::Z: realKey = Keyboard::Key::Z; break;
                case sf::Keyboard::Key::Num1: realKey = Keyboard::Key::NUM1; break;
                case sf::Keyboard::Key::Num2: realKey = Keyboard::Key::NUM2; break;
                case sf::Keyboard::Key::Num3: realKey = Keyboard::Key::NUM3; break;
                case sf::Keyboard::Key::Num4: realKey = Keyboard::Key::NUM4; break;
                case sf::Keyboard::Key::Num5: realKey = Keyboard::Key::NUM5; break;
                case sf::Keyboard::Key::Num6: realKey = Keyboard::Key::NUM6; break;
                case sf::Keyboard::Key::Num7: realKey = Keyboard::Key::NUM7; break;
                case sf::Keyboard::Key::Num8: realKey = Keyboard::Key::NUM8; break;
                case sf::Keyboard::Key::Num9: realKey = Keyboard::Key::NUM9; break;
                case sf::Keyboard::Key::Num0: realKey = Keyboard::Key::NUM0; break;
                default: realKey = Keyboard::Key::UNDEFINED_KEY; break;
                }
                ek.setKey(realKey);
                ek.setKeyboardAction(KEY_PRESSED);
                onEvent(&ek);

                //ek.setKey(p_event->getIf<sf::Event::KeyPressed>()->code);
            }
            else if (p_event->is<sf::Event::KeyReleased>()) {
                EventKeyboard ek;
                sf::Event::KeyReleased* p_kb_event =
                    reinterpret_cast<sf::Event::KeyReleased*> (&e);
                // Get SFML keyboard code.
                sf::Keyboard::Key key;
                key = p_kb_event->code;
                Keyboard::Key realKey;
                switch (key) {
                case sf::Keyboard::Key::Space: realKey = Keyboard::Key::SPACE; break;
                case sf::Keyboard::Key::Enter: realKey = Keyboard::Key::RETURN; break;
                case sf::Keyboard::Key::Escape: realKey = Keyboard::Key::ESCAPE; break;
                case sf::Keyboard::Key::Tab: realKey = Keyboard::Key::TAB; break;
                case sf::Keyboard::Key::Left: realKey = Keyboard::Key::LEFTARROW; break;
                case sf::Keyboard::Key::Right: realKey = Keyboard::Key::RIGHTARROW; break;
                case sf::Keyboard::Key::Up: realKey = Keyboard::Key::UPARROW; break;
                case sf::Keyboard::Key::Down: realKey = Keyboard::Key::DOWNARROW; break;
                case sf::Keyboard::Key::Pause: realKey = Keyboard::Key::PAUSE; break;
                case sf::Keyboard::Key::Subtract: realKey = Keyboard::Key::MINUS; break;
                case sf::Keyboard::Key::Equal: realKey = Keyboard::Key::PLUS; break;
                case sf::Keyboard::Key::Grave:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) {
                        realKey = Keyboard::Key::TILDE;
                    }
                    break;
                case sf::Keyboard::Key::Period: realKey = Keyboard::Key::PERIOD; break;
                case sf::Keyboard::Key::Comma: realKey = Keyboard::Key::COMMA; break;
                case sf::Keyboard::Key::Slash: realKey = Keyboard::Key::SLASH; break;
                case sf::Keyboard::Key::LControl: realKey = Keyboard::Key::LEFTCONTROL; break;
                case sf::Keyboard::Key::RControl: realKey = Keyboard::Key::RIGHTCONTROL; break;
                case sf::Keyboard::Key::LShift: realKey = Keyboard::Key::LEFTSHIFT; break;
                case sf::Keyboard::Key::RShift: realKey = Keyboard::Key::RIGHTSHIFT; break;
                case sf::Keyboard::Key::F1: realKey = Keyboard::Key::F1; break;
                case sf::Keyboard::Key::F2: realKey = Keyboard::Key::F2; break;
                case sf::Keyboard::Key::F3: realKey = Keyboard::Key::F3; break;
                case sf::Keyboard::Key::F4: realKey = Keyboard::Key::F4; break;
                case sf::Keyboard::Key::F5: realKey = Keyboard::Key::F5; break;
                case sf::Keyboard::Key::F6: realKey = Keyboard::Key::F6; break;
                case sf::Keyboard::Key::F7: realKey = Keyboard::Key::F7; break;
                case sf::Keyboard::Key::F8: realKey = Keyboard::Key::F8; break;
                case sf::Keyboard::Key::F9: realKey = Keyboard::Key::F9; break;
                case sf::Keyboard::Key::F10: realKey = Keyboard::Key::F10; break;
                case sf::Keyboard::Key::F11: realKey = Keyboard::Key::F11; break;
                case sf::Keyboard::Key::F12: realKey = Keyboard::Key::F12; break;
                case sf::Keyboard::Key::A: realKey = Keyboard::Key::A; break;
                case sf::Keyboard::Key::B: realKey = Keyboard::Key::B; break;
                case sf::Keyboard::Key::C: realKey = Keyboard::Key::C; break;
                case sf::Keyboard::Key::D: realKey = Keyboard::Key::D; break;
                case sf::Keyboard::Key::E: realKey = Keyboard::Key::E; break;
                case sf::Keyboard::Key::F: realKey = Keyboard::Key::F; break;
                case sf::Keyboard::Key::G: realKey = Keyboard::Key::G; break;
                case sf::Keyboard::Key::H: realKey = Keyboard::Key::H; break;
                case sf::Keyboard::Key::I: realKey = Keyboard::Key::I; break;
                case sf::Keyboard::Key::J: realKey = Keyboard::Key::J; break;
                case sf::Keyboard::Key::K: realKey = Keyboard::Key::K; break;
                case sf::Keyboard::Key::L: realKey = Keyboard::Key::L; break;
                case sf::Keyboard::Key::M: realKey = Keyboard::Key::M; break;
                case sf::Keyboard::Key::N: realKey = Keyboard::Key::N; break;
                case sf::Keyboard::Key::O: realKey = Keyboard::Key::O; break;
                case sf::Keyboard::Key::P: realKey = Keyboard::Key::P; break;
                case sf::Keyboard::Key::Q: realKey = Keyboard::Key::Q; break;
                case sf::Keyboard::Key::R: realKey = Keyboard::Key::R; break;
                case sf::Keyboard::Key::S: realKey = Keyboard::Key::S; break;
                case sf::Keyboard::Key::T: realKey = Keyboard::Key::T; break;
                case sf::Keyboard::Key::U: realKey = Keyboard::Key::U; break;
                case sf::Keyboard::Key::V: realKey = Keyboard::Key::V; break;
                case sf::Keyboard::Key::W: realKey = Keyboard::Key::W; break;
                case sf::Keyboard::Key::X: realKey = Keyboard::Key::X; break;
                case sf::Keyboard::Key::Y: realKey = Keyboard::Key::Y; break;
                case sf::Keyboard::Key::Z: realKey = Keyboard::Key::Z; break;
                case sf::Keyboard::Key::Num1: realKey = Keyboard::Key::NUM1; break;
                case sf::Keyboard::Key::Num2: realKey = Keyboard::Key::NUM2; break;
                case sf::Keyboard::Key::Num3: realKey = Keyboard::Key::NUM3; break;
                case sf::Keyboard::Key::Num4: realKey = Keyboard::Key::NUM4; break;
                case sf::Keyboard::Key::Num5: realKey = Keyboard::Key::NUM5; break;
                case sf::Keyboard::Key::Num6: realKey = Keyboard::Key::NUM6; break;
                case sf::Keyboard::Key::Num7: realKey = Keyboard::Key::NUM7; break;
                case sf::Keyboard::Key::Num8: realKey = Keyboard::Key::NUM8; break;
                case sf::Keyboard::Key::Num9: realKey = Keyboard::Key::NUM9; break;
                case sf::Keyboard::Key::Num0: realKey = Keyboard::Key::NUM0; break;
                default: realKey = Keyboard::Key::UNDEFINED_KEY; break;
                }
                ek.setKey(realKey);
                ek.setKeyboardAction(KEY_RELEASED);
                onEvent(&ek);
                //ek.setKey(p_event->getIf<sf::Event::KeyPressed>()->code);
            }
            
            else if (p_event->is<sf::Event::MouseMoved>()) {
                EventMouse em;
                sf::Vector2i testV;
                sf::Event::MouseMoved* p_mm_event =
                    reinterpret_cast<sf::Event::MouseMoved*> (&e);
                testV = p_mm_event->position;
                df::Vector realVector;
                realVector.setX(testV.x);
                realVector.setY(testV.y);

                em.setMousePosition(realVector);
                em.setMouseAction(MOVED);
                onEvent(&em);

            }

            else if (p_event->is<sf::Event::MouseButtonPressed>()) {
                EventMouse em;
                sf::Vector2i testV;
                sf::Event::MouseButtonPressed* p_mbp_event =
                    reinterpret_cast<sf::Event::MouseButtonPressed*> (&e);
                testV = p_mbp_event->position;
                df::Vector realVector;
                realVector.setX(testV.x);
                realVector.setY(testV.y);

                em.setMousePosition(realVector);
                em.setMouseAction(CLICKED);
                onEvent(&em);

            }

        }
    }
}
