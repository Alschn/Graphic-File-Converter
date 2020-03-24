#include "Image.h"


class Converter
{
protected:
	const Image &oldImage;
	Image *newImage;

public:
	virtual void ProccessImage();
	void SaveImage();
	Converter(const Image &base_image) : oldImage(base_image)
	{
		newImage = new Image(base_image); //heap allocated memory
	};
};

