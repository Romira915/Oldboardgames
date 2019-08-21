#pragma once
#include "Task.h"
#include "DxLib.h"

class Move : public Task
{
public:
	Move();
	Move(VECTOR inputpos);
	virtual ~Move() override;

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;   
	virtual void Draw() override;

	void Move_toP(float x, float y, float speed);
	bool Whether_moving();

protected:
	VECTOR pos;

private:
	bool moving;
	float dist_x, dist_y, movespeed;
	float delta_x, delta_y;
	float maxframe, counter;
};
