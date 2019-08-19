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

	void Move_toP(double x, double y, double speed);
	bool Whether_moving();

protected:
	VECTOR pos;

private:
	bool moving;
	double dist_x, dist_y, movespeed;
	double delta_x, delta_y;
	double maxframe, counter;
};
