#pragma once
#include "stdafx.h"
#include "Member.h"
#include "Link.h"

class Model
{
public:
	Model(const std::string filename);
	virtual ~Model(void);
	double energy(cv::Mat& haystack, Arrangement& a);
	std::vector<std::string> members();
	Member& getMember(std::string name);
	std::vector<Link> getLinks(std::string nameA, std::string nameB);

private:
	std::vector<std::string> explode(std::string);
	std::map<std::string, int> members_map_;
	std::vector<Member*> members_;
	std::vector<std::vector<int> > links_map_;
	std::vector<Link*> links_;
};
