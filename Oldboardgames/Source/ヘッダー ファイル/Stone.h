#pragma once
#include "Move.h"
#include <string>

class Stone : public Move
{
public:
	Stone();
	~Stone();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

private:
	const std::string coin_filepath = "Assets//coin";
	int coinHandle;
};