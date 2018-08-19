#include <iostream>
#include <memory>
#include <boost/format.hpp>
#include "Source.h"
#include "CurlWrapper.h"
#include <curl/curl.h>

int main() {
 const std::vector<Source> sources = {
         Source("AP English", "https://afs-prod.appspot.com/api/v2/feed/tag?tags=%s", "en", {
           {"apf-usnews", "national"},
           {"apf-intlnews", "world"},
           {"apf-sports", "sports"},
           {"apf-entertainment", "entertainment"},
           {"apf-business", "business"},
           {"apf-science", "science"},
           {"apf-Health", "science"},
           {"apf-technology", "technology"},
           {"apf-oddities", "oddities"}
         }, [] (const std::string& articleData, const Source* const source) { // Article Parser, takes the article url and gets ArticleData for it
          // TODO: Parse
					return nullptr;
				 }, [] (const std::string& category, const std::string& categoryData, const Source* const source) { // Category parser, ran once, responsible for parsing categories and handing articles for each category off to the ArticleParser
          // TODO: Parse
          return nullptr;
         })
 };

 std::vector<std::thread> threads;

 curl_global_init(CURL_GLOBAL_ALL);

 // Start thread for each source
 for (const Source& source : sources) threads.emplace_back(std::thread(&Source::parse, source/*, std::ref(threads)*/));

 // Wait for threads before exiting main thread
 for (auto& thread : threads) thread.join();

 curl_global_cleanup();
}
