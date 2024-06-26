#!/usr/bin/python3

import subprocess

result = subprocess.run(['./a.out'], capture_output=True, text=True)
if result.returncode != 0:
    raise Exception(result.stderr.rstrip())
print(result.stdout.rstrip())

