#pragma once
#include "Move.h"
#include <string>

class Coin : public Move
{
public:
	Coin();
	Coin(int Handle);
	~Coin();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	const std::string coin_filepath = "Assets//coin";
	int coinHandle;
};