#include "Arrangement.h"
#include "Position.h"
#include "Member.h"
#include "ImageMember.h"
#include <map>
#include <fstream>
#include <sstream>
#include "debug.h"
#include "Link.h"
#include "Model.h"

using namespace std;
using namespace cv;

Model::Model(const string filename)
{
	string folder = filename.substr(0, filename.find_last_of("/\\"));

	ifstream filestream(filename.c_str());

	string line;
	while (!filestream.eof()) {
		std::getline(filestream, line);
		vector<string> chunks = explode(line);
		
		if (chunks.size() == 0) {
			break;
		}

		string linetype = chunks[0];
		transform(linetype.begin(), linetype.end(), linetype.begin(), tolower);
		if (linetype == "member") {
			/* Example:
			 * Member  Image   head    head.png 36
			 */
			Member* m;

			string membertype = chunks[1];
			transform(membertype.begin(), membertype.end(), membertype.begin(), tolower);

			string membername = chunks[2];

			/* Member Image head head.png 36
			 * becomes
			 * head.png 36
			 */
			chunks.erase(chunks.begin(), chunks.begin() + 3);
			if (membertype == "image") {
				m = new ImageMember(folder, chunks);
			}

			unsigned int insert_index = members_.size();
			members_.push_back(m);
			members_map_[membername] = insert_index;
		} else if (linetype == "link") {
			//	Link  Spring   head  trunk  77  1

			//	string nameA, nameB;
			//	string link_type;
			//	double arg0, arg1;
		} else if (linetype == "#") {
			// Comment
		} else {
			cout << linetype << " <= unrecognised syntax" << endl;
		}
	}

}

Model::~Model(void)
{
	// TODO (delete every members & links)
}

vector<string> Model::members()
{
	vector<string> members(members_map_.size());

	int i = 0;
	for (map<string, int>::iterator it = members_map_.begin(); it != members_map_.end(); ++it) {
		members[i] = it->first;
		++i;
	}
	
	return members;
}

Member& Model::getMember(std::string name)
{
	return *members_[members_map_[name]];
}

std::vector<Link> Model::getLinks(std::string nameA, std::string nameB)
{
	return std::vector<Link>();
}

vector<string> Model::explode(string s)
{
	const char spaces[] = " \t";
	vector<string> chunks;

	unsigned int start = 0;
	unsigned int end = s.find_first_of(spaces);

	while (true) {
		string chunk = s.substr(start, end - start);
		
		// Trim
		chunk.erase(chunk.find_last_not_of(spaces) + 1);
		chunk.erase(0, chunk.find_first_not_of(spaces));

		if (chunk.size() > 0) {
			chunks.push_back(chunk);
		}

		if (end == -1) {
			break;
		}
		start = end + 1;
		end = s.find_first_of(spaces, start);
	}

	return chunks;
}

double Model::energy(Mat& haystack, Arrangement& a)
{
	double e = 0;

	for (unsigned int i = 0; i < members_.size(); ++i) {
		e += members_[i]->energy(haystack, a[i]);
	}

	for (unsigned int i = 0; i < links_.size(); ++i) {
		Link* l = links_[i];
		e += l->energy(a[l->first_member()], a[l->second_member()]);
	}

	return e;
}