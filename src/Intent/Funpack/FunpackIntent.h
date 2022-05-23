#ifndef SPENCER_FUNPACKINTENT_H
#define SPENCER_FUNPACKINTENT_H

#include "../Intent.hpp"

class MatrixAnimGIF;

class FunpackIntent : public Intent {
public:
	void loop(uint micros) override;
	void enter() override;
	void exit() override;

protected:
	FunpackIntent(const char* responses[], uint8_t noResponses);
	const char* filePath = nullptr;

private:
	MatrixAnimGIF* anim = nullptr;
};


#endif //SPENCER_FUNPACKINTENT_H