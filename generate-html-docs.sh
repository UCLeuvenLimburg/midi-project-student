#!/usr/bin/env bash

echo Converting AsciiDoc to HTML...
find -mindepth 1 -name "*.asciidoc" | xargs asciidoctor -R docs -D html
echo HTML files can be found under html directory