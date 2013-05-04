# Compile command
Compile_command = @g++ -Wall -Werror -O2 -pthread -lpthread Library/*.cpp

# Editable enviroment
Service_register_server_address		:= "127.0.0.1"
Service_register_server_port		:= "12222"
Image_manipulation_server_port		:= "23457"
Image_storage_server_port			:= "34568"
Client_iteretions					:= "3"

# Setting up enviroment
Image_manipulation_server_command 	:= "Image_manipulation_server ${Image_manipulation_server_port} ${Service_register_server_address} ${Service_register_server_port}"
Image_storage_server_command 		:= "Image_storage_server ${Image_storage_server_port} ${Service_register_server_address} ${Service_register_server_port}"
Service_register_server_command 	:= "Service_register_server ${Service_register_server_port}"
Client_command						:= "Client ${Client_iteretions} ${Service_register_server_address} ${Service_register_server_port}"

# Setting up Xterm enviroment
XtermCommand = @xterm -hold -leftbar -geometry

Service_oriented_architecture:
	@clear
	@echo "Service Oriented Architecture"
	@echo ""
	@make -s Compile
	@make -s Make_directories
	@make -s Execute
	@echo ""

Erase:
	@echo "Removing previus build results"
	@echo ""
	@rm -f Image_manipulation_server Image_storage_server Service_register_server Client

Compile:
	@echo "Compiling sources"
	@make Service_register_server Image_manipulation_server Image_storage_server Client
	@echo "Compiling process complete."
	@echo ""

Service_register_server: Library/*.cpp Service_register/*.cpp Service_register_server.cpp
	@echo "   Compiling Service Register"
	${Compile_command} Service_register_server.cpp Service_register/*.cpp -o Service_register_server

Image_manipulation_server: Library/*.cpp Image_manipulation/*.cpp Image_manipulation_server.cpp
	@echo "   Compiling Image Manipulation Server"
	${Compile_command} Image_manipulation_server.cpp Image_manipulation/*.cpp -o Image_manipulation_server

Image_storage_server: Library/*.cpp Image_storage/*.cpp Image_storage_server.cpp
	@echo "   Compiling Image Storage Server"
	${Compile_command} Image_storage_server.cpp Image_storage/*.cpp -o Image_storage_server

Client: Library/*.cpp Client.cpp
	@echo "   Compiling Client"
	${Compile_command} Client.cpp Clients/*.cpp -o Client

Make_directories:
	@mkdir -p Images
	@mkdir -p Files/Clients
	@mkdir -p Files/Servers/Image_manipulation_server
	@mkdir -p Files/Servers/Image_storage_server

Execute: Image_manipulation_server Image_storage_server Service_register_server Client
	@echo "\033[1;34mExecuting application\033[0m"
	@xterm -e "echo Pre-fetching xterm"
	@echo "Launching Service Register"
	${XtermCommand} 75x45+0+0 -e "./${Service_register_server_command}" & sleep 0.5
	@echo "Launching Image Manipulation Server"
	${XtermCommand} 75x45+525+0 -e "./${Image_manipulation_server_command}" & sleep 0.5
	@echo "Launching Image Storage Server"
	${XtermCommand} 75x45+988+0 -e "./${Image_storage_server_command}" & sleep 2
	@echo "Launching Clients"
	${XtermCommand} 75x30+1500+220 -e "./${Client_command}" & sleep 0.2
	${XtermCommand} 75x30+0+1500 -e "./${Client_command}" & sleep 0.2
	${XtermCommand} 75x30+525+1500 -e "./${Client_command}" & sleep 0.2
	${XtermCommand} 75x30+988+1500 -e "./${Client_command}" & sleep 0.2
	${XtermCommand} 75x30+1500+1500 -e "./${Client_command}" & sleep 0.2