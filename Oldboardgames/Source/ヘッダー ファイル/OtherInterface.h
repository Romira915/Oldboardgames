#pragma once
class OtherInterface
{
public:
	virtual bool KeyUp(unsigned char key) = 0;
	virtual bool KeyDown(unsigned char key) = 0;
	virtual const int* Key_Frame() = 0;
};

