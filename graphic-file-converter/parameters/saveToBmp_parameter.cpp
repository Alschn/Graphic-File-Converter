//Created by Wojciech Nowicki
#include <iostream>
#include  "saveToBmp_parameter.h"
#include "../image_scanner.h"

void SaveToBmpParameter::executeParam(Converter* conversion, std::string& output_path)
{
	ImageScanner* changed_conversion = dynamic_cast<ImageScanner*>(conversion);
	changed_conversion->saveToBmp(output_path);
}
