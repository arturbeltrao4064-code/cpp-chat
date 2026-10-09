#include "cliente.hpp"
#include <iostream>

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <winsock2.h>
#endif

void inicializacliente() {

#ifdef _WIN32

    // 1. Inicializar o Winsock
    WSADATA dados;

    int resultado = WSAStartup(MAKEWORD(2, 2), &dados);

    if (resultado != 0) {
        std::cerr << "Erro ao inicializar Winsock: "
                  << resultado << std::endl;
        return;
    }

    // 2. Criar o socket do cliente
    SOCKET conexao = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (conexao == INVALID_SOCKET) {
        std::cerr << "Erro ao criar socket: "
                  << WSAGetLastError() << std::endl;

        WSACleanup();
        return;
    }

    // 3. Definir o endereço do servidor
    sockaddr_in endereco{};

    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(54000);
    endereco.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // 4. Solicitar a conexão com o servidor
    if (connect(conexao,
                reinterpret_cast<sockaddr*>(&endereco),
                sizeof(endereco)) == SOCKET_ERROR) {

        std::cerr << "Erro ao conectar: "
                  << WSAGetLastError() << std::endl;

        closesocket(conexao);
        WSACleanup();
        return;
    }

    std::cout << "Conectado ao servidor com sucesso!"
              << std::endl;

    // 5. Liberar os recursos
    closesocket(conexao);
    WSACleanup();

#else

    std::cerr << "Cliente ainda nao implementado para Linux."
              << std::endl;

#endif
}