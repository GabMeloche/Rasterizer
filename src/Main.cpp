#include <SDL.h>
#include <iostream>
#include <App.h>

int main(int argc, char* argv[])
{
	App* application = new App;

	application->Startup();
	return 0;
}