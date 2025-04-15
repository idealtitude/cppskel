#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
{{DOCSTRING}}
"""

import sys
#import os

#from typing import Any
import argparse


# App version
__author__  = "stephane"
__version__ = "0.0.0"
#__license__ = "MT108"

# Constants
EXIT_SUCCESS = 0
EXIT_FAILURE = 1
#APP_PATH = os.path.dirname(os.path.realpath(__file__))
#APP_CWD = os.getcwd()


# Command line arguments
# def get_args() -> argparse.Namespace:
    # parser = argparse.ArgumentParser(
        # prog="", description="", epilog="Help and documentation at..."
    # )
#
    # parser.add_argument("number", nargs=1, help="")
    # parser.add_argument(
        # "-v", "--version", action="version", version=f"%(prog)s {__version__}"
    # )
#
    # return parser.parse_args()


# Entry point
def main(_args: list[str]) -> int:
    """Entry point, main function."""
    #arguments: argparse.Namespace = get_args()

    return EXIT_SUCCESS


if __name__ == "__main__":
    sys.exit(main(sys.argv))
