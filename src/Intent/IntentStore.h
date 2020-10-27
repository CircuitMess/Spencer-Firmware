#ifndef SPENCER_INTENTSTORE_H
#define SPENCER_INTENTSTORE_H


#include <map>
#include "Intent.hpp"

class IntentStore {
public:
	static const IntentInfo* findIntent(const char* intent);

private:
	static std::map<const char*, IntentInfo> storage;

	friend class IntentStoreFiller;
	class IntentStoreFiller {
		IntentStoreFiller();
	};

};


#endif //SPENCER_INTENTSTORE_H
