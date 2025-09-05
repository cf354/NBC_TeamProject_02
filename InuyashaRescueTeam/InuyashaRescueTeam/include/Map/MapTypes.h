#pragma once
#include <cmath>

using namespace std;

namespace Map
{
	struct Vector2D
	{
		Vector2D() : x(0), y(0) {}
		Vector2D(int x, int y) : x(x), y(y) {}

		int x, y;

		inline Vector2D operator+(const Vector2D& other) const
		{
			return Vector2D(this->x + other.x, this->y + other.y);
		}

		inline Vector2D operator-(const Vector2D& other) const
		{
			return Vector2D(this->x - other.x, this->y - other.y);
		}

		inline Vector2D operator+=(const Vector2D& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		inline Vector2D operator-=(const Vector2D& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		inline bool operator ==(const Vector2D& other) const
		{
			return this->x == other.x && this->y == other.y;
		}

		inline static float Distance(const Vector2D& v1, const Vector2D& v2)
		{
			int x = v2.x - v1.x;
			int y = v2.y - v1.y;
			return sqrt(x * x + y * y);
		}
	};

	struct Vector3D
	{
		int x, y, z;
	};

	struct Vector2F
	{
		Vector2F() : x(0.0f), y(0.0f) {}
		Vector2F(const Vector2D& vD) : x(vD.x), y(vD.y) {}
		Vector2F(float x, float y) : x(x), y(y) {}

		float x, y;

		inline Vector2F operator+(const Vector2F& other) const
		{
			return Vector2F(this->x + other.x, this->y + other.y);
		}

		inline Vector2F operator-(const Vector2F& other) const
		{
			return Vector2F(this->x - other.x, this->y - other.y);
		}

		inline Vector2F operator*(float f) const
		{
			return Vector2F(this->x * f, this->y * f);
		}

		inline Vector2F operator/(float f) const
		{
			return Vector2F(this->x / f, this->y / f);
		}

		inline bool operator==(const Vector2F& other) const
		{
			return fabs(this->x - other.x) < 1e-6f && fabs(this->y - other.y) < 1e-6f;
		}

		inline static float Distance(const Vector2F& v1, const Vector2F& v2)
		{
			float x = v2.x - v1.x;
			float y = v2.y - v1.y;
			return sqrt(x * x + y * y);
		}

		inline static Vector2F Lerp(const Vector2F& start, const Vector2F& end, float f)
		{
			f = fmin(1.0f, fmax(0.0f, f));
			return Vector2F(start + (end - start) * f);
		}
	};

	struct MapObj
	{
		// 좌하단 원점
		Vector2D pos;
		Vector2D sizeCollider;
		Vector2D sizeRender;
		string strRender;
	};
}
