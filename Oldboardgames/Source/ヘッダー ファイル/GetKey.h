#pragma once
#include "Task.h"

class GetKey : public Task
{
public:
	GetKey();
	~GetKey();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override {}

private:
	char key_frame[256];
	char key_previous[256];
};

