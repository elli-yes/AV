// #include <fstream>
// #include <iostream>
// using namespace std;
// #include <filesystem>
// using namespace std::filesystem;
// #include <typeinfo>
// #include <vector>
// #include <algorithm>
// #include <iterator>

// path pathToShow("/home/");
// cout << "exists() = " << exists(pathToShow) << "\n"
//      << "root_name() = " << pathToShow.root_name() << "\n"
//      << "root_path() = " << pathToShow.root_path() << "\n"
//      << "relative_path() = " << pathToShow.relative_path() << "\n"
//      << "parent_path() = " << pathToShow.parent_path() << "\n"
//      << "filename() = " << pathToShow.filename() << "\n"
//      << "stem() = " << pathToShow.stem() << "\n"
//      << "extension() = " << pathToShow.extension() << "\n";

// void scan()
// {

//   char buff[50];
//   ifstream fin("cppstudio.doc", ios::binary);
//   const path workdir = current_path();

//   if (!fin.is_open())
//   {
//     printf("%s", typeid(workdir).name());
//     cout << "Файл не может быть открыт!\n";
//   }
//   else
//   {
//     fin >> buff;
//     cout << buff << endl;

//     fin.getline(buff, 50);
//     fin.close();
//     cout << buff << endl;
//   }
//   cout << system("ls | grep exe");
// }