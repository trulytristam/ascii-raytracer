#pragma once


#include <math.h>
#include <stdio.h>

#include <random>

using namespace std;


mt19937 mt_rand(time(0));





struct v3 {

	float x, y,z ;


	v3 operator + (v3 o)
	{
		return { x + o.x, y + o.y, z + o.z };
	}
	v3 operator - (v3 o)
	{
		return { x - o.x, y - o.y , z - o.z };
	}

	v3 operator * (float o)
	{
		return { x * o, y * o , z * o };
	}

	v3 operator / (float o)
	{
		return { x /o, y / o , z / o };
	}

	float mag()
	{
		return sqrt(x * x + y * y + z * z);
	}

	v3 norm()
	{
		float t = mag();

		return { x / t, y / t, z / t };
	}

	float dot(v3 o)
	{
		return x * o.x + y * o.y + z * o.z;
	}


	v3 reflect(v3 n)
	{

		v3 p = *this;


		v3 v = n * (p.dot(n));

		
		return p - v * 2;


	}

	v3 refract(v3 n, float n1, float n2)
	{
		
		v3 dir = this->norm();



		float h = dir.dot(n*-1);

		float in = acos(h);

		v3 t = dir + n * h;

		v3 tangent = t.norm();


		float out = asin(n1 * sin(in) / n2);


		v3 O = tangent *sin(out);
		v3 A = n*-1 * cos(out);


		return (A + O).norm();

	}

	
	static v3 rand(v3 n)
	{
		v3 temp;

		int a = (mt_rand()%10001) - 5000;
		int b = (mt_rand()%10001) - 5000;
		int c = (mt_rand()%10001) - 5000;


		temp.x = (float)a / 5000;
		temp.y = (float)b / 5000;
		temp.z = (float)c / 5000;



		temp = temp.norm();

		if (temp.dot(n)<0)
		{
			temp = temp * -1;
		}


		return temp;

	}


	v3 lerp(v3 o, float r)
	{
		return *this * (1 - r) + o * r;
	}



	void operator += (v3 o)
	{
		*this = *this + o;
	}
	void operator -= (v3 o)
	{
		*this = *this - o;
	}

};