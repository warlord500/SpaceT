#!/bin/bash
left=$1
right=$2

leftahead=`git rev-list --count $right..$left`
rightahead=`git rev-list --count $left..$right`

echo "$left (ahead $leftahead) | (behind $rightahead) $right"
