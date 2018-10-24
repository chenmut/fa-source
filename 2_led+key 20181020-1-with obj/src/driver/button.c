#include "button.h"

int getButtonStatus(const int button)
{
	return digitalRead ( button );
}