#include <iostream>
#include <string>

#include "access_listener.h"
#include "api.h"

using espotifai_api::AccessListener;
using espotifai_api::Api;

class EventHandler : public AccessListener {
 public:
  void OnAccessGuaranteed(const std::string &token) const override {
    std::cout << "access guaranteed, token: " << token << std::endl;
  }

  void OnAccessDenied(const std::string &msg) const override {
    std::cerr << "access denied!" << msg << std::endl;
  }
};

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "usage: " << argv[0] << " client_id client_secret"
              << std::endl;
    std::exit(1);
  }

  const std::string kClientId{argv[1]};
  const std::string kClientSecret{argv[2]};

  Api api;
  EventHandler ev;

  api.Auth(ev, kClientId, kClientSecret);

  std::exit(0);
}
