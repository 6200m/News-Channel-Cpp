//
// Created by void on 8/16/18.
//

#ifndef FILE_MAKER_SOURCE_H
#define FILE_MAKER_SOURCE_H

#include "ArticleData.h"
#include "CurlWrapper.h"
#include "Logger.h"
#include <boost/format.hpp>
#include <functional>
#include <iostream>
#include <utility>
#include <memory>
#include <thread>
#include <string>
#include <mutex>
#include <map>

class Source final {
public:
 // ArticleParser takes the data of an articles page, parses it and returns ArticleData
 // Don't worry about Source* being null, it can only be called from inside an instance
 typedef std::function<std::optional<ArticleData>(const std::string &articleData, const Source *const)> ArticleParser;
 // Parser ran for each category, threaded
 typedef std::function<std::optional<std::vector<std::string>>
	(const std::string &category, const std::string &categoryData, const Source *const)> CategoryParser;
 typedef std::vector<std::pair<std::string, std::string>> FeedCategories;
 ArticleParser articleParser;
 CategoryParser categoryParser;
public:
 // Various information about the source
 std::string name, language, url;
 FeedCategories feedCategories;

 explicit Source(std::string &&name, std::string &&url, std::string &&language, FeedCategories &&feedCategories,
								 ArticleParser &&articleParser, CategoryParser &&categoryParser) :
	name(std::move(name)), language(std::move(language)), url(std::move(url)), feedCategories(std::move(feedCategories)),
	articleParser(std::move(articleParser)), categoryParser(std::move(categoryParser)) {}
 //

 std::vector<ArticleData> parse() const;
};

#endif //FILE_MAKER_SOURCE_H
