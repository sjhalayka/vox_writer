#include "VoxWriter.h"

//https://github.com/aiekick/MagicaVoxel_File_Writer
// example from @unphased on this topic : https://github.com/aiekick/MagicaVoxel_File_Writer/issues/2

// https://github.com/jpaver/opengametools

#include <iostream>
using namespace std;

vox::VoxWriter v;
const int image_size = 8;

std::vector<unsigned char> pixels(image_size* image_size, 0);




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





int main()
{
	int red_index = 1, gray_index = 2;

	v.AddColor(192, 192, 192, 255, red_index);
	v.AddColor(64, 64, 64, 255, gray_index);



	for (size_t i = 0; i < image_size; i++)
	{
		for (size_t j = 0; j < image_size; j++)
		{
			size_t index = j * image_size + i;

			float height = sqrt(i * i + j * j) * 1;

			if (height < 1)
				height = 1;

			for (int h = 0; h < height; h++)
			{
				if (i % 2 == 0)
				{
					if (j % 2 == 0)
						v.AddVoxel(i, j, h, gray_index);
					else
						v.AddVoxel(i, j, h, red_index);
				}
				else
				{
					if (j % 2 != 0)
						v.AddVoxel(i, j, h, gray_index);
					else
						v.AddVoxel(i, j, h, red_index);
				}
			}
		}
	}

	v.SaveToFile("output_voxwriter.vox");
}