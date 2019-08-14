#pragma once
class OtherInterface
{
public:
	virtual ~OtherInterface() {}
	virtual bool KeyUp(unsigned char key) = 0;
	virtual bool KeyDown(unsigned char key) = 0;
	virtual const int* Key_Frame() = 0;
};

