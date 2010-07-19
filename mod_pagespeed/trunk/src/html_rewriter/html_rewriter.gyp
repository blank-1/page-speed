# Copyright 2010 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

{
 'variables': {
    # chromium_code indicates that the code is not
    # third-party code and should be subjected to strict compiler
    # warnings/errors in order to catch programming mistakes.
    'chromium_code': 1,
    'instaweb_root':  '<(DEPTH)/third_party/instaweb/src/net/instaweb',
  },

  'targets': [
    {
      'target_name': 'html_rewriter',
      'type': '<(library)',
      'dependencies': [
        '<(DEPTH)/base/base.gyp:base',
        '<(DEPTH)/third_party/apache/httpd/httpd.gyp:include',
        '<(DEPTH)/third_party/serf/serf.gyp:serf',
        '<(instaweb_root)/instaweb.gyp:instaweb_htmlparse',
        '<(instaweb_root)/instaweb.gyp:instaweb_rewriter',
        '<(instaweb_root)/instaweb.gyp:instaweb_util',
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        '<(DEPTH)/html_rewriter/apache_rewrite_driver_factory.cc',
        '<(DEPTH)/html_rewriter/apr_file_system.cc',
        '<(DEPTH)/html_rewriter/apr_mutex.cc',
        '<(DEPTH)/html_rewriter/apr_timer.cc',
        '<(DEPTH)/html_rewriter/html_parser_message_handler.cc',
        '<(DEPTH)/html_rewriter/html_rewriter.cc',
        '<(DEPTH)/html_rewriter/html_rewriter_config.cc',
        '<(DEPTH)/html_rewriter/html_rewriter_imp.cc',
        '<(DEPTH)/html_rewriter/md5_hasher.cc',
        '<(DEPTH)/html_rewriter/pagespeed_server_context.cc',
        '<(DEPTH)/html_rewriter/serf_url_async_fetcher.cc',
        '<(DEPTH)/html_rewriter/serf_url_fetcher.cc',
      ],
      'export_dependent_settings': [
        '<(instaweb_root)/instaweb.gyp:instaweb_util',
      ],
    },
    {
      'target_name': 'apr_file_system_test',
      'type': 'executable',
      'dependencies': [
        'html_rewriter',
        '<(DEPTH)/base/base.gyp:base',
        '<(DEPTH)/testing/gtest.gyp:gtest',
        '<(DEPTH)/testing/gtest.gyp:gtestmain',
        '<(DEPTH)/third_party/apache/apr/apr.gyp:apr',
        '<(DEPTH)/third_party/apache/aprutil/aprutil.gyp:aprutil',
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        '<(DEPTH)/html_rewriter/apr_file_system_test.cc',
      ],
    },
    {
      'target_name': 'serf_url_async_fetcher_test',
      'type': 'executable',
      'dependencies': [
        'html_rewriter',
        '<(DEPTH)/base/base.gyp:base',
        '<(DEPTH)/testing/gtest.gyp:gtest',
        '<(DEPTH)/testing/gtest.gyp:gtestmain',
        '<(DEPTH)/third_party/apache/apr/apr.gyp:apr',
        '<(DEPTH)/third_party/apache/aprutil/aprutil.gyp:aprutil',
        '<(DEPTH)/third_party/serf/serf.gyp:serf',
        '<(instaweb_root)/instaweb.gyp:instaweb_util',
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
      'sources': [
        '<(DEPTH)/html_rewriter/serf_url_async_fetcher_test.cc',
      ],
    },
  ],
}
