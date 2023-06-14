def replace_spaces(line):
    line = line.strip()  # Remove leading/trailing whitespaces

    if line.startswith("newMonth"):
        line = line.replace("newMonth", "new_month_aux obj", 1)

    if line.startswith("addCostumer"):
        line = line.replace("addCostumer", "add_costumer_aux obj", 1)

    elif line.startswith("getPhone"):
        line = line.replace("getPhone", "get_phone_aux obj", 1)

    elif line.startswith("makeMember"):
        line = line.replace("makeMember", "make_member_aux obj", 1)

    elif line.startswith("isMember"):
        line = line.replace("isMember", "is_member_aux obj", 1)

    elif line.startswith("buyRecord"):
        line = line.replace("buyRecord", "buy_record_aux obj", 1)

    elif line.startswith("addPrize"):
        line = line.replace("addPrize", "add_prize_aux obj", 1)

    elif line.startswith("getExpenses"):
        line = line.replace("getExpenses", "get_expenses_aux obj", 1)

    elif line.startswith("putOnTop"):
        line = line.replace("putOnTop", "put_on_top_aux obj", 1)

    elif line.startswith("getPlace"):
        line = line.replace("getPlace", "get_place_aux obj", 1)

    line = line.replace(" ", "(", 1)  # Replace the first space with open parentheses "("
    line = line.replace(" ", ", ")  # Replace all other spaces with ", "
    line += ");"  # Add close parentheses ")" at the end

    line = line.replace("False", "false")
    line = line.replace("True", "true")

    return line


def process_file(file_path, output_file):
    with open(file_path, 'r') as input_file, open(output_file, 'w') as output_file:
        for line in input_file:
            processed_line = replace_spaces(line)
            print(processed_line, file=output_file)


if __name__ == '__main__':
    import sys

    if len(sys.argv) < 3:
        print("Please provide the path to the input file and the output file.")
        sys.exit(1)

    input_file_path = sys.argv[1]
    output_file_path = sys.argv[2]
    process_file(input_file_path, output_file_path)

