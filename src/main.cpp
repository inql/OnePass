#include <iostream>
#include "onepass/clientWrapper.hpp"
#include "onepass/client.hpp"
using namespace onepass::core;
using namespace onepass::storage;
using namespace onepass::client;

int main(int argc, char *argv[]){
    ClientWrapper cw(argc, argv);
    return Client::handle(cw);
}