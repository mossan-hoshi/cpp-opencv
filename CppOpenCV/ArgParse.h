#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

class Argument {
 public:
  Argument(std::vector<std::string>& names, std::vector<std::string>& values,
           std::string description = "", std::string type = "string") {
    this->initialize(names = names, values = values, description = description,
                     type = type);
  };
  Argument(const Argument& rhs) {
    this->initialize(names = rhs.names, values = rhs.values,
                     description = rhs.description, type = rhs.type);
  }

  std::vector<std::string> get() { return values; };

  bool IsNameMatched(std::string name) {
    // erase '--' or '-'
    const std::string compare_name =
        name.replace(name.begin(), name.end(), "-", "");
    for (int i = 0; i <= this->names.size(); i++) {
      if (compare_name == this->names[i]) return true;
    }
    return false;
  }

  void SetValue(std::string valueStr) { this->values = std::vector{valueStr}; }
  void SetValues(std::vector<std::string> valueStrs) {
    this->values = std::vector<std::string>();
    std::copy(valueStrs.begin(), valueStrs.end(), back_inserter(this->values));
    this->is_vector = true;
  }

  void SetName(std::string name) {
    this->SetNames(std::vector<std::string>{name});
  }
  void SetNames(std::vector<std::string> names) {
    for_each(names.begin(), names.end(), [&](std::string name) {
      const std::string compare_name =
          name.replace(name.begin(), name.end(), "-", "");
      for_each(this->names.begin(), this->names.end(),
               [name](std::string name2) {
                 if (name2 == name) return true;
               });
    });
  }
  std::string getType() { return this->type; };

 private:
  void initialize(std::vector<std::string>& names,
                  std::vector<std::string>& values,
                  std::string description = "", std::string type = "string") {
    this->SetNames(names);
    this->SetNames(values);
    this->description = description;
    this->type = type;
  };
  std::vector<std::string> names;
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
  void AddArgument(std::vector<std::string> names,
                   std::vector<std::string> values,
                   std::string description = "",
                   std::string type = "std::string") {
    Arguments.push_back(Argument(names = names, values = values,
                                 description = description,
                                 type = this->getType(type)));
  }

  template <class T>
  std::vector<T> get(std::string name) const {
    for_each(Arguments.begin(), Arguments.end(), [&](Argument arg) {
      if (arg.IsNameMatched(name)) {
        std::vector<T> values{};
        auto valuesStr = arg.get();
        for_each(valuesStr.begin(), valuesStr.end(), [&](std::string valueStr) {
          T tmpResultValue;
          convertStringToValue(valuesStr, tmpResultValue);
          values.push_back(tmpResultValue);
        });
      }
    });
  }

 private:
  std::vector<Argument> Arguments;

  bool isSameStrings(std::string str1, std::string str2) {
    return str1.size() == str2.size() &&
           std::equal(str1.cbegin(), str1.cend(), str2.cbegin(), str2.cend(),
                      [](const char& c1, const char& c2) {
                        return tolower(c1) == tolower(c2);
                      });
  }

  bool isStringIncludedInStringVector(std::string str1,
                                      std::vector<std::string> stringVector) {
    for_each(stringVector.begin(), stringVector.end(), [&](std::string str2) {
      if (this->isSameStrings(str1, str2)) return true;
    });
    return false;
  }

  std::string getType(std::string typeStr) {
    if (this->isStringIncludedInStringVector(typeStr,
                                             {"char", "character", "c"})) {
      return typeid(char).name();
    } else if (this->isStringIncludedInStringVector(
                   typeStr,
                   {"unsigned char", "unsigned character", "uchar", "uc"})) {
      return typeid(unsigned char).name();
    } else if (this->isStringIncludedInStringVector(typeStr, {"short", "s"})) {
      return typeid(short).name();
    } else if (this->isStringIncludedInStringVector(
                   typeStr, {"unsigned short", "ushort", "us"})) {
      return typeid(unsigned short).name();
    } else if (this->isStringIncludedInStringVector(typeStr,
                                                    {"int", "integer", "i"})) {
      return typeid(int).name();
    } else if (this->isStringIncludedInStringVector(
                   typeStr,
                   {"unsigned int", "unsigned integer", "uint", "ui"})) {
      return typeid(unsigned int).name();
    } else if (this->isStringIncludedInStringVector(typeStr, {"long", "l"})) {
      return typeid(long).name();
    } else if (this->isStringIncludedInStringVector(
                   typeStr, {"unsigned long", "ulong", "ul"})) {
      return typeid(unsigned long).name();
    } else if (this->isStringIncludedInStringVector(typeStr,
                                                    {"long long", "ll"})) {
      return typeid(long long).name();
    } else if (this->isStringIncludedInStringVector(typeStr, {"float", "f"})) {
      return typeid(float).name();
    } else if (this->isStringIncludedInStringVector(typeStr, {"doube", "d"})) {
      return typeid(double).name();
    } else if (this->isStringIncludedInStringVector(typeStr,
                                                    {"string", "str", "s"})) {
      return typeid(std::string).name();
    }
  }
};
