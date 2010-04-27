// Copyright 2010 Google Inc.
// Author: sligocki@google.com (Shawn Ligocki)
//
// UrlFetcher is an interface for asynchronously fetching urls.  The
// caller must supply a callback to be called when the fetch is complete.

#ifndef NET_INSTAWEB_UTIL_PUBLIC_URL_ASYNC_FETCHER_H_
#define NET_INSTAWEB_UTIL_PUBLIC_URL_ASYNC_FETCHER_H_

#include <string>

namespace net_instaweb {

class MessageHandler;
class MetaData;
class Writer;

class UrlAsyncFetcher {
 public:
  struct Callback {
    virtual ~Callback();
    virtual void Done(bool success) = 0;
  };

  virtual ~UrlAsyncFetcher();

  // Fetch a URL, streaming the output to fetched_content_writer, and
  // returning the headers.  request_headers is optional -- it can be NULL.
  // response_headers and fetched_content_writer must be valid until
  // the call to Done().
  //
  // This function returns false if the request is determined to be invalid
  // before asynchronous, say, because the url had invalid syntax.
  virtual void StreamingFetch(const std::string& url,
                              const MetaData& request_headers,
                              MetaData* response_headers,
                              Writer* fetched_content_writer,
                              MessageHandler* message_handler,
                              Callback* callback) = 0;
};

}  // namespace net_instaweb

#endif  // NET_INSTAWEB_UTIL_PUBLIC_URL_ASYNC_FETCHER_H_