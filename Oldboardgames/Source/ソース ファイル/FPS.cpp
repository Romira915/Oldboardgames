#include "FPS.h"
#include "DxLib.h"

FPS::FPS()
{
	fps = 60;
	n = 60;
}

FPS::FPS(int setfps, int setN)
{
	fps = setfps;
	n = setN;
}

FPS::~FPS()
{
	DeleteFontToHandle(fontHandle);
}

void FPS::Initialize()
{
	fontHandle = CreateFontToHandle(NULL, FPS_FONTSIZE * SCREEN_SIZEX, -1);
	counter = 0;
	nowfps = 0;
	starttime = 0;
}

void FPS::Finalize()
{
}

void FPS::Update()
{
	if (counter == 0)
	{
		starttime = GetNowCount();
	}
	if (counter == n)
	{
		int t = GetNowCount();
		nowfps = 1000.0 / ((t - starttime) / float(n));
		starttime = t;
		counter = 0;
	}

	fpsstring = std::to_string(nowfps);
	stringwidth = GetDrawStringWidthToHandle(fpsstring.c_str(), fpsstring.length(), fontHandle);
	counter++;
}

void FPS::Draw()
{
	DrawStringToHandle(SCREEN_SIZEX - stringwidth, 0, fpsstring.c_str(), GetColor(0, 128, 0), fontHandle);
}

void FPS::Wait()
{
	int tooktime = GetNowCount() - starttime;
	int waittime = counter * 1000 / fps - tooktime;
	if (waittime > 0)
	{
		WaitTimer(waittime);
	}
}
