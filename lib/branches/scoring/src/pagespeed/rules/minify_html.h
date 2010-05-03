// Copyright 2009 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef PAGESPEED_RULES_MINIFY_HTML_H_
#define PAGESPEED_RULES_MINIFY_HTML_H_

#include "base/basictypes.h"
#include "pagespeed/rules/minify_rule.h"

namespace pagespeed {

namespace rules {

/**
 * Lint rule that checks that HTML resources are minified.
 */
class MinifyHTML : public MinifyRule {
 public:
  MinifyHTML(bool save_optimized_content);

 private:
  DISALLOW_COPY_AND_ASSIGN(MinifyHTML);
};

}  // namespace rules

}  // namespace pagespeed

#endif  // PAGESPEED_RULES_MINIFY_HTML_H_
