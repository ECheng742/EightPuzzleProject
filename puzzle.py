size = int(input("Enter size: "))
game_list = []
for i in range(size):
    game_list.append([0]*size)

for i in game_list:
    for j in i:
        print(j,end=" ")
    print()

# class Puzzle:
#     # initializer
#     x = 0
#     game = [[],[],[]]
#     def __init__(self):
#         x = 5


# if __name__ == "__main__":
#     print("Hello world")
#     p = Puzzle()
#     print(p.x)
