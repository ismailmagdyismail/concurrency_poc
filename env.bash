function run()
{
    local file=$1
    file=${file%.cpp}
    g++ -std=c++17 $file.cpp -o $file.exe
    ./$file.exe
}
