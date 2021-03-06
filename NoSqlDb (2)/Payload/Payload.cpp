
#include "Payload.h"

using namespace Payload;

    File::File(std::string Str)
	{
		XmlProcessing::XmlDocument XmlDoc(Str, XmlProcessing::XmlDocument::str);
		path_ = XmlDoc.descendents("path").select()[0]->children()[0]->value();
		std::vector<Sptr> Categories = XmlDoc.descendents("categories").select()[0]->children();
		for (auto pCategory : Categories)
		{
			categories_.insert(pCategory->children()[0]->value());
		}
	}

	File::operator std::string()
	{
		Sptr pPayload = XmlProcessing::makeTaggedElement("file");
		Sptr pPath = XmlProcessing::makeTaggedElement("path", path_);
		pPayload->addChild(pPath);
		Sptr pCategories = XmlProcessing::makeTaggedElement("categories");
		pPayload->addChild(pCategories);
		for (auto category : categories_) {
			Sptr pCategory = XmlProcessing::makeTaggedElement("category", category);
			pCategories->addChild(pCategory);
		}
		return pPayload->toString();
	}

	bool File::operator==(const File& f) 
	{
		if (path_ != f.path_)
			return false;
		if (categories_.size() != f.categories_.size())
			return false;
		auto it = categories_.begin();
		auto it1 = f.categories_.begin();
		while (it != categories_.end() && it1 != f.categories_.end())
		{
			if (*it != *it1)
				return false;
			it++;
			it1++;
		}
		return true;
	}

	File& File::addCategory(const Category& category) {
		categories().insert(category);
		return *this;
	}

	File& File::delCategory(const Category& category) {
		auto it = categories_.find(category);
		if (it != categories_.end())
			categories_.erase(it);
		return *this;
	}

	bool File::compare(const File p1)
	{
		std::regex e(p1.path_);
		if (!std::regex_match(path_, e))
			return false;
		
		for (auto category : p1.categories_)
		{
			auto it = categories_.find(category);
			if (it == categories_.end())
				return false;
		}
		return true;
	}

	std::ostream& Payload::operator<<(std::ostream& out, const File& f) {
		out << "Path: " << f.path() << " Categories:";
		for (auto category : f.categories()) {
			out << " " << category;
		}
		return out;
	}


#ifdef TEST_PAYLOAD

int main() {

	std::cout << "test";

	return 0;
}
#endif