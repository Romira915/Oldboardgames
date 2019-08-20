#include "CoinManager.h"

CoinManager::CoinManager()
{
	VECTOR tmp[BOARD_NUM] = { {473,803,0},{599,639,0},{725,802,0},{868,638,0},{1007,803,0},{1145,644,0},{1284,800,0},{1447,500,0},{1290,191,0},{1161,351,0},{1032,193,0},{890,352,0},{755,188,0},{620,354,0},{470,194,0},{294,504,0}, };
	for (int i = 0; i < BOARD_NUM; i++)
	{
		coindrawpos5[i] = tmp[i];
	}
}

CoinManager::~CoinManager()
{
}

void CoinManager::Initialize()
{
}

void CoinManager::Finalize()
{
}

void CoinManager::Update()
{
}

void CoinManager::Draw()
{
}
