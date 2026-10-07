#!/bin/sh
# Copyright (C) 2011-2024 GraphicsMagick Group
# SPDX-License-Identifier: MIT
#
# Simple filter to filter a ChangeLog to something in reStructuredText.
#
if [ -n "$1" ]
then
    printf "================================\n%s\n================================\n\n" "$1"
else
    printf "=========================\n%s\n=========================\n\n" "ChangeLog"
fi
expand | sed -e 's/^        \* /  - /g ; s/^        /    /g ; s/\*/\\*/g; s/\_/\\_/g'
