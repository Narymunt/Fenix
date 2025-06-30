// klasa do operacji na vectorach 3d

#pragma once
#include <math.h>

class CVector3 
{

public:
	float x;
	float y;
	float z;

	// konstruktor
	CVector3(float a = 0, float b = 0, float c = 0) : x(a), y(b), z(c) {}
	CVector3(const CVector3 &vec) : x(vec.x), y(vec.y), z(vec.z) {}

	//podstawienie wektora
	const CVector3 &operator=(const CVector3 &vec) 
   {
		x = vec.x;
		y = vec.y;
		z = vec.z;

		return *this;
	}

	//równoœæ wektorów
	const bool operator==(const CVector3 &vec) const 
   {
		return ((x == vec.x) && (y == vec.y) && (z == vec.z));
	}

	//nierównoœæ wektorów
	const bool operator!=(const CVector3 &vec) const 
   {
		return !(*this == vec);
	}

	// dodawanie wektorów
	const CVector3 operator+(const CVector3 &vec) const 
   {
		return CVector3(x + vec.x, y + vec.y, z + vec.z);
	}

	// dodawanie wektorów
	const CVector3 operator+() const 
   {    
		return CVector3(*this);
	}

	// dodawanie wektorów
	const CVector3& operator+=(const CVector3& vec) 
   {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	// odejmowanie wektorów
	const CVector3 operator-(const CVector3& vec) const 
   {    
		return CVector3(x - vec.x, y - vec.y, z - vec.z);
	}

	// odejmowanie wektorów
	const CVector3 operator-() const 
   {    
		return CVector3(-x, -y, -z);
	}

	// odejmowanie wektorów
	const CVector3 &operator-=(const CVector3& vec) 
   {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;

		return *this;
	}

	// mno¿enie wektora przez skalar
	const CVector3 &operator*=(const float &s) 
   {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	
   const CVector3 &operator*=(const CVector3 &s) 
   {
		x *= s.x;
		y *= s.y;
		z *= s.z;
		
		return *this;
	}
	
   // dzielenie wektora przez skalar
	const CVector3 &operator/=(const float &s) 
   {
		const float recip = 1/s;

		x *= recip;
		y *= recip;
		z *= recip;

		return *this;
	}

	// mno¿enie wektora przez skalar
	const CVector3 operator*(const float &s) const 
   {
		return CVector3(x*s, y*s, z*s);
	}
	
   // mno¿enie wektora przez skalar
	const CVector3 operator*(const CVector3 &s) const 
   {
		return CVector3(x*s.x, y*s.y, z*s.z);
	}
	
   // mno¿enie wektora przez skalar
	friend inline const CVector3 operator*(const float &s, const CVector3 &vec) 
   {
		return vec*s;
	}

	// dzielenie wektora przez skalar
	const CVector3 operator/(float s) const 
   {
		s = 1/s;
		return CVector3(s*x, s*y, s*z);
	}

	// iloczyn wektorowy
	const CVector3 crossProduct(const CVector3 &vec) const 
   {
		return CVector3(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
	}

	// iloczyn wektorowy
	const CVector3 operator^(const CVector3 &vec) const 
   {
		return CVector3(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
	}

	// iloczyn skalarny
	const float dotProduct(const CVector3 &vec) const 
   {
		return x*vec.x + y*vec.x + z*vec.z;
	}

	// iloczyn skalarny
	const float operator%(const CVector3 &vec) const {
		return x*vec.x + y*vec.x + z*vec.z;
	}

	// d³ugoœæ wektora
	const float length() const 
   {
		return (float)sqrt((double)(x*x + y*y + z*z));
	}

	// wektor jednostkowy
	const CVector3 unitVector() const 
   {
		return (*this) / length();
	}

	// normalizacja wektora
	void normalize() 
   {
		(*this) /= length();
	}

	// operator modu³u (d³ugoœci) wektora
	const float operator!() const 
   {
		return sqrt(x*x + y*y + z*z);
	}

	// zmienia d³ugoœæ wektora
	const CVector3 operator | (const float length) const 
   {
		return *this*(length/!(*this));
	}

	// zmienia d³ugoœæ wektora
	const CVector3& operator |= (const float length) 
   {
		return *this = *this | length;
	}

	// zwraca k¹t, który tworz¹ wektory
	const float inline angle(const CVector3& normal) const 
   {
		return acos(*this % normal);
	}

	// tworzy odbicie wektora wzglêdem powierzchni zdefiniowanej przez normaln¹
	const CVector3 inline reflection(const CVector3& normal) const 
   {    
		const CVector3 vec(*this | 1);     // normalizuje wektor
		return (vec - normal * 2.0 * (vec % normal)) * !*this;
	}
};
