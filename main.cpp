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


	if (red)
	{
		x_start += 64/8;
		x_end += 64 / 8;
		y_start += 64 / 8;
		y_end += 64 / 8;
	}

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





	for (size_t i = 0; i < image_size; i++)
	{
		for (size_t j = 0; j < image_size; j++)
		{
			for (size_t k = 0; k < image_size; k++)
			{
				size_t index = k * image_size * image_size + j * image_size + i;

				if (pixels[index] == 1)
				{
					//std::cout << "red pixel" << endl;
					v.AddVoxel(i, j, heights[index], gray_index);
				}
				else if (pixels[index] == 2)
				{
					v.AddVoxel(i, j, heights[index], 127);
				}
				else
				{
					//cout << "gray pixel" << endl;
					//v.AddVoxel(i, j, k, 127);
				}
			}
		}
	}

	v.SaveToFile("output_voxwriter.vox");
}