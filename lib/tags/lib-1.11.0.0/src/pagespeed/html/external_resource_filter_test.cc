// Copyright 2010 Google Inc. All Rights Reserved.
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

#include <string>
#include <vector>

#include "net/instaweb/htmlparse/public/html_parse.h"
#include "net/instaweb/htmlparse/public/empty_html_filter.h"
#include "net/instaweb/util/public/google_message_handler.h"
#include "pagespeed/html/external_resource_filter.h"
#include "pagespeed/testing/pagespeed_test.h"

namespace {

static const char* kRootUrl = "http://www.example.com/";
static const char* kHtml =
    "<html><body>"
    "<script src='foo.js'></script>"
    "<script src='http://www.example.com/foo.js'></script>"
    "<link rel='stylesheet' href='http://www.example.com/foo.css'>"
    "</body></html>";

static const char* kHtmlNoRelNoSrc =
    "<html><body>"
    "<script></script>"
    "<script src='http://www.example.com/foo.js'></script>"
    "<link href='http://www.example.com/foo.css'>"
    "</body></html>";

class ExternalResourceFilterTest : public pagespeed_testing::PagespeedTest {
 public:
  virtual void DoSetUp() {
    NewPrimaryResource(kRootUrl);
  }
};

TEST_F(ExternalResourceFilterTest, Basic) {
  net_instaweb::GoogleMessageHandler message_handler;
  net_instaweb::HtmlParse html_parse(&message_handler);
  pagespeed::html::ExternalResourceFilter filter(&html_parse);
  html_parse.AddFilter(&filter);

  html_parse.StartParse(kRootUrl);
  html_parse.ParseText(kHtml, strlen(kHtml));
  html_parse.FinishParse();

  std::vector<std::string> external_resource_urls;
  ASSERT_TRUE(filter.GetExternalResourceUrls(&external_resource_urls,
                                             document(),
                                             kRootUrl));

  ASSERT_EQ(2U, external_resource_urls.size());
  ASSERT_EQ("http://www.example.com/foo.css", external_resource_urls[0]);
  ASSERT_EQ("http://www.example.com/foo.js", external_resource_urls[1]);
}

TEST_F(ExternalResourceFilterTest, NoRelShouldNotCrash) {
  net_instaweb::GoogleMessageHandler message_handler;
  net_instaweb::HtmlParse html_parse(&message_handler);
  pagespeed::html::ExternalResourceFilter filter(&html_parse);
  html_parse.AddFilter(&filter);

  html_parse.StartParse(kRootUrl);
  html_parse.ParseText(kHtmlNoRelNoSrc, strlen(kHtmlNoRelNoSrc));
  html_parse.FinishParse();

  std::vector<std::string> external_resource_urls;
  ASSERT_TRUE(filter.GetExternalResourceUrls(&external_resource_urls,
                                             document(),
                                             kRootUrl));
}

}  // namespace
