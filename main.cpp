#include "VoxWriter.h"

//https://github.com/aiekick/MagicaVoxel_File_Writer
// example from @unphased on this topic : https://github.com/aiekick/MagicaVoxel_File_Writer/issues/2

// https://github.com/jpaver/opengametools

#include <iostream>
using namespace std;

vox::VoxWriter v;
const int image_size = 64;

std::vector<unsigned char> pixels(image_size* image_size* image_size, 0);
std::vector<size_t> heights(image_size * image_size* image_size, 0);




//void rectangle(size_t x_start, size_t y_start, size_t x_end, size_t y_end, unsigned char colour_index)
//{
//	for (int i = x_start; i < x_end; i++)
//	{
//		for (int j = y_start; j < y_end; j++)
//		{
//			v.AddVoxel(i, j, 0, colour_index);
//		}
//	}
//}



void rectangle(bool red, size_t x_start, size_t y_start, size_t x_end, size_t y_end)
{
	size_t temp_height = (size_t)sqrt(x_start * x_start + y_start * y_start);

	for (int i = x_start; i < x_end; i++)
	{
		for (int j = y_start; j < y_end; j++)
		{
			size_t index = j * image_size + i;
			heights[index] = 1;// temp_height * 0.1;

			if (red)
				pixels[index] = 1;
			else
				pixels[index] = 2;
		}
	}
}


int main() 
{
	int a = image_size / 8;
 
	int red_index = 0, gray_index = 1;

	v.AddColor(255, 0, 0, 255, red_index);
	v.AddColor(127, 127, 127, 255, gray_index);


	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (i % 2 == 0)
			{
				if (j % 2 == 0)
					rectangle(false, 8 + 8 * i, 8 * i + 16, 8 + 8 * j, 8 * j + 16);
				else
					rectangle(true, 8 * i, 8 * i + 8, 8 * j, 8 * j + 8);

			}
			else
			{
				//if (j % 2 == 0)
				//	rectangle(true, 8 + 8 * i, 8 * i + 16, 8 * j, 8 * j + 16);
				//else
				//	rectangle(false, 8 * i, 8 * i + 8, 8 * j, 8 * j + 8);
			}
			//else
			//{
			//	if (j % 2 == 0)
			//		rectangle(false, 8 * i, 8 * i + 8, 8 * j, 8 * j + 8);
			//	else
			//		rectangle(true, 8 * i, 8 * i + 8, 8 * j, 8 * j + 8);
			//}
		}
	}
	/*

	for (int y = 0; y <= 3; y++)
	{
		for (int x = 0; x <= 3; x++)
		{
			rectangle(true, x * a * 2, y * a * 2, a * (2 * x + 1), a * (2 * y + 1));
		}
	}

	for (int y = 0; y <= 3; y++)
	{
		for (int x = 0; x <= 3; x++)
		{
			rectangle(true, a * (2 * x + 1), a * (2 * y + 1), (x + 1) * a * 2, (y + 1) * a * 2);
		}
	}






	for (int y = 0; y <= 3; y++)
	{
		for (int x = 0; x <= 3; x++)
		{
			rectangle(false, x * a * 2, y * a * 2, a * (2 * x + 1), a * (2 * y + 1));
		}
	}

	for (int y = 0; y <= 3; y++)
	{
		for (int x = 0; x <= 3; x++)
		{
			rectangle(false, a * (2 * x + 1), a * (2 * y + 1), (x + 1) * a * 2, (y + 1) * a * 2);
		}
	}

	*/



	for (size_t i = 0; i < image_size; i++)
	{
		for (size_t j = 0; j < image_size; j++)
		{
				size_t index = j * image_size + i;

				if (pixels[index] == 1)
				{
					//std::cout << "red pixel" << endl;
					v.AddVoxel(i, j, heights[index], gray_index);
				}
				else if (pixels[index] == 2)
				{
					v.AddVoxel(i, j, heights[index], red_index);
				}
				else
				{
					//cout << "gray pixel" << endl;
					v.AddVoxel(i, j, heights[index], 170);
				}

		}
	}

	v.SaveToFile("output_voxwriter.vox");
}