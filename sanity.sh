#!/bin/bash

cd "$(dirname "$0")"

for p in sanity/*; do ./${p}; done
