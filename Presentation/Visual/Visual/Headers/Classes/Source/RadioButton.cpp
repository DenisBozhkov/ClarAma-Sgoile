#include "../Headers/RadioButton.h"
Visual::RadioButton::RadioButton()
	:Checkbox()
	{ style=WS_TABSTOP|BS_NOTIFY|BS_AUTORADIOBUTTON; }