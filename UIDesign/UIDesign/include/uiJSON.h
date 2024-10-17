#pragma once

#include "uiPrerequisites.h"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

using JSONDocument = rapidjson::Document;
using JSONValue = rapidjson::Value;

template<typename T>
using JSONWriter = rapidjson::Writer<T>;

using JSONFileReader = rapidjson::FileReadStream;

using JSONFileWriter = rapidjson::FileWriteStream;

using JSONIStream = rapidjson::IStreamWrapper;

using JSONOStream = rapidjson::OStreamWrapper;
