#pragma once

class Point2D
{
private:
	int m_x;
	int m_y;
public:
	Point2D(int x, int y);
	int GetX() const;
	int GetY() const;
	void SetX(int x);
	void SetY(int y);
	void operator+=(Point2D& other);
	Point2D operator*(int i) const;
	Point2D operator+(Point2D p) const;
	Point2D operator-(Point2D p) const;
	bool operator==(Point2D p) const;
	bool operator!=(Point2D p) const;
};
