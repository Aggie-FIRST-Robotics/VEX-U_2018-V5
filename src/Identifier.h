#include <string>

class Identifier {
	public:
		Identifier(std::string id);
		std::string getID();
	private:
		std::string identifier;
};