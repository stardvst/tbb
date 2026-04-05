#include "../image-fractal.h"
#include <iostream>
#include <tbb/tbb.h>
#include <vector>

void myfuncG(const std::vector<ImagePtr> &image_vector)
{
	const double tint_array[] = {0.75, 0, 0};
	for (ImagePtr img : image_vector)
	{
		img = applyGamma(img, 1.4);
		img = applyTint(img, tint_array);
		writeImage(img);
	}
}

int main(int argc, char *argv[])
{
	{
		std::vector<ImagePtr> image_vector;

		for (int i = 2000; i < 20000000; i *= 10)
			image_vector.push_back(makeFractalImage(i));

		tbb::tick_count t0 = tbb::tick_count::now();
		myfuncG(image_vector);
		std::cout << "Time : " << (tbb::tick_count::now() - t0).seconds() << " seconds" << std::endl;
	}
	return 0;
}
