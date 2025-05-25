#include <thread>
#include <unistd.h>

#include "CLManager.h"
#include "NetworkManager.h"

// int main(){
//   return 0;
// }
int main() {
    NetworkManager &networkManager = NetworkManager::getInstance();

    CLManager &clManager = CLManager::getInstance();

    std::thread serverThread(&NetworkManager::runServer, &networkManager);

    sleep(1);

    clManager.run();

    serverThread.detach();
    return 0;
}
