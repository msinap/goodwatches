#include "utility.h"
#include "CommandManager.h"
#include "UserRepository.h"
#include "FilmRepository.h"
#include "MyServer.h"
#include "Handlers.h"

int main(int argc, char **argv) {
	FilmRepository* filmRepository = new FilmRepository();
    UserRepository* userRepository = new UserRepository(filmRepository);
	//CommandManager commandManager;
    // commandManager.inputCommands();

	try {
		MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
        server.setNotFoundErrPage("static/404.html");
		server.get("/signup", new ShowPage("static/signup.html"));
		server.post("/signup", new SignupHandler());
		server.run();
	} catch (Server::Exception e) {
		cerr << e.getMessage() << endl;
	}
}
