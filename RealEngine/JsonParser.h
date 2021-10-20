#pragma once

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Globals.h"
#include "JSON/parson.h"
//#include "Math.h"
//#include "MathGeoLib/src/MathGeoLib.h"


class JsonParser{

public:

	JsonParser();
	JsonParser(const char* fileName);
	~JsonParser();

	uint saveToJson();

private:
	JSON_Value* valueRoot;
	JSON_Object* root;
	JSON_Array* json_array;

};

#endif //__CONFIG_H__