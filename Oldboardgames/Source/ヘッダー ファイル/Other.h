#pragma once
#include "Task.h"
#include "OtherInterface.h"

class Other : public OtherInterface, Task
{
public:
	Other();
	~Other();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override {}

	bool KeyUp(unsigned char key) override;
	bool KeyDown(unsigned char key) override;
	const int* Key_Frame() override;

private:
	int key_frame[256];
	int key_previous[256];
};

