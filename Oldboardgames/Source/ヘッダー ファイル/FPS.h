#pragma once
#include "Task.h"
#include <string>

#define FONTSIZE 40 / STD_SCREENSIZEX

class FPS : public Task
{
public:
	FPS();
	FPS(int setfps, int setN);
	~FPS();

	void Initialize() override;	//������
	void Finalize() override;	//�I������
	void Update() override;		//�X�V
	void Draw() override;		//�`��
	void Wait();

private:
	int fontHandle;
	int counter;
	int nowfps;
	int starttime;

	int fps;
	int n;

	int stringwidth;
	std::string fpsstring;
};

