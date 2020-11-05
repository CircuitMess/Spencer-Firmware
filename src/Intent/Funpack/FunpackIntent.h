#ifndef SPENCER_FUNPACKINTENT_H
#define SPENCER_FUNPACKINTENT_H

#include "../Intent.hpp"

#define SIZEOF_ARR(arr) (sizeof(arr) / sizeof(arr[0]))
#define FUNPACK(arr) FunpackIntent(arr, SIZEOF_ARR(arr))

class FunpackIntent : public Intent {
public:
	void loop(uint micros) override;

protected:
	FunpackIntent(const char* responses[], uint8_t noResponses);
};


#endif //SPENCER_FUNPACKINTENT_H
