#!/usr/bin/env python3

import json
import sys
import re


report_filename = None
report_data = None


class colors:
    BLACK = '\033[30m'
    RED = '\033[31m'
    GREEN = '\033[32m'
    YELLOW = '\033[33m'
    BLUE = '\033[34m'
    MAGENTA = '\033[35m'
    CYAN = '\033[36m'
    WHITE = '\033[37m'
    UNDERLINE = '\033[4m'
    RESET = '\033[0m'


def abort():
    sys.exit(-1)


def print_colored(string, color):
    print(f'{color}{string}{colors.RESET}')


def print_info(string):
    print(string)


def print_error(string):
    print_colored(string, colors.RED)


def print_success(string):
    print_colored(string, colors.GREEN)


def get_report_filename():
    global report_filename

    if len(sys.argv) != 2:
        print_error("Call this script with the name of the file containing your report as parameter.")
        print_error("E.g. python check-report.py report.json")
        abort()

    report_filename = sys.argv[1]


def open_report():
    print_info("Opening report")
    global report_filename
    global report_data

    try:
        with open(report_filename) as file:
            report_data = json.load(file)
    except FileNotFoundError:
        print_error(f'Failed to open {report_filename}')
        abort()
    except json.JSONDecodeError as e:
        print_error(f'Your JSON file is malformed: {str(e)}')
        abort()


def get_report_entry_value(entry_name):
    global report_data

    if entry_name not in report_data:
        print_error(f'Your report is missing an entry named {entry_name}')
        abort()
    else:
        return report_data[entry_name]


def check_presence(entry_name):
    print_info(f'Checking presence of {entry_name}')
    global report_data
    get_report_entry_value(entry_name)


def check_by_regex(entry_name, regex):
    print_info(f'Checking {entry_name}')
    global report_data

    entry_value = get_report_entry_value(entry_name)
    match = re.fullmatch(regex, entry_value)
    if match is None:
        print_error(f'Report entry {entry_name} has value {entry_value}')
        print_error(f'It should match the regex {regex}')
        abort()


def check_no_todos():
    global report_data

    def check(x):
        if isinstance(x, str):
            if x == 'TODO':
                print_error('Your report still contains a TODO')
                abort()
        elif isinstance(x, dict):
            for _, v in x.items():
                check(v)
        elif isinstance(x, list):
            for y in x:
                check(y)
    check(report_data)


def success():
    print_success('Everything seems to be okay')
    print_success(f'You can submit {report_filename} as your report')



get_report_filename()
open_report()
print('')
check_no_todos()
check_presence('first-name')
check_presence('last-name')
check_by_regex('student-id', r'[sruSRU]\d{7}')
check_by_regex('github-url', f'https://github.com/ucll-pvm1920/midi-project-.*')
print('')
success()
