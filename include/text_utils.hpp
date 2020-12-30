#pragma once

#include <string>
#include <tchar.h>

#ifdef UNICODE
#define TO_STR std::to_wstring
#else
#define TO_STR std::to_string
#endif

using tstring = std::basic_string<_TCHAR>;

namespace Chars {
const _TCHAR BORDER = _T('\u2592');
const _TCHAR BLOCK = _T('\u2588');
const _TCHAR SPACE = _T(' ');
} // namespace Chars
