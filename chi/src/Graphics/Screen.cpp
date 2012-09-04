#include "chi-global.h"

#include "Screen.h"

namespace chi {

Factory<Screen> *Screen::factory = NULL;

void Screen::set(int width, int height, ScreenFlags f) {
	CHI_UNUSED(f);

	m_width = width;
	m_height = height;
}

int Screen::width() const {
	return m_width;
}

int Screen::height() const {
	return m_height;
}

}

