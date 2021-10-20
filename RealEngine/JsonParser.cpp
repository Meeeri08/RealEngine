#include "JsonParser.h"

JsonParser::JsonParser() {

	json_array = nullptr;
	valueRoot = json_value_init_object();
	root = json_value_get_object(valueRoot);
}

JsonParser::JsonParser(const char* fileName){

	valueRoot = json_parse_string(fileName);
	if (valueRoot != nullptr) {
		root = json_value_get_object(valueRoot);
	}
}

JsonParser::~JsonParser() {

}

uint JsonParser::saveToJson() {
	return uint();
}
