#!/bin/bash

docker run -v $PWD:/work -w /work  dbyin/wasmsdk:1.0 /build_wasm.sh
