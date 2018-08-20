#include <iostream>
#include <memory>
#include <boost/format.hpp>
#include "Source.h"
#include "CurlWrapper.h"
#include <curl/curl.h>
#include <sstream>
#include <iterator>

int main() {
	const std::vector<Source> sources = {
	 Source("AP English", "https://afs-prod.appspot.com/api/v2/feed/tag?tags=%s", "en", {
		{"apf-usnews",        "national"},
		{"apf-intlnews",      "world"},
		{"apf-sports",        "sports"},
		{"apf-entertainment", "entertainment"},
		{"apf-business",      "business"},
		{"apf-science",       "science"},
		{"apf-Health",        "science"},
		{"apf-technology",    "technology"},
		{"apf-oddities",      "oddities"}
	 }, [](const std::string &articleData,
				 const Source *const source) { // Article Parser, takes the article page and returns an ArticleData instance for it
		// TODO: Parse
		Logger().info << "Parsing article: " << articleData << std::endl;
		return ArticleData(0, 0, articleData, articleData, nullptr, "", "", "", source->name);
	 	//return std::nullopt;
	 }, [](const std::string &category, const std::string &categoryData,
				 const Source *const source) {
	  // Category Paarser, takes the category page (url % category key) and returns strings of articles to parse with the Article Parser

		// TODO: Parse

		// Debug parser
		std::vector<std::string> articles;
		auto inserter = std::back_inserter(articles);
		std::stringstream ss(categoryData);
		std::string item;
		while (std::getline(ss, item, '\n'))
			*(inserter++) = item;
		return articles;
	 })
	};

	std::vector<std::thread> threads;

	curl_global_init(CURL_GLOBAL_ALL);

	std::vector<ArticleData> articles;
	std::mutex articlesMutex;

	// Start thread for each source
	for (const Source &source : sources)
	threads.emplace_back(std::thread([&]() {
		std::vector<ArticleData> sourceArticles = source.parse();
		articlesMutex.lock();
		articles.reserve(sourceArticles.size());
		articles.insert(articles.end(), sourceArticles.begin(), sourceArticles.end());
		articlesMutex.unlock();
	}));

	// Wait for threads before exiting main thread
	for (auto &thread : threads) thread.join();

	curl_global_cleanup();
}
