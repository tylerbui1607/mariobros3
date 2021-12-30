#pragma once
#include "Game.h"
#include"Mario.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Coin.h"
#include "Platform.h"
#include "Camera.h"
#include "Map.h"
#include "ColorBox.h"
#include "Koopas.h"
#include "Pipe.h"
#include "BreakableBrick.h"
#include "PortalOfPipe.h"
#include "PiranhaPlant.h"
#define Sequence1MaxTime	2000

class IntroScene :
    public CScene
{
protected:
	// A play scene has to have player, right? 

	vector<LPGAMEOBJECT> objects;




	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);


	void LoadAssets(LPCWSTR assetFile);

public:
	CMario* redMario;
	CMario* greenMario;
	CPlatform* platform;
	ULONGLONG SequenceTime;
	IntroScene(int id, LPCWSTR filePath);
	bool isDoneSeq1,isDoneSeq2, isFirstJump;
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void ScriptIntro()
	{
		if (SequenceTime == 0)
			SequenceTime = GetTickCount64();
		if (!isDoneSeq1)
		{
			if(GetTickCount64()-SequenceTime >= Sequence1MaxTime )
			isDoneSeq1 = true;
		}
		if (isDoneSeq1 && !isDoneSeq2)
		{
			float vx, vy;
			redMario->GetSpeed(vx, vy);
			if (vx == 0)
			{
				redMario->SetState(MARIO_STATE_WALKING_RIGHT);
				greenMario->SetState(MARIO_STATE_WALKING_LEFT);
			}
			if (GetTickCount64() - SequenceTime >= Sequence1MaxTime + 2000 && !isFirstJump)
			{
				redMario->SetState(MARIO_STATE_JUMP);
				isFirstJump = true;
			}
			redMario->IsAllowRender = true;
			greenMario->IsAllowRender = true;
			if (GetTickCount64() - SequenceTime >= Sequence1MaxTime + 1500)
			{
				redMario->IsAllowUpdate = true;
				greenMario->IsAllowUpdate = true;
			}
			if (greenMario->x <= CGame::GetInstance()->GetBackBufferWidth() / 2)
			{
				if(!greenMario->CheckIsSitting())
				greenMario->SetState(MARIO_STATE_SIT);
			}
			if (redMario->x >= CGame::GetInstance()->GetBackBufferWidth() / 2 - 10) {
				if (redMario->y >= 402 - 30)
				{
					redMario->SetMaxVx(0.15f);
					redMario->SetSpeed(0.15f, -0.5f);
				}
			}
			if (GetTickCount64() - SequenceTime >= Sequence1MaxTime + 3500)
				isDoneSeq2 = true;
		}
		//if (isDoneSeq2)
		//	CGame::GetInstance()->InitiateSwitchScene(2);
	}
	void Clear();
	void PurgeDeletedObjects();

};

typedef IntroScene* LPINTROSCENE;