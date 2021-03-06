#include "FirePiranhaPlant.h"
#include "debug.h"

void FirePiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (PlantType == FIREPLANT)
	{
		top = y - FIRE_PIRANHAPLANT_UP_HEIGHT / 2;
		bottom = top + FIRE_PIRANHAPLANT_BBOX_HEIGHT;
	}
	else {
		top = y - GREEN_PIRANHAPLANT_BBOX_HEIGHT / 2;
		bottom = top + GREEN_PIRANHAPLANT_BBOX_HEIGHT;
	}
	left = x - FIRE_PIRANHAPLANT_BBOX_WIDTH / 2;
	right = left + FIRE_PIRANHAPLANT_BBOX_WIDTH;
	
}

void FirePiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (vy < 0) {
		if (y <= minY) {
			vy = 0;
			y = minY;
		}
	}
	else if (vy > 0) {
		if (y >= maxY) {
			vy = 0;
			y = maxY;
		}
	}
	if (y == minY) {
		CalcAtatckEnemy();
	}
	if (state == FIRE_PIRANHAPLANT_STATE_UP) {
		if (x == CGame::GetInstance()->pipeX && isInPipe)
			vy = 0;
		else if (GetTickCount64() - CalcAtkTime >= 3000) {
			SetState(FIRE_PIRANHAPLANT_STATE_DOWN);
		}
	}
	else {
		if (GetTickCount64() - CalcAtkTime >= 2000) {
			SetState(FIRE_PIRANHAPLANT_STATE_UP);
		}
	}
	
	if (y > minY + FIRE_PIRANHAPLANT_UP_HEIGHT)
	{
		isInPipe = true;
	}
	else {
		isInPipe = false;
	}

	if (fireBullet->isActivate)
		fireBullet->Update(dt,coObjects);
	y += vy * dt;
}

void FirePiranhaPlant::Render()
{
	aniId = -1;
	if (PlantType == FIREPLANT)
		GetAniFirePlant();
	else
		GetAniGreenFirePlant();
	CAnimations* animations = CAnimations::GetInstance();
	if(animations->Get(aniId))
		animations->Get(aniId)->Render(x, y);
	if (fireBullet->isActivate)
	{
		fireBullet->Render();
	}
}

void FirePiranhaPlant::GetAniFirePlant()
{
	if (x > enemyX) {
		if (y == minY) {
			if (enemyY < minY)aniId = ID_ANI_FIREPLANT_ATTACK_LEFT_UP;
			else aniId = ID_ANI_FIREPLANT_ATTACK_LEFT_DOWN;
		}
		else if (enemyY < minY)aniId = ID_ANI_FIREPLANT_LEFT_UP;
		else aniId = ID_ANI_FIREPLANT_LEFT_DOWN;
	}
	else {
		if (y == minY) {
			if (enemyY < minY)aniId = ID_ANI_FIREPLANT_ATTACK_RIGHT_UP;
			else aniId = ID_ANI_FIREPLANT_ATTACK_RIGHT_DOWN;
		}
		else if (enemyY < minY)aniId = ID_ANI_FIREPLANT_RIGHT_UP;
		else aniId = ID_ANI_FIREPLANT_RIGHT_DOWN;
	}
		
	if (aniId == -1) aniId = ID_ANI_FIREPLANT_LEFT_DOWN;
}

void FirePiranhaPlant::GetAniGreenFirePlant()
{
	if (x > enemyX) {
		if (y == minY) {
			if (enemyY < minY)aniId = ID_ANI_GREEN_FIREPLANT_ATTACK_LEFT_UP;
			else aniId = ID_ANI_GREEN_FIREPLANT_ATTACK_LEFT_DOWN;
		}
		else if (enemyY < minY)aniId = ID_ANI_GREEN_FIREPLANT_LEFT_UP;
		else aniId = ID_ANI_GREEN_FIREPLANT_LEFT_DOWN;
	}
	else {
		if (y == minY) {
			if (enemyY < minY)aniId = ID_ANI_GREEN_FIREPLANT_ATTACK_RIGHT_UP;
			else aniId = ID_ANI_GREEN_FIREPLANT_ATTACK_RIGHT_DOWN;
		}
		else if (enemyY < minY)aniId = ID_ANI_GREEN_FIREPLANT_RIGHT_UP;
		else aniId = ID_ANI_GREEN_FIREPLANT_RIGHT_DOWN;
	}

	if (aniId == -1) aniId = ID_ANI_GREEN_FIREPLANT_LEFT_DOWN;
}

void FirePiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIRE_PIRANHAPLANT_STATE_UP:
		vy = -0.05f;
		CalcAtkTime = GetTickCount64();
		break;
	case FIRE_PIRANHAPLANT_STATE_DOWN:
		vy = 0.05f;
		CalcAtkTime = GetTickCount64();
		break;
	default:
		break;
	}
}


