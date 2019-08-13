#include "Other.h"
#include "DxLib.h"

Other::Other()
{
}

Other::~Other()
{
}

void Other::Initialize()
{
	for (int i = 0; i < 256; i++)
	{
		key_frame[i] = 0;
		key_previous[i] = 0;
	}
}

void Other::Finalize()
{
}

void Other::Update()
{
	char tmpkey[256];
	GetHitKeyStateAll(tmpkey);

	for (int i = 0; i < 256; i++)
	{
		key_previous[i] = key_frame[i];
	}

	for (int i = 0; i < 256; i++)
	{
		if (tmpkey[i] != 0)
		{
			key_frame[i]++;
		}
		else {
			key_frame[i] = 0;
		}
	}
}

bool Other::KeyUp(unsigned char key)
{
	if (key_previous[key] != 0 && key_frame[key] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Other::KeyDown(unsigned char key)
{
	if (key_previous[key] == 0 && key_frame[key] != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const int* Other::Key_Frame()
{
	return key_frame;
}
