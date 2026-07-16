#include <iostream>
#include <nlohmann/json.hpp>

#include "Server.hpp"


int main() {
    auto server = std::make_unique<Server>();
    server->run();
}
