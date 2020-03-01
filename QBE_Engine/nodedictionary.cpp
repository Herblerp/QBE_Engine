#include "nodedictionary.h"
#include <string>
#include <iostream>
#include <filesystem>


using namespace std;
namespace fs = std::filesystem;

namespace Data {

	Nodedictionary::Nodedictionary()
	{
		nodeDict.push_back(Nodetype(0, 0, 0, 0));
		isLoaded = false;
	}

	//Return the nodetype with the corresponding id
	Nodetype& Nodedictionary::GetNodeType(int id) {
		if (this->isLoaded)
		{
			if (id < nodeDict.size())
				return this->nodeDict.at(id);
			throw range_error{ "Invalid nodetype id" };
		}
		throw range_error{ "Dictionary not loaded" };
	}

	//Iterate trough all qbenode files and add the types to the dictionary.
	//bool Nodedictionary::loadTypes()
	//{
	//	vector<string> fileNames;
	//	uint8_t color_r_value, color_g_value, color_b_value;
	//
	//	try {
	//
	//		std::string path = "Nodetypes";
	//
	//		for (const auto& entry : fs::directory_iterator(path))
	//			fileNames.push_back(entry.path().filename().string());
	//
	//		for (auto fileName : fileNames) {
	//
	//			uint16_t id_counter = 1;
	//
	//			INIReader reader("Nodetypes/" + fileName);
	//
	//			if (reader.ParseError() != 0) {
	//				throw runtime_error{ "Failed to parse file " + fileName + "\n" };
	//			}
	//
	//			//Load node properties here.
	//
	//			try {
	//				color_r_value = ConvertColorValue(reader.GetInteger("", "color_r_value", -1));
	//				color_g_value = ConvertColorValue(reader.GetInteger("", "color_g_value", -1));
	//				color_b_value = ConvertColorValue(reader.GetInteger("", "color_b_value", -1));
	//			}
	//			catch (exception e) {
	//
	//				//Handle invalid RGB value here.
	//
	//				throw runtime_error{"Invalid RGB value in " + fileName + "\n" };
	//			}
	//
	//			cout << "Loaded file " << fileName << "." << "\n";
	//
	//			nodeDict.push_back(Nodetype(id_counter, color_r_value, color_g_value, color_b_value));
	//			id_counter++;
	//		}
	//
	//		this->isLoaded = true;
	//		return true;
	//
	//	}
	//	catch (exception e) {
	//
	//		//Practically this should only happen when the path is incorrect. 
	//		//Everything else should be handled in this function.
	//
	//		cout << "Failed to load nodetypes: " << e.what();
	//		return false;
	//	}
	//}

	uint8_t Nodedictionary::ConvertColorValue(int value) {
		if (value > 0 || value < 255)
			return (uint8_t)value;
		throw std::invalid_argument{ "Invalid RGB value" };
	}
}