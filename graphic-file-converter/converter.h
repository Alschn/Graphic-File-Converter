#include "Image.h"


class Converter
{
protected:
	const Image *oldImage;
	Image *newImage;

public:
	virtual void processImage(int angle) = 0;
	// virtual void reflectImage(std::string reflect_by) = 0;
	void saveImage(const std::string &path) const;
	explicit Converter(const Image *base_image) : oldImage(base_image)
	{
		newImage = new Image(*base_image);
	};
};

