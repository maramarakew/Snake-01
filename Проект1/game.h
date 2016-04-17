#pragma once
#pragma once

class Game
{
public:
	Game();
	void Draw();
	enum { FieldWidth = 9, FieldHeight = 9 };
	enum State { CLOSED, OPENED, FLAG };
	struct Cell
	{
		State state;
		bool HasMine;
		int MinesAround;
	};
	Cell Field[FieldWidth][FieldHeight];
	void Open(int x, int y);
	void Mark(int x, int y);
	void OpenEmptyCells(int x, int y);
};
