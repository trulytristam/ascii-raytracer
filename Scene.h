#pragma once
#include "vector.h"
#include "Object.h"
#include <vector>
#include <Windows.h>

using namespace std;


struct Scene {
	
	int W, H;
	vector<Obj> objects;

	v3 camP = { 0,0,0 };



	float* pixelBuff;
	float nSamples = 0;


	Scene(int w, int h)
	{

		pixelBuff = new float[w * h];
		W = w;
		H = h;
		for (int i = 0; i < w * h; i++)
		{
			pixelBuff[i] = 0;
		}

	}

	bool GetClosest(v3 start, v3 dir, collision& col, int bounce)
	{
		float minDist = INFINITY;
		collision minCol;
		for (auto& o : objects)
		{
			collision temp;

			if (o.rayIntersects(start, dir, temp))
			{

				if (o.type == 0 || o.type ==2 || (o.type == 1 && bounce != 0))
				{

					if (temp.dist < minDist)
					{
						minDist = temp.dist;
						minCol = temp;
					}
				}
				
				
							

			}

		}


		if (minDist == INFINITY)
		{
			return false;
		}

		col = minCol;
		
		return true;

	}

	void Clear()
	{
		for (int i = 0; i < W * H; i++)
		{
			pixelBuff[i] = 0;
		}
		nSamples = 0;
	}



	float getColor(v3 start, v3 dir)
	{
		
		v3 currentStart = start;
		v3 currentDir = dir;
		float rayColor = 1;

		float totalDist = 0;
		int bounce = 0;
		while (totalDist< 400 && bounce < 6)
		{
			collision col;
			

			if (GetClosest(currentStart, currentDir, col, bounce))
			{

				// rayhit object
				rayColor = col.o->color * rayColor;
				totalDist += col.dist;
			

				if (col.o->type == 1)
				{
					
					return rayColor;

				}

				if (col.o->refract)// && rand()% 1000 > 100)
				{
					float n1 = 1;
					float n2 = 2.0;
					v3 N = col.normal;
					if (N.dot(currentDir) > 0)
					{
						N = N * -1;
						float temp = n1;
						n1 = n2;
						n2 = temp;
					}
					currentDir = currentDir.refract(N, n1, n2);
					currentStart = col.hitpoint + N * -0.1;
				}
				else
				{
					v3 spec = currentDir.reflect(col.normal);
					v3 diff = v3::rand(col.normal);

					currentDir = spec.lerp(diff, col.o->roughness).norm();
					currentStart = col.hitpoint + col.normal * 0.01;
				}

				
				bounce += 1;
			}
			else
			{
				break;
			}
		}


		return 0;

	}


	void NextSample()
	{

		for (float x = 0; x < W; x++)
		{
			for (float y = 0; y < H; y++)
			{
				float mx = 0.5 - (x / (float)W) ;
				float my = 0.5 - (y / (float)H) ;


				v3 dir = { mx, my, 0.8 };
				dir = dir.norm();

				float col = getColor(camP, dir);
				

				pixelBuff[(int)y * W + (int)x] = pixelBuff[(int)y * W + (int)x] + col;
				
			
			}
		}

		nSamples += 1;
	}


	void AddSphere(v3 p, float r, float c, float ro = 0.4, bool refract = 0)
	{

		Obj temp;

		temp.color = c;
		temp.p = p;
		temp.r = r;
		temp.roughness = ro;
		temp.type = 0;

		temp.refract = refract;

		objects.push_back(temp);

	}


	void AddLight(v3 p, float r)
	{

		Obj temp;

		temp.color = 3;
		temp.p = p;
		temp.r = r;
		temp.roughness = 0.4;
		temp.type = 1;

		objects.push_back(temp);

	}
	void AddPlane(v3 p, v3 n, float c)
	{
		Obj temp;

		temp.color = c;
		temp.p = p;
		temp.n = n;
		temp.roughness = 0.8;
		temp.type = 2;

		objects.push_back(temp);
	}


	wchar_t get(int x)
	{


		float t = pixelBuff[x] / nSamples;

		t = min(1, t);
		t = max(0, t);
		cout << t << endl;

		wchar_t arr[20] = {
		' ', '.' ,'.' ,'.' ,'-',
		'-', '+' ,'+' ,'=' ,'=',
		'/', '/' ,'O' ,'O' ,'0',
		'#', '#' ,'@' ,'%' ,'%'
		};


		//cout << t << endl;
		int idx = (int)(t * 19);

		idx = min(idx, 19);
		idx = max(0, idx);

		//cout << idx << endl;
		//cout << "WTF" << endl;
		//cout << idx << endl;
		
		return arr[idx];
	}







};


