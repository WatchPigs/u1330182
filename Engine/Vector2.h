#pragma once

namespace Engine
{
	class Vector2
	{
	public:
		Vector2(float x, float y);
		float GetX() const;
		float GetY() const;
		void SetX(float x);
		void SetY(float y);
		void operator+=(const Vector2& other);
		void operator-=(const Vector2& other);
		void operator*=(float i);
		void operator/=(float i);
		Vector2 operator*(float i) const;
		Vector2 operator/(float i) const;
		Vector2 operator+(Vector2 p) const;
		Vector2 operator-(Vector2 p) const;
		bool operator==(Vector2 p) const;
		bool operator!=(Vector2 p) const;
		Vector2 operator-() const;

		static const Vector2 Zero;

	private:
		float m_x;
		float m_y;
	};

	Vector2 operator*(float i, Vector2 p);
}
