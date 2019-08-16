#pragma once
#include "Task.h"
#include "DxLib.h"

class Move : public Task
{
public:
	Move();
	Move(VECTOR inputpos);
	virtual ~Move();

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;   
	virtual void Draw() override;

	void Move_toP(int x, int y, int speed);
	bool Whether_moving();

protected:
	VECTOR pos;

private:
	bool moving;
	int dist_x, dist_y, movespeed;
};
