#pragma once

#include "uiPrerequisites.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

using JSONDocument = rapidjson::Document;
using JSONValue = rapidjson::Value;

template<typename T>
using JSONWriter = rapidjson::Writer<T>;

using JSONFileReader = rapidjson::FileReadStream;

using JSONFileWriter = rapidjson::FileWriteStream;
