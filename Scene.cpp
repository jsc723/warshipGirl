#include "stdafx.h"
#include "Scene.h"


Scene::Scene(wstring bgName)
{
	timerIdShowText = 0;
	state = Normal;
	frame = 0;
	IN_FM = 30;
	bgFileName = bgName;
	shadeCount = 0;
	this->bg = db->getBitmap(bgName);
	InitOnClick();
}

void Scene::AddComponent(Component *com)
{
	components.push_back(com);
	com->AddToScene(this, components.size() - 1);
}

void ComponentResourceBarOnClick(Component *self, int x, int y, WPARAM wParam)
{
	//TODO
	db->oil += 5;
	db->alumin += 5;
	db->steel += 5;
	db->bullet += 5;
}

void Scene::AddResourceBar(int dx)
{
	Component *resourceBar = new Component(L"resourceBar.png", 355 + dx, 0, 0);
	int compX = resourceBar->x, compY = resourceBar->y;
	Label *oilLabel = new LabelInt(100 + compX, 4 + compY, 15, 8, DT_RIGHT | DT_NOCLIP,
		255, 255, 255, 255, &(db->oil));
	resourceBar->AddLabel(oilLabel);
	Label *bulletLabel = new LabelInt(220 + compX, 4 + compY, 15, 8, DT_RIGHT | DT_NOCLIP,
		255, 255, 255, 255, &(db->bullet));
	resourceBar->AddLabel(bulletLabel);
	Label *steelLabel = new LabelInt(340 + compX, 4 + compY, 15, 8, DT_RIGHT | DT_NOCLIP,
		255, 255, 255, 255, &(db->steel));
	resourceBar->AddLabel(steelLabel);
	Label *aluminLabel = new LabelInt(460 + compX, 4 + compY, 15, 8, DT_RIGHT | DT_NOCLIP,
		255, 255, 255, 255, &(db->alumin));
	resourceBar->AddLabel(aluminLabel);
	Label *diamondLabel = new LabelInt(600 + compX, 4 + compY, 15, 8, DT_RIGHT | DT_NOCLIP,
		255, 255, 255, 255, &(db->diamond));
	resourceBar->AddLabel(diamondLabel);
	resourceBar->SetChangingSceneBehaivor(0, -57);
	AddComponent(resourceBar);
}


void Scene::AddReturnBtn()
{
	Component *returnDock = new Component(L"returnDock.png", 0, H - 105, 0);
	returnDock->InstallOnClick([](Component *self, int x, int y, WPARAM wParam)
	{
		self->scene->MoveToOtherScene(sceneDock);
	});
	returnDock->SetChangingSceneBehaivor(-150, 0);
	AddComponent(returnDock);
}

void Scene::SetComponent(Component *com, int i)
{
	delete components[i];
	components[i] = com;
	com->AddToScene(this, i);
}

void Scene::DelComponent(int i)
{
	delete components[i];
	for (int j = i; j < components.size() - 1; j++) {
		components[j] = components[j + 1];
	}
	components.erase(components.end()-1);
	InitOnClick();
	for (int j = 0; j < components.size(); j++) {
		components[j]->AddToScene(this, j);
	}
}

void Scene::DelComponent(Component * com)
{
	for (int i = components.size() - 1; i >= 0; i--)
	{
		if (components[i] == com) {
			DelComponent(i);
			return;
		}
	}
}


void Scene::AddShade()
{
	Component *shade = new Component(L"black.png", 0, 0, Component::LP_SHADE);
	shade->diffuse = D3DCOLOR_ARGB(128, 255, 255, 255);
	shade->StartPaint();
	shade->InstallOnClick([](Component *self, int x, int y, WPARAM wParam) {/*do nothing*/});
	AddComponent(shade);
	shadeCount++;
}
void Scene::DelShade()
{
	if (shadeCount <= 0) return;
	for (int i = components.size() - 1; i >= 0; i--)
	{
		if (components[i]->lParam == Component::LP_SHADE) {
			DelComponent(i);
			shadeCount--;
			break;
		}
	}
}


void ComMB_OK_CC_OnClick(Component *self, int x, int y, WPARAM wParam) {
	x -= self->x;
	y -= self->y;
	Scene::MB_STATE *m = (Scene::MB_STATE *)(self->lParam);
	if (y >= 238 && y <= 284) {
		if (x >= 102 && x <= 218) {
			((ComponentMsgBox *)self)->closeMsgBox();
			m->clicked = true;
			m->ok = true;
		}
		else if (x >= 328 && x <= 450) {
			((ComponentMsgBox *)self)->closeMsgBox();
			m->clicked = true;
			m->ok = false;
		}
	}
}

bool Scene::SceneMessageBox(LPWSTR title, LPWSTR msg, int option, POINT pt)
{
	AddShade();
	MB_STATE m;
	ZeroMemory(&m, sizeof(m));
	Component *mb = new ComponentMsgBox(L"MB_OK_CANCEL.png", pt.x, pt.y, (LPARAM)&m);
	mb->InstallOnClick(ComMB_OK_CC_OnClick);
	mb->AddLabel(new LabelStr(pt.x + 100, pt.y + 5, 200, 80, DT_NOCLIP | DT_LEFT, 255, 0, 0, 0, title, fontMsg));
	mb->AddLabel(new LabelStr(pt.x + 180, pt.y + 140, 200, 80, DT_NOCLIP | DT_CENTER, 255, 0, 0, 0, msg, fontMsg));
	mb->StartPaint();
	AddComponent(mb);
	RunUntilTrue(&(m.clicked));
	DelComponent(mb);
	DelShade();
	return m.ok;
}

Scene::~Scene()
{
	EndPaint();
	for (auto &c : components) {
		if (NULL != c) {
			delete c;
			c = NULL;
		}
	}
	components.clear();
	timer->KillTimer(DISPID_TEXT);
}
void Scene::StartPaint()
{
	bgTexture = new d3dTexture(db->pathList[bgFileName.c_str()].c_str(),
		db->getBitmap(bgFileName));
	for (auto const &c : components)
	{
		c->StartPaint();
	}
}
void Scene::DrawMovingComponents(bool movingIn)
{
	d3dReadyPaintBG();
	bgTexture->BltFast(0, 0, W, H);
	d3dReadyPaintCom();
	int dframe = IN_FM - frame;
	int deltaF = (movingIn) ? dframe : frame;
	double r = (double) deltaF / IN_FM;
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->OnPaintMoving(r);
	}
	const int w = 100, h = 20;
	d3dDrawText(fontDebugInfo, text.c_str(), (W - w)/2, (H - h) / 2, w, h, DT_CENTER | DT_NOCLIP,
		255, 0, 0, 0);
}
void Scene::DrawNormalComponents()
{
	d3dReadyPaintBG();
	bgTexture->BltFast(0, 0, W, H);
	d3dReadyPaintCom();
	for (int i = 0; i<components.size(); i++)
	{
		components[i]->OnPaint();
	}
	const int w = 100, h = 20;
	d3dDrawText(fontDebugInfo, text.c_str(), (W - w) / 2, (H - h) / 2, w, h, DT_CENTER | DT_NOCLIP,
		255, 0, 0, 0);
}
void Scene::InitOnClick()
{
	for (int i = 0; i < W; i++)
		for (int j = 0; j < H; j++)
			onClickDecide[i][j] = -1;
}
void Scene::OnPaint()
{
	if (state == MovingIn) {
		DrawMovingComponents(true);
		if (++frame == IN_FM)
			state = Normal;
	}
	else if (state == Normal) {
		DrawNormalComponents();
	}
	else if (state == MovingOut) {
		DrawMovingComponents(false);
		if (++frame == IN_FM)
		{
			state = NUL;
			next->MoveIn();
		}
	}
}

void Scene::EndPaint()
{
	if (bgTexture) {
		delete bgTexture;
		bgTexture = NULL;
	}
	for (auto c : components)
	{
		c->EndPaint();
	}
}

void Scene::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	if (state != Normal)
		return;
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	if (x< 0 || x > W || y < 0 || y > H)
		return;
	int index = onClickDecide[x][y];
	if (index != -1)
		components[index]->OnClick(components[index], x, y, wParam);
	else
	{
		//TODO
		wchar_t message[50];
		wsprintf(message, L"Background (%d,%d) clicked!", x, y);
		ShowText(message, 1000);
	}
}
void Scene::OnTimer(int id)
{
	if (id == timerIdShowText)
		text = L"";
}
void Scene::MoveIn(bool moveInEffect)
{
	frame = 0; 
	sceneLast = sceneNow;
	if (sceneLast) 
		sceneLast->EndPaint(); 
	sceneNow = this; 
	if (moveInEffect)
		state = MovingIn;
	else
		state = Normal;
	StartPaint(); 
}
void Scene::MoveToOtherScene(Scene * other, bool moveOutEffect, bool moveInEffect)
{
	frame = 0; state = MovingOut; next = other;
	if (!moveOutEffect) {
		state = NUL;
		next->MoveIn(moveInEffect);
	}
}
void Scene::ShowText(wstring text, int time_ms)
{
	this->text = text;
	timerIdShowText = timer->AddMilliTimer(time_ms, 1, this);
}
//sceneShipList & sceneRepairSelect both use this
void ComRightOptOnClick(Component *self, int x, int y, WPARAM wParam)
{
	x -= self->x;
	y -= self->y;
	if (x > 27 && y > 500 && x < 105 && y < 546) {
		self->scene->MoveToOtherScene(sceneLast, false);
	}
	else {
		wchar_t message[50];
		wsprintf(message, L"ShipListOpt (%d,%d) clicked!", x, y);
		self->scene->ShowText(message, 1000);
	}
}
