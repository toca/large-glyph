#include <Windows.h>
#include <locale.h>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "characters.h"

int color_name_to_code(const std::string& name, bool is_fg) {
    static const std::map<std::string, int> fg_map = {
        {"black", 30}, {"red", 31}, {"green", 32}, {"yellow", 33},
        {"blue", 34}, {"magenta", 35}, {"cyan", 36}, {"white", 37}
    };
    static const std::map<std::string, int> bg_map = {
        {"black", 40}, {"red", 41}, {"green", 42}, {"yellow", 43},
        {"blue", 44}, {"magenta", 45}, {"cyan", 46}, {"white", 47}
    };
    auto lower = name;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    if (is_fg) {
        if (fg_map.count(lower)) return fg_map.at(lower);
    }
    else {
        if (bg_map.count(lower)) return bg_map.at(lower);
    }
    // 数字指定も許容
    try {
        int code = std::stoi(name);
        if (is_fg && 30 <= code && code <= 37) return code;
        if (!is_fg && 40 <= code && code <= 47) return code;
    }
    catch (...) {}
    // デフォルト
    return is_fg ? 37 : 40;
}

void parse_color_option(const std::string& opt, int& fg, int& bg) {
    auto comma = opt.find(',');
    std::string fg_str = (comma == std::string::npos) ? opt : opt.substr(0, comma);
    std::string bg_str = (comma == std::string::npos) ? "" : opt.substr(comma + 1);
    fg = color_name_to_code(fg_str, true);
    bg = bg_str.empty() ? 40 : color_name_to_code(bg_str, false);
}

void print_help() {
    wprintf(
        L"large-glyph - Display a string as large ASCII art\n"
        L"\n"
        L"Usage:\n"
        L"  large-glyph [--color fg,bg] [string]\n"
        L"\n"
        L"Options:\n"
        L"  --color fg,bg   Specify foreground (fg) and background (bg) color.\n"
        L"                  You can use color names or ANSI codes (30-37, 40-47).\n"
        L"                  Example: --color red,yellow\n"
        L"                           --color 32,47\n"
        L"  -h, --help      Show this help message.\n"
        L"\n"
        L"Color names: black, red, green, yellow, blue, magenta, cyan, white\n"
        L"Examples:\n"
        L"  large-glyph --color green,black Hello\n"
        L"  large-glyph -h\n"

    );
}

// TODO new line?
int main(int argc, char** argv)
{

	UINT currentCodePage = ::GetConsoleOutputCP();
	if (currentCodePage == 0) {
		wprintf(L"Failed to get console output code page. LastError: 0x%08x\n", ::GetLastError());
		return 1;
	}
	::setlocale(LC_ALL, ".UTF8"); // Set locale to the user's default locale
	::SetConsoleOutputCP(65001);

    std::string input = "";
    int fg = 0, bg = 0;
    // コマンドライン引数のパース
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--help" || arg == "-h" || arg == "/?") {
            print_help();
            return 0;
        }
        else if (arg == "--color" && i + 1 < argc) {
            parse_color_option(argv[++i], fg, bg);
        }
        else {
            input += arg;
        }
    }
    if (input.empty()) {
        input = "Hello, World!";
    }

	std::vector<std::array<const std::wstring_view, 6>> output;
	for (const auto& c : input) {
		if (' ' <= c && c <= 'z') {
			//auto f = characters[c - ' '];
			output.push_back(characters[c - ' ']);
		}
	}
	
	// 出力
	for (int i = 0; i < 6; i++) {
        if (fg || bg) {
            // 色指定がある場合は、ANSIエスケープシーケンスを使用
            printf("\x1b[%d;%dm", fg, bg);
        }
		for (const auto& c : output) {
			wprintf(L"%s", c[i].data());
		}
	    printf("\x1b[0m");
		wprintf(L"\n");
	}
	// Reset console color


	::SetConsoleOutputCP(currentCodePage);
}
