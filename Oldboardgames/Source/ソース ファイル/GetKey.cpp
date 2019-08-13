#include "GetKey.h"
#include "DxLib.h"

GetKey::GetKey()
{
}

GetKey::~GetKey()
{
}

void GetKey::Initialize()
{
	for (int i = 0; i < 256; i++)
	{
		key_frame[i] = 0;
		key_previous[i] = 0;
	}
}

void GetKey::Finalize()
{
}

void GetKey::Update()
{
	char tmpkey[256];
	GetHitKeyStateAll(tmpkey);

	for (int i = 0; i < 256; i++)
	{
		key_previous[i] = key_frame[i];
	}

	for (int i = 0; i < 256; i++)
	{
		if (tmpkey[i] == 1)
		{
			key_frame[i]++;
		}
		else {
			key_frame[i] = 0;
		}
	}
}
