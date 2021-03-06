#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <algorithm>
#include "GameLevel.h"
#include "BallObject.h"
#include "ParticleGenerator.h"
#include "PostProcessor.h"
#include "PowerUp.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

struct Boom {
	ParticleGenerator boom[15];
	double lifes[15];
	bool alive[15];
	GameObject target[15];
	Boom() {}

	Boom(const Shader &shader,const Texture2D &tex) {
		for (auto x = 0; x < 15; ++x) {
			lifes[x] = 0.0f;
			alive[x] = false;
			boom[x] = ParticleGenerator(shader, tex, 200, 40.0f);
		}
	}
};

class Game
{
public:
	//生命值
	GLuint Lives;
	//当前游戏状态
	GameState		State;
	GLboolean		Keys[1024];//键盘响
	GLboolean KeysProcessed[1024];
	GLuint			Width, Height;//游戏宽高
	//游戏关卡
	std::vector<GameLevel> Levels;
	GLuint                 Level;

	//道具
	std::vector<PowerUp>  PowerUps;
	void SpawnPowerUps(GameObject &block);
	void UpdatePowerUps(GLfloat dt);

	Game(GLuint width, GLuint height);
	~Game();
	//游戏初始化
	void Init();
	//游戏循环
	void ProcessInput(GLfloat dt);//处理输入
	void Update(GLfloat dt);//更新
	void Render();//渲染

	//碰撞检测
	void DoCollisions();
private:
	Boom boom;
	GLboolean CheckCollisionAABB(GameObject &one, GameObject &two);
	Collision CheckCollisionSphere(BallObject &one, GameObject &two);
	Direction VectorDirection(glm::vec2 target);
	void ResetLevel();
	void ResetPlayer();
};

