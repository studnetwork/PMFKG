#!/bin/bash

chmod 644 $(find . -mindepth 1 -type f)
chmod 755 $(find . -mindepth 1 -type d)
