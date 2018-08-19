//
// Created by void on 8/18/18.
//

#include "Source.h"

std::shared_ptr<std::vector<std::shared_ptr<ArticleData>>> Source::parse() const {
 std::vector<std::thread> threads;

 for (auto& category : categories)
	threads.emplace_back(std::thread([&] () {
	 std::cout << "Downloading " << category.first << "..." << std::endl;

	 std::string categoryData;
	 CURLcode result = CurlWrapper::get((boost::format(url) % category.first).str().c_str(), &categoryData);
	 if (!result) {
		std::cout << "Finished downloading " << category.first << "! " << categoryData.length() << std::endl;
	  categoryParser(category.first, categoryData, this); // Parse category site data per source
	 } else {
		std::cerr << "Error requesting category " << category.second << " for " << name << ": " << curl_easy_strerror(result) << std::endl;
	 }
	}));

 for (auto& thread : threads)
  thread.join();
}
