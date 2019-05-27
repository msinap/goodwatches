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
		server.get("/", new StartHandler());
		server.get("/signup", new ShowPage("static/signup.html"));
		server.post("/signup", new SignupHandler());
		server.get("/login", new ShowPage("static/login.html"));
		server.post("/login", new LoginHandler());
		server.get("/logout", new LogoutHandler());
		server.get("/addfilm", new ShowPage("static/addfilm.html"));
		server.post("/addfilm", new AddFilmHandler());
		server.run();
	}catch (Server::Exception &e) {
		cerr << e.getMessage() << endl;
	}
}
