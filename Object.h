#pragma once
#include "vector.h"
using namespace std;

struct Obj;
struct collision {

	Obj* o;

	v3 hitpoint;

	v3 normal;
	float dist;





};

struct Obj {

	v3 p;
	float r;

	v3 n;

	int type;

	float color;
	float roughness;

	bool refract = false;


	bool rayIntersects(v3 start, v3 dir, collision& col)
	{


		if (type < 2)
		{
			//sphere

			//cout << "p: " << p.x << ", " << p.y<< ", "<< p.z << endl;
			//cout << "s: " << start.x << ", " << start.y<< ", "<< start.z << endl;

			v3 L = p - start;
			float tst = L.dot(dir);

			v3 H = start + dir * tst;

			float z = (H - p).mag();

			//cout <<"z: "<<  z << endl;
			 
			if (z > r)
			{
				return false;
			}

			float f = sqrt(r * r - z * z);

			//cout << "f: " << f << endl;


			float d0 = tst - f;
			float d1 = tst + f;


			if (d1 < d0)
			{
				float temp = d0;
				d0 = d1;
				d1 = temp;
			}

			if (d0 < 0)
			{
				d0 = d1;


				if (d0 < 0)
				{
					return false;
				}

			}
			collision temp;


			temp.o = this;
			temp.hitpoint = start + dir * d0;

			temp.normal = (temp.hitpoint - p).norm();
			temp.dist = d0;

			col = temp;
			
			return true;

		}

		else if (type == 2)
		{
			//plane

			v3 v = (p - start);
			float H = v.dot(n * -1);

			if (H < 0)return false;


			float y = dir.dot(n*-1);

			if (y <= 0)return false;



			v3 t = dir + n * y;

			v3 tangent = t.norm();



			float x = dir.dot(tangent);


			float ratio = x / y;


			float length = H * ratio;


			v3 hitpoint = start + dir * length;



			collision temp;

			temp.o = this;
			temp.hitpoint = hitpoint;
			temp.normal = n;
			temp.dist = length;

			col = temp;

			return true;
		}




		return false;


	}




};
