#include "JsonParser.h"

JsonParser::JsonParser() {

	json_array = nullptr;
	rootValue = json_value_init_object();
	root = json_value_get_object(rootValue);
	wantToDelete = true;
}

JsonParser::JsonParser(const char* fileName){

	rootValue = json_parse_string(fileName);
	if (rootValue != nullptr) {
		root = json_value_get_object(rootValue);
		wantToDelete = true;
	}
}

JsonParser::~JsonParser() {

	root = nullptr;
	if (rootValue != nullptr) {
		//rootValue = nullptr;
		json_value_free(rootValue);
	}
}

uint JsonParser::saveToJson() {
	return uint();
}

uint JsonParser::saveToJson(char** buf) const
{
	uint size = json_serialization_size_pretty(rootValue);
	*buf = new char[size];
	json_serialize_to_buffer(rootValue, *buf, size);
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

uint JsonParser::GetNumElementsInArray(const char* field) const
{
	JSON_Array* array = json_object_get_array(root, field);
	if (array == nullptr) {
		return -1;
	}
	int num = json_array_get_count(array);
	return num;
}

uint JsonParser::GetUInt(const char* field, uint default, int index) const
{
	JSON_Value* value;

	if (index < 0) {
		value = json_object_get_value(root, field);
	}

	JSON_Array* array = json_object_get_array(root, field);
	if (array != nullptr) {
		value = json_array_get_value(array, index);
	}

	if (value && json_value_get_type(value) == JSONNumber) {
		return (uint)json_value_get_number(value);
	}

	return default;
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

bool JsonParser::AddArray(const char* array_name)
{
	JSON_Value* val = json_value_init_array();
	json_array = json_value_get_array(val);

	return json_object_set_value(root, array_name, val) == JSONSuccess;
}

bool JsonParser::AddArrayChild(const JsonParser& parser)
{
	if (json_array != nullptr) {
		return json_array_append_value(json_array, json_value_deep_copy(parser.rootValue)) == JSONSuccess;
	}
	return false;
}