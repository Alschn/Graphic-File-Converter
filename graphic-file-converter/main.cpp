#include <iostream>

#include "image.h"

int main()
{
	Image im(R"(C:\Users\Gustaw\source\repos\graphic-file-converter\sample_bmps\10x10.bmp)", true);

	im.show();

	return 0;
}
