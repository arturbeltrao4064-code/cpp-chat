#include "server.hpp"
#include <iostream>

#ifdef _WIN32                // compilador condicional para Windows, se tiver win32 ele compila o código abaixo
    #define _WIN32_lean_AND_MEAN // evita que o windows.h inclua algumas bibliotecas desnecessárias
    #include <winsock2.h>
#endif

void inicializaserver()
{ // implementação da função para inicializar o servidor

#ifdef _WIN32
    WSADATA dados;
    int result = WSAStartup(MAKEWORD(2, 2), &dados);
    if (result != 0)
    {
        std::cerr << "Falha ao inicializar o Winsock. Código de erro: " << result << std::endl; // cerr é usado para exibir mensagens de erro
        return;
    }
    std::cout << "Winsock inicializado com sucesso." << std::endl;

    SOCKET servidor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (servidor == INVALID_SOCKET)
    {
        std::cerr << "Erro ao criar socket: "
                  << WSAGetLastError() << std::endl;

        WSACleanup();
        return;
    }

    std::cout << "Socket TCP criado com sucesso!" << std::endl;

    sockaddr_in endereco{};
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(54000);                  // Porta do servidor
    endereco.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Endereço de loopback (localhost)

    if (bind(servidor, (sockaddr *)&endereco, sizeof(endereco)) == SOCKET_ERROR)
    {
        std::cerr << "Erro ao vincular socket: "
                  << WSAGetLastError() << std::endl;

        closesocket(servidor);

        WSACleanup(); // Limpeza do Winsock após o uso
        return;
    }
    std::cout << "Socket associado na porta 54000!" << std::endl;

    // NOVA ETAPA: colocar o socket em estado de escuta
    if (listen(servidor, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cerr << "Erro ao colocar o servidor em escuta: "
                  << WSAGetLastError() << std::endl;

        closesocket(servidor);
        WSACleanup();
        return;
    }

    std::cout << "Servidor esperando um cliente..." << std::endl;

    SOCKET cliente = accept(servidor, nullptr, nullptr);

    if (cliente == INVALID_SOCKET)
    {
        std::cerr << "Erro ao aceitar cliente: "
                  << WSAGetLastError() << std::endl;

        closesocket(servidor);
        WSACleanup();
        return;
    }

    std::cout << "Cliente conectado com sucesso!" << std::endl;

    closesocket(cliente);
    closesocket(servidor);
    WSACleanup();
#else
    std::cout << "Linux: sistema não precisa de inicialização especial." << std::endl;
#endif
}