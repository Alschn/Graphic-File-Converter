#include "Image.h"
#include <vector>

class Converter
{
protected:
	const Image &oldImage;
	Image *newImage;

public:
	virtual void ProccessImage(const vector<int> parameters);
	void SaveImage();
	Converter(const Image &base_image) : oldImage(base_image)
	{
		newImage = new Image(base_image);
	};
};

