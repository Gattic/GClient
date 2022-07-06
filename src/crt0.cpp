// Copyright 2020 Robert Carneiro, Derek Meer, Matthew Tabak, Eric Lujan
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and
// associated documentation files (the "Software"), to deal in the Software
// without restriction,
// including without limitation the rights to use, copy, modify, merge, publish,
// distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom
// the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include "crt0.h"
#include "Backend/Database/GList.h"
#include "Backend/Networking/main.h"
#include "Backend/Networking/service.h"
#include "Backend/Networking/socket.h"
#include "core/error.h"
#include "core/md5.h"
#include "core/version.h"
#include "main.h"

bool GClient::running = true;
Version* GClient::version = new Version("0.57");

/*!

*/
bool GClient::getRunning()
{
	return running;
}

Version GClient::getVersion()
{
	return *version;
}

void GClient::stop()
{
	running = false;
}

int main(int argc, char* argv[])
{
	// version & header
	printf("%s\n", GClient::getVersion().header().c_str());

	// For random numbers
	srand(time(NULL));

	GNet::GServer* serverInstance = new GNet::GServer();

	// command line args
	bool localOnly = false;
	for (int i = 1; i < argc; ++i)
	{
		printf("Ingesting program paramter [%d]: %s\n", i, argv[i]);
		localOnly = (strcmp(argv[i], "local") == 0);
	}

	// Launch the server server
	serverInstance->run(localOnly);

	// Launch the gui
	RequestListener::run(serverInstance);

	// Cleanup GNet
	serverInstance->stop();

	return EXIT_SUCCESS;
}
