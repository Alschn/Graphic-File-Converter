#include "Image.h"


class Converter
{
protected:
	const Image *oldImage;
	Image *newImage;

public:
	virtual void proccessImage();
	void saveImage(const std::string &path) const;
	Converter(const Image *base_image) : oldImage(base_image)
	{
		newImage = new Image(*base_image);
	};
};

