// Copyright 2010 and onwards Google Inc.
// Author: jmarantz@google.com (Joshua Marantz)

#ifndef NET_INSTAWEB_UTIL_PUBLIC_STRING_UTIL_H_
#define NET_INSTAWEB_UTIL_PUBLIC_STRING_UTIL_H_


#include <string>
#include "base/string_util.h"
#include "third_party/base64/base64.h"
#include "third_party/chromium/src/base/string_piece.h"

namespace net_instaweb {

typedef base::StringPiece StringPiece;

inline std::string IntegerToString(int i) {
  return IntToString(i);
}

inline void Web64Encode(const std::string& in, std::string* out) {
  *out = web64_encode(reinterpret_cast<const unsigned char*>(in.data()),
                      in.size());
}

inline bool Web64Decode(StringPiece in, std::string* out) {
  bool ret = web64_decode(in.as_string(), out);
  return ret;
}

const StringPiece kEmptyString;
inline std::string StrCat(const StringPiece& a,
                           const StringPiece& b,
                           const StringPiece& c = kEmptyString,
                           const StringPiece& d = kEmptyString,
                           const StringPiece& e = kEmptyString,
                           const StringPiece& f = kEmptyString) {
  std::string res;
  a.AppendToString(&res);
  b.AppendToString(&res);
  c.AppendToString(&res);
  d.AppendToString(&res);
  e.AppendToString(&res);
  f.AppendToString(&res);
  return res;
}

struct CharStarCompareInsensitive {
  bool operator()(const char* s1, const char* s2) const {
    return strcasecmp(s1, s2) < 0;
  };
};

struct CharStarCompareSensitive {
  bool operator()(const char* s1, const char* s2) const {
    return strcmp(s1, s2) < 0;
  }
};

struct StringCompareInsensitive {
  bool operator()(const std::string& s1, const std::string& s2) const {
    return strcasecmp(s1.c_str(), s2.c_str()) < 0;
  };
};

}  // namespace net_instaweb

#endif  // NET_INSTAWEB_UTIL_PUBLIC_STRING_UTIL_H_