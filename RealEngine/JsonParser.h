#pragma once

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Globals.h"
#include "Math.h"
#include "JSON/parson.h"
#include "MathGeoLib/src/MathGeoLib.h"


class JsonParser
{

public:

	JsonParser();
	JsonParser(const char* fileName);
	~JsonParser();

	uint saveToJson() const;

private:
	JSON_Value* valueRoot;
	JSON_Object* root;
	JSON_Array* json_array;

};

#endif //__CONFIG_H__