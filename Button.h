#pragma once

class Button
{

public:
	typedef void(*ClickCallback)();
	Button() = delete;
	//overload with other callbacks as needed
	Button(double top, double left, double width, double height, ClickCallback onClick);
	void checkClick(double x, double y);
	~Button() = default;
	ClickCallback m_onClick;
private:
	float m_xMin;
	float m_xMax;
	float m_yMin;
	float m_yMax;
};