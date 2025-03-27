#include<iostream>
/*
一、文件系统
    1. 常用功能
        路径操作：跨平台路径解析、拼接、规范化。
        文件与目录管理：创建、删除、重命名、复制等。
        文件属性查询：检查文件是否存在、获取大小、修改时间等。
        目录遍历：递归或非递归遍历文件树。
        符号链接处理：创建和解析符号链接。
        错误处理：支持异常或错误码处理文件操作失败。
    2.核心类与函数
        1） 路径类：std::filesystem::path
            用途：表示文件路径，自动处理平台差异（如 / 与 \）。
            常用操作： 
                #include <filesystem>
                namespace fs = std::filesystem;
                fs::path p1 = "C:/MyFolder/data.txt";  // 路径初始化
                fs::path p2 = p1.parent_path();        // 获取父目录路径
                p1 /= "subdir/file2.txt";             // 路径拼接
                std::string str = p1.string();        // 转换为字符串
        2） 常用函数  
            函数	                        说明
            exists(path)	            检查路径是否存在。
            create_directory(path)	    创建目录。
            copy(src, dst)	            复制文件或目录。
            remove(path)	            删除文件或空目录。
            file_size(path)	            获取文件大小（字节）。
            last_write_time(path)	    获取文件最后修改时间。
            current_path()	            获取/设置当前工作目录。
            directory_iterator(path)	遍历目录下的文件和子目录。
二、文件流
    1. 功能
        C++ 文件流提供了对文件进行输入和输出操作的封装，它们是基于流的思想，将文件看作一个数据流进行处理。
    2. 核心类以及成员函数
        a. std::ifstream（输入文件流）
            构造函数
                可直接在构造时指定文件名和打开模式
                    std::ifstream in("input.txt");  // 默认以 std::ios::in 模式打开
            open()
                打开文件（适用于先声明对象后再打开文件）：
                    std::ifstream in;
                    in.open("input.txt", std::ios::in);
            is_open()
                检查文件是否成功打开：
            getline()
                从流中读取一行数据：
                    std::string line;
                    std::getline(in, line);
            operator>>
                用于格式化读取数据（如读取整数、字符串等
            close()
                关闭文件，释放相关资源
        b. std::ofstream（输出文件流）
            构造函数
            open()
            operator<<
                重载插入运算符，用于将数据写入文件
                    out << "Hello, Filesystem!" << std::endl;
            write()
                用于写入二进制数据，接受字符数组和长度
                    const char* buffer = "binary data";
                    out.write(buffer, strlen(buffer));
            close()
        c. std::fstream（双向文件流）
            构造函数
                std::fstream fs("data.txt", std::ios::in | std::ios::out);
            open()
            operator>> / operator<<
            seekg() / seekp()
                分别用于设置输入（get）和输出（put）位置：
                    fs.seekg(0); // 移动到文件开始位置，准备读取
                    fs.seekp(0, std::ios::end); // 移动到文件末尾，准备写入
            tellg() / tellp()
                获取当前输入/输出流的位置：
                    auto pos = fs.tellg();
            close()
    3. 打开模式
        a. std::ios::in
            用途：以输入（读）的方式打开文件。
            适用对象：通常用于 std::ifstream 或 std::fstream。
            行为：如果文件不存在，则打开失败。
        b. std::ios::out
            用途：以输出（写）的方式打开文件。
            适用对象：通常用于 std::ofstream 或 std::fstream。
            行为：默认情况下，如果文件已存在，会先清空文件内容（即执行截断操作）；如果文件不存在，会创建新文件。
        c. std::ios::app
            用途：以追加（append）的方式写入文件。
            行为：每次写操作都将数据附加到文件末尾，而不会截断原有内容。
            适用场景：日志记录、追加数据等场合。
        d. std::ios::ate
            用途：打开文件后立即移动到文件末尾。
            区别于 app：与 std::ios::app 不同，ate 仅在打开时将文件指针定位到末尾，之后的写操作可以在任意位置（如果手动移动文件指针的话）进行。
            适用场景：需要定位到文件末尾进行初始操作，但之后可能需要随机写入。
        e. std::ios::trunc
            用途：截断文件。
            行为：打开文件时将文件内容清空。
            默认行为：对于 std::ios::out 模式，如果未指定其他模式（例如 app），通常会自动包含 trunc，即清空文件。
        f. std::ios::binary
            用途：以二进制模式打开文件。
            区别于文本模式：在二进制模式下，文件读写不会对数据做任何转换（例如 Windows 下的换行符转换），适用于图像、音频、视频、压缩文件等非文本数据的操作。
    4.注意事项
        模式可以通过按位“或”操作组合使用，以满足特定需求，如：
            写入模式：
                std::ofstream out("file.txt", std::ios::out | std::ios::trunc);
            追加写模式（文本）：
                std::ofstream out("file.txt", std::ios::out | std::ios::app);

*/
//1.文件系统基本操作
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

void normalOperation(){
    //创建目录
    fs::path dir = "./filedir";
    if(!fs::exists(dir)){
        fs::create_directory(dir);
        std::cout << "dir has created.\n";
    }
    else std::cout << "dir existed.\n";
    //创建文件、如果文件不存在，自动创建
    fs::path file = dir / "data.txt";//std::filesystem::path 重载了/，没有重载+，含义就是连接两个路径
    std::ofstream(file) << "Hello, Filesystem!"; // 写入内容

    //复制与重命名
    fs::path src = "source.txt";
    fs::path dst = "backup/backup.txt";

    if (fs::exists(src)) {
        fs::copy(src, dst);        // 复制
        fs::rename(dst, "new.txt");// 重命名
    }

    //文件状态与权限
    auto status = fs::status("file.txt");
    if (fs::is_regular_file(status)) {
        std::cout << "Regular file\n";
    }
    auto perms = status.permissions();
    if ((perms & fs::perms::owner_write) != fs::perms::none) {
        std::cout << "Writable by owner\n";
    }



}
//2.递归遍历目录
//自带的
void recursiveList(const fs::path& dir) {
    for (const auto& entry : fs::recursive_directory_iterator(dir)) {
        std::cout << entry.path().filename() << "\n";
    }
}
//自行实现的
void displayList(const fs::path& dir,int id = 0){
    for (const auto& i : fs::directory_iterator(dir)){
        std::cout <<std::string("--", id) <<i.path().filename() << "\n";
        if(fs::is_directory(i)){
            displayList(i.path(),id+1);
        } 
    }
}

//3.错误处理
void handlerError(){
    try {
        fs::remove("non_existent_file.txt");
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    // 或使用错误码
    std::error_code ec;
    fs::remove("non_existent_file.txt", ec);
    if (ec) {
        std::cerr << "Error code: " << ec.message() << "\n";
    }
}

/*
4. 符号链接
    符号链接（Symbolic Link，也称为软链接）是一种特殊的文件，它指向另一个文件或目录。符号链接允许你使用一个路径名引用另一个路径名，
这在需要为文件或目录建立别名、实现跨目录的引用时非常有用。
    a. std::filesystem::create_symlink(target, link)
        创建一个符号链接，其中 target 是目标路径，link 是符号链接路径。
    b. std::filesystem::symlink_status(path)
        获取指定路径的符号链接状态，用于判断某个路径是否为符号链接。
    c. std::filesystem::read_symlink(path)
        读取符号链接所指向的目标路径。
*/
#include <string>
void testlink(){
     // 定义目标文件和符号链接的路径
     fs::path target = "target.txt";
     fs::path symlink = "link.txt";
 
     // 1. 创建目标文件，并写入初始内容
     if (!fs::exists(target)){
         std::ofstream out(target);
         if (!out) {
             std::cerr << "无法创建目标文件: " << target << std::endl;
         }
         out << "Hello, Filesystem via Symlink!" << std::endl;
     }
     
     // 2. 创建符号链接指向目标文件
     try {
         // 如果符号链接不存在，则创建
         if (!fs::exists(symlink)) {
             fs::create_symlink(target, symlink);
             std::cout << "创建符号链接成功: " << symlink 
                       << " -> " << target << std::endl;
         }
        fs::path target2 = fs::read_symlink(symlink);
        std::cout << "target2 path : " << target2 << std::endl;
     } catch (const fs::filesystem_error& e) {
         std::cerr << "创建符号链接失败: " << e.what() << std::endl;
     }
     
     // 3. 通过符号链接读取文件内容
     {
         std::ifstream in(symlink);
         if (!in) {
             std::cerr << "无法通过符号链接读取文件" << std::endl;
         }
         std::string line;
         std::getline(in, line);
         std::cout << "从符号链接读取内容: " << line << std::endl;
     }
     
     // 4. 通过符号链接写入文件内容（追加模式）
     {
         std::ofstream out(symlink, std::ios::app);
         if (!out) {
             std::cerr << "无法通过符号链接写入文件" << std::endl;
         }
         out << "追加的一行文本" << std::endl;
     }
     
     // 5. 读取目标文件，验证写入效果
     {
         std::ifstream in(target);
         if (!in) {
             std::cerr << "无法读取目标文件" << std::endl;
         }
         std::string line;
         std::cout << "目标文件内容:" << std::endl;
         while (std::getline(in, line)) {
             std::cout << line << std::endl;
         }
     }
    
    
}

int main(){
    //normalOperation();
    //recursiveList("/home/gamma/cppStudy/16_file");
    //displayList("/home/gamma/cppStudy/16_file");
    testlink();
    return 0;
}