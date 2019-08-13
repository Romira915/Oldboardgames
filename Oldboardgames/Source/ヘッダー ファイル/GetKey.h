#pragma once
#include "Task.h"
#include "OtherInterface.h"

class GetKey : public OtherInterface, Task
{
public:
	GetKey();
	~GetKey();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override {}

	bool KeyUp(char key);
	bool KeyDown(char key);

private:
	char key_frame[256];
	char key_previous[256];
};

