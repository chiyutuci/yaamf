#include "yaamf/tools.h"
#include "yaamf/yaamf.h"
#include <fstream>
#include <iostream>

using namespace std;

void check_input(int argc, char **argv) {
  fstream config("config.yaml");
  if (!config) {
    cout << "\nFailed: Can not find config.yaml\n" << endl;
    exit(-1);
  }
  if (argc < 2) {
    cout << "\nFailed: Missed an input file\n" << endl;
    exit(-1);
  }
  if (argc > 2) {
    cout << "\nFailed: Unexpected command line arguments\n" << endl;
    exit(-1);
  }
  fstream target(argv[1]);
  if (!target) {
    cout << "\nFailed: Can not find " << argv[1] << "\n" << endl;
    exit(-1);
  }
}

int main(int argc, char **argv) {
  // check_input(argc, argv);

  Yaamf yaamf("target.yaml");

  Timer timer;
  yaamf.run();
  timer.end_all();

  return 0;
}
