#include <unistd.h>
#include <thread>

#include "NetworkManager.h"

int main() {
    std::thread serverThread(runServer);

    sleep(1);

    // main

    serverThread.detach();
    return 0;
}

