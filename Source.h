//
// Created by void on 8/16/18.
//

#ifndef FILE_MAKER_SOURCE_H
#define FILE_MAKER_SOURCE_H

#include <boost/format.hpp>
#include "ArticleData.h"
#include "CurlWrapper.h"
#include <functional>
#include "NewsData.h"
#include <iostream>
#include <utility>
#include <memory>
#include <string>
#include <thread>
#include <map>

class Source final {
public:
 // ArticleParser takes the data of an articles page, parses it and returns ArticleData
 // Don't worry about Source* being null, it can only be called from inside an instance
 typedef std::function<std::shared_ptr<ArticleData>(const std::string& articleData, const Source* const)> ArticleParser;
 // Parser ran for each category, threaded
 typedef std::function<std::shared_ptr<std::vector<std::shared_ptr<ArticleData>>>
   (const std::string& category, const std::string& categoryData, const Source* const)> CategoryParser;
 typedef std::vector<std::pair<std::string, std::string>> Categories;
 const ArticleParser articleParser;
 const CategoryParser categoryParser;
public:
 // Various information about the source
 const std::string name, language, url;
 const Categories categories;

 explicit Source(std::string&& name, std::string&& url, std::string&& language, Categories&& categories,
 	ArticleParser&& articleParser, CategoryParser&& categoryParser):
 		name(std::move(name)), language(std::move(language)), url(std::move(url)), categories(std::move(categories)),
 			articleParser(std::move(articleParser)), categoryParser(std::move(categoryParser)) {}
 //

 std::shared_ptr<std::vector<std::shared_ptr<ArticleData>>> parse() const;
};

#endif //FILE_MAKER_SOURCE_H
