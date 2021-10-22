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

	root = nullptr;
	if (valueRoot != nullptr) {
		valueRoot = nullptr;
	}
}

uint JsonParser::saveToJson() {
	return uint();
}

uint JsonParser::saveToJson(char** buf)
{
	uint size = json_serialization_size_pretty(valueRoot);
	*buf = new char[size];
	json_serialize_to_buffer_pretty(valueRoot, *buf, size);
	return size;
}

int JsonParser::GetInt(const char* name, int default)
{
	if (json_object_has_value(root, name) == 1) {
		return json_object_get_number(root, name);
	}
	else {
		return default;
	}
}

float JsonParser::GetFloat(const char* name, float default)
{
	if (json_object_has_value(root, name) == 1) {
		return json_object_get_number(root, name);
	}
	else {
		return default;
	}
}

bool JsonParser::GetBool(const char* name, bool default)
{
	if (json_object_has_value(root, name) == 1) {
		return json_object_get_boolean(root, name);
	}
	else {
		return default;
	}
}

const char* JsonParser::GetString(const char* name, const char* default)
{
	if (json_object_has_value(root, name) == 1) {
		return json_object_get_string(root, name);
	}
	else {
		return default;
	}
}

JSON_Array* JsonParser::GetArray(const char* name)
{
	if (json_object_has_value(root, name) == 1) {
		return json_object_get_array(root, name);
	}
	else {
		return nullptr;
	}
}

void JsonParser::AddInt(const char* name, int number)
{
	json_object_set_number(root, name, number);
}

void JsonParser::AddFloat(const char* name, float number)
{
	json_object_set_number(root, name, number);
}

void JsonParser::AddBool(const char* name, bool boolean)
{
	json_object_set_boolean(root, name, boolean);
}

void JsonParser::AddString(const char* name, const char* string)
{
	json_object_set_string(root, name, string);
}