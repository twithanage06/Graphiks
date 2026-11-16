import math
import subprocess
from pathlib import Path

RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
RESET = "\033[0m"

def fail_msg(inp, out, expected):
    msg = f"{RED}FAILED!!!{RESET}\nEntered: {inp}\nExpected: {expected}\nGot: {out}"
    print("-" * max(len(line) for line in msg.splitlines()))
    print(f"\n{msg}\n")


ROOT = Path(__file__).resolve().parent.parent
EXECUTABLE = ROOT / "calculator"
errors = 0
passes = 0
test_cases = {
    #Addition
    "30+3":33,
    "30+-3": 27,
    "-30+3": -27,
    "-30+-3":-33,
    "30+0":30,
    #Subtraction
    "30-3":27,
    "30--3":33,
    "-30-3":-33,
    "-30--3": -27,
    "30-0":30,
    #Multiplication
    "30*3":90,
    "30*-3":-90,
    "-30*3":-90,
    "-30*-3":90,
    "30*0":0,
    #Division
    "30/3":10,
    "30/-3":-10,
    "-30/3":-10,
    "-30/-3":10,
    "0/30":0,
    "30/0": "Division by zero",
    "30/30":1,
    #Parenthesis
    "(30+3)+4":37,
    "(30+3)-4":29,
    "(30+3)*4":132,
    "(30+3)/4":(33/4),
    "(30+3)/0": "Division by zero",
    "(30+3": "No closing parenthesis",
    "30+3)": "Missing opening parenthesis",
    "()": "Empty parenthesis",
    #Exponent
    "2^3": 8,
    "2^-3":(1/8),
    "-2^2":-4,
    "-2^3":-8,
    "-2^-3":-(1/8),
    "2^0":1,
    "0^2":0,
    "0^0":1,
    "0^-2": "Division by zero"
}

for case, expected in test_cases.items():
    result = subprocess.run(
        [str(EXECUTABLE)],
        input=case + "\n",
        capture_output=True,
        text=True,
        timeout=5
    )

    if isinstance(expected, str):
        #Test expects an error
        actual = result.stderr.strip().removeprefix("Error: ").strip()

        passed = (
            result.returncode != 0 and
            actual == expected
        )

        if result.returncode == 0:
            actual = result.stdout.strip()

    else:
        #Test expects a numerical result
        if result.returncode != 0:
            actual = result.stderr.strip()
            passed = False
        else:
            try:
                actual = float(result.stdout.strip())
                passed = math.isclose(
                    actual, expected,
                    rel_tol=1e-6,
                    abs_tol=1e-9
                )
            except ValueError:
                actual = result.stdout.strip()
                passed = False

    if passed:
        passes += 1
    else:
        errors += 1
        fail_msg(case, actual, expected)


width = 20
print("-" * width)
print(f"| {f'{GREEN}Passes:{RESET} {passes}':<{width-4}} |")
print(f"| {f'{RED}Errors:{RESET} {errors}':<{width-4}} |")
print("-" * width)