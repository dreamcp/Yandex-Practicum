#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

using namespace std;
using filesystem::path;

path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}



void PrintDirectory(ostream& dst, const path& p, const string& shift)
{
    set<string> files;
    set<string> dirs;

    dst << shift << p.filename().string() << endl;
   
     for (const auto& dir_entry: filesystem::directory_iterator(p)) {
        auto status = dir_entry.status().type();
        if( status == filesystem::file_type::directory){
            //PrintDirectory(dst, dir_entry.path(), shift + "  ");
            dirs.insert(dir_entry.path().string());
        }
        else if(status == filesystem::file_type::regular)
            files.insert(dir_entry.path().filename().string());          
    } 

    for ( auto dir = dirs.rbegin(); dir != dirs.rend(); ++dir) {        
        PrintDirectory(dst, path(*dir), shift + "  ");
    }

    for ( auto f = files.rbegin(); f != files.rend(); ++f)
        dst << shift << "  " << *f << endl;
}


// напишите эту функцию
void PrintTree(ostream& dst, const path& p)
{
    PrintDirectory(dst, p, "");
}

int main() {
    error_code err;
    filesystem::remove_all("test_dir", err);
    filesystem::create_directories("test_dir"_p / "a"_p, err);
    filesystem::create_directories("test_dir"_p / "b"_p, err);

    ofstream("test_dir"_p / "b"_p / "f1.txt"_p);
    ofstream("test_dir"_p / "b"_p / "f2.txt"_p);
    ofstream("test_dir"_p / "a"_p / "f3.txt"_p);

    ostringstream out;

    PrintTree(out, "test_dir"_p);
    cout << out.str();
    assert(out.str() ==
        "test_dir\n"
        "  b\n"
        "    f2.txt\n"
        "    f1.txt\n"
        "  a\n"
        "    f3.txt\n"s
    );
}
