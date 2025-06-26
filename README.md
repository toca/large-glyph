# large-glyph
A simple tool to generate large ASCII letters for your terminal.

```
large-glyph.exe "Hello, World!"

>██╗  ██╗        ██╗  ██╗                                      ██╗       ██╗ ██╗
>██║  ██║ █████╗  ██╗  ██╗  █████╗      ██╗  ██╗ █████╗ ██╗ ██╗ ██╗      ██║ ██║
>███████║██▄▄▄██╗ ██║  ██║ ██╔══██╗     ██║█╗██║██╔══██╗██║█╔═╝ ██║  ██████║ ██║
>██╔══██║██╔════╝ ██║  ██║ ██║  ██║     ██║█║██║██║  ██║███╔╝   ██║ ██╔══██║ ╚═╝
>██║  ██║ ██████╗ ███╗ ███╗ █████╔╝      █████╔╝ █████╔╝██╔╝    ███╗ ██████║ ██╗
>╚═╝  ╚═╝ ╚═════╝ ╚══╝ ╚══╝ ╚════╝       ╚════╝  ╚════╝ ╚═╝     ╚══╝ ╚═════╝ ╚═╝

large-glyph - Display a string as large ASCII art

Usage:
  large-glyph [--color fg,bg] [string]

Options:
  --color fg,bg   Specify foreground (fg) and background (bg) color.
                  You can use color names or ANSI codes (30-37, 40-47).
                  Example: --color red,yellow
                           --color 32,47
  -h, --help      Show this help message.

Color names: black, red, green, yellow, blue, magenta, cyan, white
Examples:
  large-glyph --color green,black Hello
  large-glyph -h
```