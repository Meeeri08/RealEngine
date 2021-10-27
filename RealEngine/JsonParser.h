#pragma once

#include "Globals.h"
#include "JSON/parson.h"

class JsonParser{

public:

	JsonParser();
	JsonParser(const char* fileName);
	~JsonParser();

	uint saveToJson();
	uint saveToJson(char** file) const;

	int GetInt(const char* name, int default = -1);
	float GetFloat(const char* name, float default = -1.0f);
	bool GetBool(const char* name, bool default = false);
	const char* GetString(const char* name, const char* default);
	JSON_Array* GetArray(const char* name);
	uint GetNumElementsInArray(const char* field) const;
	uint GetUInt(const char* field, uint default = 0, int index = -1) const;

	void AddInt(const char* name, int number);
	void AddFloat(const char* name, float number);
	void AddBool(const char* name, bool boolean);
	void AddString(const char* name, const char* string);
	bool AddArray(const char* array);
	bool AddArrayChild(const JsonParser& parser);

private:
	JSON_Value* rootValue;
	JSON_Object* root;
	JSON_Array* json_array;

	bool wantToDelete;

};
