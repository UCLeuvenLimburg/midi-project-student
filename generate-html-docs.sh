#!/usr/bin/env bash

find -mindepth 1 -name "*.asciidoc" | xargs asciidoctor -R docs -D html