#include "utility.h"
#include "CommandManager.h"
#include "MyServer.h"

int main(int argc, char **argv) {
    CommandManager commandManager;
    // commandManager.inputCommands();

	try {
		MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
        server.setNotFoundErrPage("static/404.html");
		server.run();
	} catch (Server::Exception e) {
		cerr << e.getMessage() << endl;
	}
}
