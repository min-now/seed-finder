import sys

def main():
	map_file = open(f"{sys.argv[1]}", "rb")
	if len(sys.argv) != 3:
		print(f"Usage: {sys.argv[1]} <.per_file> <c_struct_name>")
		sys.exit(1)

	SIZE_X = int.from_bytes(map_file.read(1), "big"); map_file.read(1)
	SIZE_Y = int.from_bytes(map_file.read(1), "big")
	map_file.read(5)
	map_file.read(2)

	# print(SIZE_X, SIZE_Y)

	map_data = [[0 for x in range(SIZE_Y)] for y in range(SIZE_X)]

	print(f"static const u8 {sys.argv[2]}_DATA[{SIZE_Y}][{SIZE_X}] = {{")

	for x in range(SIZE_X):
		print("\t{", end="")
		for y in range(SIZE_Y):
			tile = int.from_bytes(map_file.read(1), "big")
			map_data[x][y] = hex(tile)
			# if y == SIZE_Y - 1
			print(f"{map_data[x][y]}", end=", " if y != SIZE_Y - 1 else "")

			map_file.read(7)
		print("}", end=",\n" if x != SIZE_X - 1 else "")

	print("};")

	map_file.close()

if __name__ == "__main__":
	main()
