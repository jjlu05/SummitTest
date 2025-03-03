#include "Sprite.h"
#include <iostream>
namespace df {
	Sprite::Sprite(int max_frames) {
		m_frame_count = 0;
		m_width = 0;
		m_height = 0;
		m_frame = new Frame[max_frames];
		m_max_frame_count = max_frames;
		m_color = COLOR_DEFAULT;
		m_slowdown = 0;
	
	
	}

	Sprite::~Sprite() {
		if (m_frame != nullptr) {
			delete[] m_frame;
			m_frame = nullptr;  
		}
	}


	void Sprite::setWidth(int new_width) {
		m_width = new_width;
	}
	int Sprite::getWidth() const {
		return m_width;
	}

	void Sprite::setHeight(int new_height) {
		m_height = new_height;
	}
	int Sprite::getHeight() const{
		return m_height;
	}

	void Sprite::setColor(df::Color new_color) {
		m_color = new_color;
	}
	Color Sprite::getColor() const {
		return m_color;
	}



	int Sprite::getFrameCount() const {
		return m_frame_count;
	}
	int Sprite::addFrame(Frame new_frame) {
		if (m_frame_count == m_max_frame_count) {
			std::cout << "failed";
			return -1;
		}
		else {
			std::cout << "addedFrame ";
			m_frame[m_frame_count] = new_frame;
			m_frame_count++;
		}
	}

	Frame Sprite::getFrame(int frame_number) const {
		if (frame_number < 0 || frame_number >= m_frame_count) {
			Frame emptyFrame;  
			return emptyFrame;
		}
		return m_frame[frame_number];
	}


	void Sprite::setLabel(std::string new_label) {
		m_label=new_label;
	}
	std::string Sprite::getLabel() const {

		return m_label;
	}


	void Sprite::setSlowdown(int new_sprite_slowdown) {
		m_slowdown = new_sprite_slowdown;
	}
	int Sprite::getSlowdown() const {
		return m_slowdown;
	}
	int Sprite::draw(int frame_number, Vector position) const {
		if ((frame_number < 0) || (frame_number > m_frame_count - 1)) {
			std::cout << "BOOM";
			return -1;
		}
		Frame currentFrame = m_frame[frame_number];
		currentFrame.draw(position, m_color);
		return 0;
	}
}