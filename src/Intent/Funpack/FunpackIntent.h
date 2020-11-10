#ifndef SPENCER_FUNPACKINTENT_H
#define SPENCER_FUNPACKINTENT_H

#include "../Intent.hpp"

class FunpackIntent : public Intent {
public:
	void loop(uint micros) override;

protected:
	FunpackIntent(const char* responses[], uint8_t noResponses);
};


#endif //SPENCER_FUNPACKINTENT_H