#ifndef SPENCER_INTENTSTORE_H
#define SPENCER_INTENTSTORE_H


#include <map>
#include "Intent.hpp"

class IntentStore {
public:
	static const IntentInfo* findIntent(const char* intent);

	static void fillStorage();

private:
	struct CStrCompare {
		bool operator()(char const* a, char const* b) const{
			return strcmp(a, b) < 0;
		}
	};

	static std::map<const char*, IntentInfo, CStrCompare> storage;

};


#endif //SPENCER_INTENTSTORE_H
