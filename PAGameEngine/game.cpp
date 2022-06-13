#include "game.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

vector<string> split0(string line) {
	string word;
	vector<string> words;
	istringstream ss(line);
	while (cin >> word) {
		words.push_back(word);
	}
	return words;
}

vector<string> split(string line, char delim = ' ') {
	string word;
	vector<string> words;
	istringstream ss(line);
	while (getline(ss, word, delim)) {
		words.push_back(word);
	}
	return words;
}

class ExceptionGame :public exception {
public:
	virtual const char* what() const throw() {
		return "Customized ExceptionGame error";
	}
};

void Game::init() {

	LoaderOBJ::setBasePath(".\\3dModels");

	//////////////////
	//Escena del juego
	GameScene* gameScene = new GameScene();


	scenes.push_back(gameScene);

	///////////////////////
	//Escena de la interfaz
	MenuScene* menuScene = new MenuScene();


	scenes.push_back(menuScene);

	////////////////////
	//Escena del ranking
	RankingScene* rankingScene = new RankingScene();


	scenes.push_back(rankingScene);

	activeScene = menuScene;

}

void Game::render() {
	this->activeScene->render();
}

void Game::update() {

	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	if ((currentTime.count() - this->initialMilliseconds.count()) - this->lastUpdatedTime > UPDATE_PERIOD)
	{
		this->activeScene->update(TIME_INCREMENT);
		this->lastUpdatedTime = currentTime.count() - this->initialMilliseconds.count();
	}

	if ((this->activeScene == this->scenes[0]) && (this->activeScene->detectaDerrota())) {
		this->activeScene->resetScene();
		scenes[2]->dibujaRanking();
		this->activeScene = this->scenes[1];
	}


}

void Game::processKeyPressed(unsigned char key, int x, int y) {
	
	if (this->activeScene == this->scenes[1]) {
		if (key == '1') {
			this->activeScene = this->scenes[0];
		}
		else if (key == '4') {
			this->activeScene = this->scenes[2];
		}
	}
	else if(this->activeScene == this->scenes[2]){
		if (key == '4') {
			this->activeScene = this->scenes[1];
		}
	}

	this->activeScene->processKeyPressed(key, x, y);
}

void Game::processMouseMovement(int x, int y) {
	this->activeScene->processMouseMovement(x, y);
}

void Game::processMouseClick(int button, int state, int x, int y) {
	this->activeScene->processMouseClick(button, state, x, y);
}

