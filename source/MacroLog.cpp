﻿#include "app.h"

int main()
{
	app::init();
	while (app::is_running)
	{
		app::run();
	}

	return 0;
}


