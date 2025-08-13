#pragma once

#include <etl/string.h>

namespace linebot
{

constexpr static size_t INFO_STRING_LENGTH = 128;

using info_string = etl::string<INFO_STRING_LENGTH>;

}
