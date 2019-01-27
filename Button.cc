#include "Button.h"
#include <iostream>

Button::Button(double x_min, double x_max, double y_min, double y_max, ClickCallback onClick) :
	m_xMin(x_min),
	m_xMax(x_max),
	m_yMin(y_min),
	m_yMax(y_max),
	m_onClick(onClick) {
}

void Button::checkClick(double x, double y) {
	
	if ( m_xMax >= x &&  m_xMin <= x &&
		 m_yMax >= y && m_yMin <= x) {
		m_onClick();
	}
}

