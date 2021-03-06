# Compile command
Compile_command = @g++ `Magick++-config --cxxflags --cppflags` -Wall -Werror -O2 -lm -lpthread -pthread SOA_Library/*.cpp

# Editable enviroment
Interactive							:= "false"
Service_register_server_address		:= "127.0.0.1"
Service_register_server_port		:= "23456"
Image_manipulation_server_port		:= "34567"
Image_storage_server_port			:= "45678"
Client_iteretions					:= "100"

# Setting up enviroment
ifeq (${Interactive}, "false")
Image_manipulation_server_command 	:= "Image_manipulation_server ${Image_manipulation_server_port} ${Service_register_server_address} ${Service_register_server_port}"
Image_storage_server_command 		:= "Image_storage_server ${Image_storage_server_port} ${Service_register_server_address} ${Service_register_server_port}"
Service_register_server_command 	:= "Service_register_server ${Service_register_server_port}"
Client_command						:= "Client ${Client_iteretions} ${Service_register_server_address} ${Service_register_server_port}"
else
Image_manipulation_server_command 	:= "Image_manipulation_server"
Image_storage_server_command 		:= "Image_storage_server"
Service_register_server_command 	:= "Service_register_server"
Client_command						:= "Client"
endif

Service_oriented_architecture:
	@clear
	@echo "Service Oriented Architecture"
	@echo ""
	@make -s Compile
	@make -s Make_directories
	@echo ""

Compile:
	@echo "Compiling sources"
	@make Service_register_server Image_manipulation_server Image_storage_server Client
	@echo "   Compiling process complete."
	@echo ""

Service_register_server: SOA_Library/*.cpp Application/Service_register_server/*.h Application/Service_register_server/*.cpp Service_register_server.cpp
	@echo "   Compiling Service Register"
	${Compile_command} Service_register_server.cpp Application/Service_register_server/*.cpp -o Service_register_server

Image_manipulation_server: SOA_Library/*.cpp Application/Image_manipulation_server/*.h Application/Image_manipulation_server/*.cpp Image_manipulation_server.cpp
	@echo "   Compiling Image Manipulation Server"
	${Compile_command} Image_manipulation_server.cpp Application/Image_manipulation_server/*.cpp `Magick++-config --ldflags --libs` -o Image_manipulation_server

Image_storage_server: SOA_Library/*.cpp Application/Image_storage_server/*.h Application/Image_storage_server/*.cpp Image_storage_server.cpp
	@echo "   Compiling Image Storage Server"
	${Compile_command} Image_storage_server.cpp Application/Image_storage_server/*.cpp -o Image_storage_server

Client: SOA_Library/*.cpp Application/Clients/*.h Client.cpp
	@echo "   Compiling Client"
	${Compile_command} Client.cpp -o Client
	
Make_directories:
	@mkdir -p Images
	@mkdir -p Work_directories/Clients
	@mkdir -p Work_directories/Servers/Image_manipulation_server
	@mkdir -p Work_directories/Servers/Image_storage_server
	
Erase:
	@echo "Removing previus build results"
	@echo ""
	@rm -f Image_manipulation_server Image_storage_server Service_register_server Client
