#include <locale.h>
#include <stdio.h>
#include <wchar.h>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "C.UTF-8"); // this also works

    wchar_t hello_eng[] = L"Hello World!";
    wchar_t hello_china[] = L"世界, 你好!";
    wchar_t* hello_japan = L"こんにちは日本!";
    printf("%ls\n", hello_eng);
    printf("%ls\n", hello_china);
    printf("%ls\n", hello_japan);

    return 0;
}