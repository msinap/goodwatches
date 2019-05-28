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
    //commandManager.inputCommands();

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
		server.get("/profile", new ProfileHandler("static/profile.html"));
		server.get("/home", new HomeHandler("static/home.html"));
		server.get("/film", new FilmHandler("static/film.html"));
		server.get("/filmtable.css", new ShowFile("static/filmtable.css", "text/css"));
		server.post("/addmoney", new AddMoneyHandler());
		server.get("/buy", new BuyHandler());
		server.post("/rate", new RateHandler());
		server.run();
	}catch (Server::Exception &e) {
		cerr << e.getMessage() << endl;
	}
}
