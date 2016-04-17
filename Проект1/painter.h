#pragma once

class Painter
{
public:
	static const int CellSize = 16;
	void DrawClosedCell(int x, int y); //��������� �������� ������
	void DrawOpenedCell(int x, int y, int MinesAround); //��������� �������� ������
	void DrawFlag(int x, int y); //��������� �����
	void DrawMine(int x, int y); //��������� ����
private:
	void DrawOpenedCell(int x, int y); //��������� ��������� ������.Private, ������ ��� ������������ ������ ������ ���������
};
