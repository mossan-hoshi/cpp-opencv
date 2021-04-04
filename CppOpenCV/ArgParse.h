#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

class Argument {
 public:
  Argument(std::vector<std::string> command_options, std::string dest,
           std::vector<std::string> values, std::string description,
           std::string type) {
    initialize(command_options = command_options, dest = dest, values = values,
               description = description, type = type);
  };
  Argument(std::string command_option, std::string dest,
           std::vector<std::string> values, std::string description,
           std::string type) {
    initialize(command_options = std::vector<std::string>{command_option},
               dest = dest, values = values, description = description,
               type = type);
  };
  Argument(std::vector<std::string> command_options, std::string dest,
           std::string value, std::string description, std::string type) {
    initialize(command_options = command_options, dest = dest,
               values = std::vector<std::string>{value},
               description = description, type = type);
  };
  Argument(std::string command_option, std::string dest, std::string value,
           std::string description, std::string type) {
    initialize(command_options = std::vector<std::string>{command_option},
               dest = dest, values = std::vector<std::string>{value},
               description = description, type = type);
  };
  Argument(const Argument& rhs) {
    initialize(command_options = rhs.command_options, dest = rhs.dest,
               values = rhs.values, description = rhs.description,
               type = rhs.type);
  }

  std::vector<std::string> get() { return values; };

  bool IsCommandOptionMatched(std::string command_option) {
    // erase '--' or '-'
    const std::string compare_command_option = command_option.replace(
        command_option.begin(), command_option.end(), "-", "");
    for (int i = 0; i <= this->command_options.size(); i++) {
      if (compare_command_option == this->command_options[i]) return true;
    }
    return false;
  }

  bool IsNameMatched(std::string dest) { return (dest == this->dest); }

  void SetValue(std::string valueStr) {
    this->values = std::vector<std::string>{valueStr};
  }
  void SetValues(std::vector<std::string> valueStrs) {
    this->values = std::vector<std::string>{};
    std::copy(valueStrs.begin(), valueStrs.end(), back_inserter(this->values));
    this->is_vector = true;
  }

  void SetCommandOption(std::string name) {
    SetCommandOptions(std::vector<std::string>{name});
  }
  void SetCommandOptions(std::vector<std::string> options_to_set) {
    command_options = std::vector<std::string>{};
    for_each(options_to_set.begin(), options_to_set.end(),
             [&](std::string option_to_set) {
               option_to_set.erase(
                   std::remove(option_to_set.begin(), option_to_set.end(), '-'),
                   option_to_set.end());
               std::cout << option_to_set << std::endl;
               command_options.push_back(option_to_set);
             });
  }
  std::string getType() { return type; };
  std::string getDest() { return dest; };

 private:
  void initialize(std::vector<std::string>& command_options, std::string dest,
                  std::vector<std::string>& values,
                  std::string description = "", std::string type = "string") {
    this->SetCommandOptions(command_options);
    this->dest = dest;
    this->SetValues(values);
    this->description = description;
    this->type = type;
  };
  std::vector<std::string> command_options;
  std::string dest;
  std::string description;
  std::string type;
  bool is_vector;
  std::vector<std::string> values;
};

// convertStringToValue()
void convertStringToValue(std::string str, char& result) {
  result = static_cast<char>(stoi(str));
}
void convertStringToValue(std::string str, unsigned char& result) {
  result = static_cast<unsigned char>(stoi(str));
}
void convertStringToValue(std::string str, short& result) {
  result = static_cast<short>(stoi(str));
}
void convertStringToValue(std::string str, unsigned short& result) {
  result = static_cast<unsigned short>(stoi(str));
}
void convertStringToValue(std::string str, int& result) { result = stoi(str); }
void convertStringToValue(std::string str, unsigned int& result) {
  result = static_cast<unsigned int>(stoi(str));
}
void convertStringToValue(std::string str, long& result) {
  result = static_cast<long>(stoll(str));
}
void convertStringToValue(std::string str, unsigned long& result) {
  result = static_cast<unsigned long>(stoll(str));
}
void convertStringToValue(std::string str, long long& result) {
  result = stoll(str);
}
void convertStringToValue(std::string str, float& result) {
  result = stof(str);
}
void convertStringToValue(std::string str, double& result) {
  result = stod(str);
}
void convertStringToValue(std::string str, std::string& result) {
  result = str;
}

class ArgumentParser {
 public:
  ArgumentParser() { Arguments = std::vector<Argument>{}; };

  void AddArgument(
      std::vector<std::string> command_options, std::string dest,
      std::string type = "std::string",
      std::vector<std::string> deaults = std::vector<std::string>{},
      std::string description = "") {
    Arguments.push_back(
        Argument(command_options, dest, deaults, description, getType(type)));
  }
  void AddArgument(
      std::string command_options, std::string dest,
      std::string type = "std::string",
      std::vector<std::string> deaults = std::vector<std::string>{},
      std::string description = "") {
    Arguments.push_back(
        Argument(command_options, dest, deaults, description, getType(type)));
  }
  void AddArgument(std::vector<std::string> command_options, std::string dest,
                   std::string type = "std::string", std::string deaults = "",
                   std::string description = "") {
    Arguments.push_back(
        Argument(command_options, dest, deaults, description, getType(type)));
  }
  void AddArgument(std::string command_options, std::string dest,
                   std::string type = "std::string", std::string deaults = "",
                   std::string description = "") {
    Arguments.push_back(
        Argument(command_options, dest, deaults, description, getType(type)));
  }

  void ParseArgs(int argc, char* argv[]) {
    std::vector<std::string> keys{};
    std::vector<std::vector<std::string> > values{};
    int option_index = -1;
    // collect options
    for (int i = 1; i < argc; i++) {
      std::string argStr(argv[i]);
      std::cout << argStr << std::endl;
      if (isDoubleHyphenOption(argStr)) {
        keys.push_back(eraseChar(argStr, '-'));
        values.push_back(std::vector<std::string>{});
        option_index += 1;
      } else if (option_index >= 0) {
        values[option_index].push_back(argStr);
      } else {
        throw std::invalid_argument("[ERROR] invalid option ");
      }
      // TODO : single hyphen option
    }

    // set arguments values
    for (int i = 0; i < keys.size(); i++) {
      getArgument(keys[i]).SetValues(values[i]);
    }
  }

  Argument& getArgument(std::string dest) {
    for (int i = 0; i < Arguments.size(); i++) {
      if (Arguments[i].IsNameMatched(dest)) {
        return Arguments[i];
      }
    }
    throw std::invalid_argument("[ERROR] no such argument : " + dest);
  }

  Argument& operator[](std::string dest) { return getArgument(dest); }

  template <class T>
  std::vector<T> get(std::string dest) const {
    for (int i = 0; i < Arguments.size(); i++) {
      if (Arguments[i].IsCommandOptionMatched(dest)) {
        std::vector<T> values{};
        auto valuesStr = Arguments[i].get();
        valueStringsToValues(valuesStr, values);
        return values;
      }
    }
    throw std::invalid_argument("[ERROR] no such argument : " + dest);
  }

 private:
  std::vector<Argument> Arguments;

  template <class T>
  void valueStringsToValues(std::vector<std::string>& valueStrs,
                            std::vector<T>& values) {
    values.clear();
    for_each(valueStrs.begin(), valueStrs.end(), [&](std::string valueStr) {
      T tmpResultValue;
      convertStringToValue(valueStr, tmpResultValue);
      values.push_back(tmpResultValue);
    });
  }

  bool isSingleHyphenOption(std::string argStr) {
    if (argStr.size() < 2) return false;
    return argStr[0] == '-' && argStr[1] != '-';
  }
  bool isDoubleHyphenOption(std::string argStr) {
    if (argStr.size() < 3) return false;
    return argStr[0] == '-' && argStr[1] == '-';
  }

  std::string eraseChar(std::string str, char erase_char) {
    str.erase(std::remove(str.begin(), str.end(), erase_char), str.end());
    return str;
  }

  bool isSameStrings(std::string str1, std::string str2) {
    return str1.size() == str2.size() &&
           std::equal(str1.cbegin(), str1.cend(), str2.cbegin(), str2.cend(),
                      [](const char& c1, const char& c2) {
                        return tolower(c1) == tolower(c2);
                      });
  }

  bool isStringIncludedInStringVector(std::string str1,
                                      std::vector<std::string> stringVector) {
    bool result = false;
    for_each(stringVector.begin(), stringVector.end(), [&](std::string str2) {
      if (isSameStrings(str1, str2)) {
        result = true;
      }
    });
    return result;
  }

  std::string getType(std::string typeStr) {
    if (isStringIncludedInStringVector(typeStr, {"char", "character", "c"})) {
      return typeid(char).name();
    } else if (isStringIncludedInStringVector(
                   typeStr,
                   {"unsigned char", "unsigned character", "uchar", "uc"})) {
      return typeid(unsigned char).name();
    } else if (isStringIncludedInStringVector(typeStr, {"short", "s"})) {
      return typeid(short).name();
    } else if (isStringIncludedInStringVector(
                   typeStr, {"unsigned short", "ushort", "us"})) {
      return typeid(unsigned short).name();
    } else if (isStringIncludedInStringVector(typeStr,
                                              {"int", "integer", "i"})) {
      return typeid(int).name();
    } else if (isStringIncludedInStringVector(
                   typeStr,
                   {"unsigned int", "unsigned integer", "uint", "ui"})) {
      return typeid(unsigned int).name();
    } else if (isStringIncludedInStringVector(typeStr, {"long", "l"})) {
      return typeid(long).name();
    } else if (isStringIncludedInStringVector(
                   typeStr, {"unsigned long", "ulong", "ul"})) {
      return typeid(unsigned long).name();
    } else if (isStringIncludedInStringVector(typeStr, {"long long", "ll"})) {
      return typeid(long long).name();
    } else if (isStringIncludedInStringVector(typeStr, {"float", "f"})) {
      return typeid(float).name();
    } else if (isStringIncludedInStringVector(typeStr, {"doube", "d"})) {
      return typeid(double).name();
    } else if (isStringIncludedInStringVector(
                   typeStr, {"std::string", "string", "str", "s"})) {
      return typeid(std::string).name();
    }
    throw std::invalid_argument("[ERROR] invalid type String : " + typeStr);
  }
};
