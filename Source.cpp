//
// Created by void on 8/18/18.
//

#include "Source.h"

std::vector<ArticleData> Source::parse() const {
	std::vector<std::thread> threads;
	std::vector<ArticleData> articles;
	std::mutex threadsLock, articlesLock;

	for (auto &category : feedCategories) {
	 threadsLock.lock();
	 threads.emplace_back(std::thread([&]() {
		std::string categoryData;
		Logger().info << "Downloading " << category.first << "..." << std::endl;
		//CURLcode result = CurlWrapper::get((boost::format(url) % category.first).str().c_str(), &categoryData);
		// Debug "data"
		CURLcode result = CURLE_OK;
		categoryData = "This is the first example article\nThis is the second example article\nThis is the third example article";

		if (!result) {
		 Logger().info << "Finished downloading " << category.second << "! " << categoryData.length() << std::endl;
		 auto categoryFeed = categoryParser(category.first, categoryData, this); // Parse category site data per source
		 if (categoryFeed) {
			for (auto &articleData : *categoryFeed) {
			 //std::lock_guard<std::mutex> articleParsingThreadLockGuard(threadsLock);
			 //threads.emplace_back(std::thread([&]() { // Start thread per article parsing, probably overkill
				auto article = articleParser(articleData, this);
				if (article) {
				 std::lock_guard<std::mutex> articlesLockGuard(articlesLock);
				 articles.emplace_back(article.value());
				}
			 //}));
			}
		 }
		} else {
		 Logger().error << "Error requesting category " << category.second << " for " << name << ": "
							 << curl_easy_strerror(result) << std::endl;
		}
	 }));
	 threadsLock.unlock();
	}

	// Wait for all threads to finish
	for (auto &thread : threads) thread.join();

	return articles;
}
