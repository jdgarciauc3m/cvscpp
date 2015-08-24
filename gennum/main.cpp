#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <random>
#include <algorithm>

struct options {
  int size;
  std::string outfile;
  bool binary = false;
};

std::ostream & operator<<(std::ostream & os, const options & ops) {
  os << "Size: " << ops.size << std::endl;
  os << "Outfile: " << ops.outfile << std::endl;
  return os;
}

options parse_args(const std::vector<std::string> & args) {

  using namespace std;

  std::vector<std::string> flags;
  std::vector<std::string> argvals;
  std::partition_copy(begin(args), end(args), 
    back_inserter(flags), back_inserter(argvals),
    [](const std::string & s) { return s.size()>0 && s[0]=='-'; });

  constexpr size_t expected_args = 2;
  if (argvals.size() !=expected_args) {
    std::cerr << "Wrong number of args. Expected " << expected_args << ". Received " << args.size() << std::endl;
    throw std::invalid_argument{"Parse error"};
  }

  options result;
  result.size = std::stoi(argvals[0]);
  result.outfile = argvals[1];

  for (auto && flag : flags) {
    if (flag == "-b") result.binary = true;
    else {
      std::cerr << "Invalid option " << flag << std::endl;
      throw std::invalid_argument{"Parse error"};
    }
  }

  return result;
}

int main(int argc, char ** argv) {
  std::vector<std::string> args{argv+1, argv+argc};
  auto ops = parse_args(args);

  std::cout << ops << std::endl;

  std::ofstream of{ops.outfile,
    (ops.binary) ? (std::ios_base::out|std::ios_base::binary) : (std::ios_base::out)};
  std::random_device rng;
  std::uniform_int_distribution<int> ugen{0, std::numeric_limits<int>::max()};
  for (auto i=ops.size; i>0;--i) {
    auto val = ugen(rng);
    if (ops.binary) {
      of.write(reinterpret_cast<char*>(&val), sizeof(val));
    }
    else {
      of << val << std::endl;
    }
  }

  return 0;
}
