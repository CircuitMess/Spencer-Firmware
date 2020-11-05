#!/bin/bash

for f in $(find www -type f); do
  mkdir -p data/$(dirname $f)
  gzip -c "$f" > "data/$f.gz"
done