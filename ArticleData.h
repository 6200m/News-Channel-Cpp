//
// Created by void on 8/18/18.
//

#ifndef FILE_MAKER_ARTICLEDATA_H
#define FILE_MAKER_ARTICLEDATA_H

#include <string>

class ArticleData final {
public:
 // TODO: Make some of these optional
 uint32_t updatedTime,
	updatedTime2; // wat
 std::string article, headline;
 char *pictureData;
 std::string credits, caption, location, source;

 explicit ArticleData(const uint32_t updatedTime, const uint32_t updatedTime2, std::string article,
											std::string headline, char *pictureData, std::string credits,
											std::string caption, std::string location, std::string source)
	: updatedTime(updatedTime), updatedTime2(updatedTime2), article(std::move(article)),
		headline(std::move(headline)), pictureData(pictureData), credits(std::move(credits)), caption(std::move(caption)),
		location(std::move(location)), source(std::move(source)) {}
		//
};


#endif //FILE_MAKER_ARTICLEDATA_H
