#include <iostream>
#include <string>

#include "ArgParse.h"
#include "CppOpenCV.h"

ArgumentParser ArgParse(int argc, char* argv[]) {
  ArgumentParser args = ArgumentParser();

  args.AddArgument(
      std::vector<std::string>{
          "--in_file_path",
          "--ifp",
      },
      "in_file_path", "string", std::string(R"(..\data\sample.jpg)"),
      "input image file path");

  args.AddArgument(
      std::vector<std::string>{
          "--out_dir_path",
          "--odp",
      },
      "out_dir_path", "std::string", std::string(R"(..\out)"),
      "output folder path");

  args.AddArgument("--char_arg_sample", "char_arg_sample", "char", "-1",
                   "character argument sample");

  args.AddArgument("--uchar_arg_sample", "uchar_arg_sample", "unsigned char", "255",
                   "unsigned char argument sample");

  args.AddArgument("--int_arg_sample", "int_arg_sample", "int", "-1000",
                   "integer argument sample");

  args.AddArgument("--uint_arg_sample", "uint_arg_sample", "uint", "9999",
                   "unsigned integer argument sample");

  args.AddArgument("--long_long_arg_sample", "long_long_arg_sample", "ll", "99999999999",
                   "long_long argument sample");

  args.AddArgument("--float_arg_sample", "float_arg_sample", "float", "1.5",
                   "float argument sample");

  return args;
}

int main(int argc, char* argv[]) {
  auto args = ArgParse( argc, argv[]);
  ImageProcess(args);
}
