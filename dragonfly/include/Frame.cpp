﻿#include "Frame.h"
#include "DisplayManager.h"
#include "stdio.h"
#include <cstdio>
#include <iostream>

namespace df {
	Frame::Frame() :m_width(0), m_height(0), m_frame_str() {
	
	}
	Frame::Frame(int init_width, int init_height, std::string init_frame_str) {
		m_width = init_width;
		m_height = init_height;
		m_frame_str = init_frame_str;
	}



    // Set width of frame.
    void Frame::setWidth(int new_width) {
        m_width = new_width;
    };

    // Get width of frame.
    int Frame::getWidth() const {
        return m_width;
    };

    // Set height of frame.
    void Frame::setHeight(int new_height) {
        m_height = new_height;
    };

    // Get height of frame.
    int Frame::getHeight() const {
        return m_height;
    };

    // Set frame characters (stored as string).
    void Frame::setString(std::string new_frame_str) {
        m_frame_str = new_frame_str;
    };

    // Get frame characters (stored as string).
    std::string Frame::getString() const {
        return m_frame_str;
    };

    // Draw self, centered at position (x, y) with color.
 // Return 0 if ok, else −1.
 // Note: top-left coordinate is (0,0).
    int Frame::draw(Vector position, Color color) const {

        // Error check empty string.
        if (m_frame_str.empty()) {
            return -1;
        }
            // Determine offsets since centered at position.
        int x_offset = getWidth() / 2;
        int y_offset = getHeight() / 2;

        // Draw character by character.
        for (int y = 0; y < m_height; y++) {
            for (int x = 0; x < m_width; x++) {
                Vector temp_pos(position.getX() + x - x_offset,
                    position.getY() + y - y_offset);
                DM.drawCh(temp_pos, m_frame_str[y * m_width + x], color);
            }
        }
            
        

    }
}