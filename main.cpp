#include "llvm/Support/CommandLine.h"
#include <cstdio>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

using namespace llvm;

static constexpr char const *storeLocation = "todo";

static cl::opt<bool> Help("h", cl::desc("Alias for -help"), cl::Hidden);

static cl::OptionCategory TODOCategory("TODO options");

static cl::opt<std::string> Add("add", cl::desc("add a new todo item."),
                                cl::cat(TODOCategory));

static cl::opt<int> Done("done", cl::desc("mark an item as done."),
                         cl::cat(TODOCategory));

static cl::opt<int> Del("del", cl::desc("delete an item in the todo list."),
                        cl::cat(TODOCategory));

static cl::opt<bool> List("list", cl::desc("list all todo items"),
                          cl::cat(TODOCategory));

static cl::opt<bool> Clear("clear", cl::desc("remove all todo items."),
                           cl::cat(TODOCategory));

class TODO {
public:
  explicit TODO(std::string location) : Location(std::move(location)) {}

  void addItem(std::string_view item) {
    std::ofstream todo{Location, std::ios_base::app | std::ios_base::out};
    todo << fmt::format("- [ ] {}\n", item);
  }

  void listItems() {
    int index = 1;
    std::string line;
    std::ifstream todo{Location};
    while (std::getline(todo, line)) {
      fmt::print("{} {}\n", index++, line);
    }
  }

  void delItem(int index) {
    int Index = 1;
    std::string line;
    std::ifstream todo{Location};
    std::ofstream tmp{".tmp_todo"};
    while (std::getline(todo, line)) {
      if (Index++ != index) {
        tmp << line << "\n";
      }
    }
    std::rename(".tmp_todo", Location.c_str());
  }

  void doneItem(int index) {
    int Index = 1;
    std::string line;
    std::ifstream todo{Location};
    std::ofstream tmp{".tmp_todo"};
    while (std::getline(todo, line)) {
      if (Index++ != index) {
        tmp << line << "\n";
      } else {
        tmp << "- [x]" << line.substr(5) << "\n";
      }
    }

    std::rename(".tmp_todo", Location.c_str());
  }

  void clear() { std::ofstream todo{Location}; }

private:
  std::string Location;
};

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv,
                              "A very simple todo list in the terminal.\n");
  TODO todo{storeLocation};

  if (!Add.empty()) {
    todo.addItem(Add.getValue());
  }

  if (Done > 0) {
    todo.doneItem(Done);
  }

  if (Del > 0) {
    todo.delItem(Del);
  }

  if (List) {
    todo.listItems();
  }

  if (Clear) {
    todo.clear();
  }
}
