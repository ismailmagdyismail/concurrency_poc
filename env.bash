function compile_run()
{
    local file=$1
    g++ -std=c++11 mini_pocs/$file.cpp -o mini_pocs/$file.exe
    ./mini_pocs/$file.exe
}
