def read_array_from_file(filename):
    with open(filename, 'r') as file:
        line = file.readline().strip()
        array = list(map(int, line.split(',')))
    return array

def is_sorted(array):
    return all(array[i] <= array[i + 1] for i in range(len(array) - 1))

def main():
    sorted_array_file = 'build/sorted_array.txt'
    random_array_file = 'build/random_array.txt'

    sorted_array = read_array_from_file(sorted_array_file)
    random_array = read_array_from_file(random_array_file)

    if is_sorted(sorted_array):
        print(f"[SUCCESS] The array in {sorted_array_file} is sorted correctly.")
    else:
        print(f"[FAILURE] The array in {sorted_array_file} is NOT sorted correctly.")

    sorted_random_array = sorted(random_array)
    if sorted_array == sorted_random_array:
        print(f"[SUCCESS] The array in {sorted_array_file} is equal to the sorted version of the array in {random_array_file}.")
    else:
        print(f"[FAILURE] The array in {sorted_array_file} is NOT equal to the sorted version of the array in {random_array_file}.")

if __name__ == "__main__":
    main()